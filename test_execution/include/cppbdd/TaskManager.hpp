#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <array>
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

protected:
    static std::array<std::string, 5> task_names_;
    TaskName name_;
    std::string msg_;
};

typedef std::shared_ptr<Task> TaskPtr;


class CallableTask : public Task {
public:
    typedef std::function<void(void)>Callable;

    CallableTask(TaskName name, const std::string& msg, Callable callback)
        : Task(name, msg), callback_(callback) {}

    void operator() (void) { if (callback_) callback_(); }

private:
    Callable callback_;
};

template<typename... Args>
class MultiArgsCallableTask : public Task {
public:
    typedef std::function<void(Args...)>Callable;

    MultiArgsCallableTask(TaskName name, const std::string& msg, Callable callback)
        : Task(name, msg), callback_(callback) {}

    void operator() (Args... args) { if (callback_) callback_(args...); }

private:
    Callable callback_;
};


class TaskManager {
public:
    bool addTask(CallableTask& task);

    template<typename... Args>
    bool addTask(MultiArgsCallableTask<Args...>& task) {
        tasks_.emplace_back(new MultiArgsCallableTask(task));
        return true;
    }

    void runAll(void);

private:
    std::vector<TaskPtr> tasks_;
};

}  // namespace: cppbdd

#endif  // TASK_MANAGER_HPP
