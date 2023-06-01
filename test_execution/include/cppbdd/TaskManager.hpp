#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <iostream>
#include <any>
#include "cppbdd/format.hpp"

namespace cppbdd {

using namespace std;

enum TaskName {
    SCENARIO,
    GIVEN,
    WHEN,
    THEN,
    AND,
};


class Task {
public:
    Task(TaskName name, const string& msg)
        : name_(name), msg_(msg) {}

    virtual ~Task(void) = default;

    void printMessage(void) const;

    virtual void operator() (void) = 0;
    virtual size_t getMinReqExeTimes(void) const = 0;

    friend class TaskManager;

protected:
    static array<string, 5> task_names_;
    TaskName name_;
    string msg_;
};

typedef unique_ptr<Task> TaskUniquePtr;


class CallableTask final : public Task {
public:
    typedef function<void(void)> Callable;

    CallableTask(TaskName name, const string& msg, Callable callback)
        : Task(name, msg), callback_(callback) {}

    void operator() (void) override {
        this->printMessage();
        callback_();
    }

    size_t getMinReqExeTimes(void) const override {
        return 1;
    }

private:
    Callable callback_;
};

template<typename T>
class SingleArgCallableTask final : public Task {
public:
    typedef function<void(T)> Callable;

    SingleArgCallableTask(
        TaskName name,
        const string& msg,
        Callable callback,
        const vector<T>& test_cases
    ) : Task(name, msg),
        callback_(callback),
        test_cases_(test_cases) {}

    void operator() (void) override {
        this->printMessage(test_cases_[idx_]);
        callback_(test_cases_[idx_]);
        idx_++;
        if (idx_ == test_cases_.size()) idx_ = 0;
    }

    void printMessage(const T& test_case) const {
        switch (name_) {
        case TaskName::SCENARIO:
            cout << endl;
            break;
        case TaskName::GIVEN:
            cout << endl;
            // fall through
        case TaskName::WHEN:
        case TaskName::THEN:
        case TaskName::AND:
            cout << "  ";
            break;
        }

        cout << task_names_[name_] << ' ';
        cout << dyna_format(msg_, test_case) << endl;
    }

    size_t getMinReqExeTimes(void) const override {
        return test_cases_.size();
    }

private:
    Callable callback_;
    vector<T> test_cases_;
    size_t idx_ = 0;
};


class TaskManager {
public:
    bool addTask(CallableTask* const task) {
        if (!task) return false;
        tasks_.emplace_back(task);
        return true;
    }

    template<typename T>
    bool addTask(SingleArgCallableTask<T>* const task) {
        if (!task) return false;
        tasks_.emplace_back(task);
        return true;
    }

    void clear(void);
    void runAll(void);

protected:
    vector<TaskUniquePtr> tasks_;
};

}  // namespace: cppbdd

#endif  // TASK_MANAGER_HPP
