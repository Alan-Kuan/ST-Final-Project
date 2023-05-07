#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <iostream>

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

protected:
    static std::array<std::string, 5> task_names_;
    TaskName name_;
    std::string msg_;
};

typedef std::shared_ptr<Task> TaskPtr;


class CallableTask final : public Task {
public:
    typedef std::function<void(void)>Callable;

    CallableTask(TaskName name, const std::string& msg, Callable callback)
        : Task(name, msg), callback_(callback) {}

    void operator() (void) override { callback_(); }

private:
    Callable callback_;
};

template<typename... Args>
class MultiArgsCallableTask final : public Task {
public:
    typedef std::function<void(Args...)> Callable;
    typedef std::tuple<Args...> TestCase;

    MultiArgsCallableTask(
        TaskName name,
        const std::string& msg,
        Callable callback,
        const std::vector<TestCase>& test_cases
    ) : Task(name, msg),
        callback_(callback),
        test_cases_(test_cases) {}

    void operator() (void) override {
        std::apply(callback_, test_cases_[idx_++]);
        if (idx_ == test_cases_.size()) idx_ = 0;
    }

private:
    Callable callback_;
    std::vector<TestCase>test_cases_;
    size_t idx_ = 0;
};


class TaskManager {
public:
    TaskManager(size_t test_case_num)
        : test_case_num_(test_case_num) {}

    bool addTask(CallableTask& task);

    template<typename... Args>
    bool addTask(MultiArgsCallableTask<Args...>& task) {
        tasks_.emplace_back(new MultiArgsCallableTask(task));
        return true;
    }

    void runAll(void);

private:
    std::vector<TaskPtr> tasks_;
    size_t test_case_num_;
};

}  // namespace: cppbdd

#endif  // TASK_MANAGER_HPP
