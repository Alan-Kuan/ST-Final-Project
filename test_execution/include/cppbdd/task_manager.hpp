#ifndef CPPBDD_TASK_MANAGER_HPP_
#define CPPBDD_TASK_MANAGER_HPP_

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <any>
#include "cppbdd/format.hpp"

namespace cppbdd {

enum TaskName {
    kScenario,
    kGiven,
    kWhen,
    kThen,
    kAnd,
};


class Task {
public:
    Task(TaskName name, const std::string& msg)
        : name_(name), msg_(msg) {}

    virtual ~Task(void) = default;

    void PrintMessage(void) const;

    virtual void operator() (void) = 0;
    virtual size_t GetMinReqExeTimes(void) const = 0;

    friend class TaskManager;

protected:
    static std::array<std::string, 5> task_names_;
    TaskName name_;
    std::string msg_;
};

typedef std::unique_ptr<Task> TaskUniquePtr;


class CallableTask final : public Task {
public:
    typedef std::function<void(void)> Callable;

    CallableTask(TaskName name, const std::string& msg, Callable callback)
        : Task(name, msg), callback_(callback) {}

    void operator() (void) override {
        this->PrintMessage();
        callback_();
    }

    size_t GetMinReqExeTimes(void) const override {
        return 1;
    }

private:
    Callable callback_;
};

template<typename T>
class SingleArgCallableTask final : public Task {
public:
    typedef std::function<void(T)> Callable;

    SingleArgCallableTask(
        TaskName name,
        const std::string& msg,
        Callable callback,
        const std::vector<T>& test_cases
    ) : Task(name, msg),
        callback_(callback),
        test_cases_(test_cases) {}

    void operator() (void) override {
        this->PrintMessage(test_cases_[idx_]);
        callback_(test_cases_[idx_]);
        idx_++;
        if (idx_ == test_cases_.size()) idx_ = 0;
    }

    void PrintMessage(const T& test_case) const {
        switch (name_) {
        case TaskName::kScenario:
            std::cout << std::endl;
            break;
        case TaskName::kGiven:
            std::cout << std::endl;
            // fall through
        case TaskName::kWhen:
        case TaskName::kThen:
        case TaskName::kAnd:
            std::cout << "  ";
            break;
        }

        std::cout << task_names_[name_] << ' ';
        std::cout << dyna_format(msg_, test_case) << std::endl;
    }

    size_t GetMinReqExeTimes(void) const override {
        return test_cases_.size();
    }

private:
    Callable callback_;
    std::vector<T> test_cases_;
    size_t idx_ = 0;
};


class TaskManager {
public:
    bool AddTask(CallableTask* const task) {
        if (!task) return false;
        tasks_.emplace_back(task);
        return true;
    }

    template<typename T>
    bool AddTask(SingleArgCallableTask<T>* const task) {
        if (!task) return false;
        tasks_.emplace_back(task);
        return true;
    }

    void clear(void);
    void RunAll(void);

protected:
    std::vector<TaskUniquePtr> tasks_;
};

}  // namespace cppbdd

#endif  // CPPBDD_TASK_MANAGER_HPP_
