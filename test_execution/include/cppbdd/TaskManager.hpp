#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <iostream>
#include "cppbdd/format.hpp"

namespace cppbdd {

enum TaskName {
    SCENARIO,
    GIVEN,
    WHEN,
    THEN,
    AND,
};


class Task {
public:
    Task(TaskName name, const std::string& msg)
        : name_(name), msg_(msg) {}
    void printMessage(void) const;

    virtual void operator() (void) = 0;
    virtual size_t getMinReqExeTimes(void) const = 0;

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
        this->printMessage();
        callback_();
    }

    size_t getMinReqExeTimes(void) const override {
        return 1;
    }

private:
    Callable callback_;
};

template<typename... Args>
class MultiArgCallableTask final : public Task {
public:
    typedef std::function<void(Args...)> Callable;
    typedef std::tuple<Args...> TestCase;

    MultiArgCallableTask(
        TaskName name,
        const std::string& msg,
        Callable callback,
        const std::vector<TestCase>& test_cases
    ) : Task(name, msg),
        callback_(callback),
        test_cases_(test_cases) {}

    void operator() (void) override {
        this->printMessage(test_cases_[idx_]);
        std::apply(callback_, test_cases_[idx_]);
        idx_++;
        if (idx_ == test_cases_.size()) idx_ = 0;
    }

    void printMessage(const TestCase& test_case) const {
        auto format = [&](Args... args) {
            return dyna_format(msg_, args...);
        };
        std::cout << std::apply(format, test_case) << std::endl;
    }

    size_t getMinReqExeTimes(void) const override {
        return test_cases_.size();
    }

private:
    Callable callback_;
    std::vector<TestCase> test_cases_;
    size_t idx_ = 0;
};


class TaskManager {
public:
    bool addTask(CallableTask& task);

    template<typename... Args>
    bool addTask(MultiArgCallableTask<Args...>& task) {
        tasks_.emplace_back(new MultiArgCallableTask(task));
        return true;
    }

    void runAll(void);

private:
    std::vector<TaskUniquePtr> tasks_;
};

}  // namespace: cppbdd

#endif  // TASK_MANAGER_HPP
