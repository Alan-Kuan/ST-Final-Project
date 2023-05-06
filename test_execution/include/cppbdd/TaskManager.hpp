#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>

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

private:
    TaskName name_;
    std::string msg_;
};

typedef std::shared_ptr<Task> TaskPtr;


template<typename... Args>
class CallableTask : public Task {
public:
    typedef std::function<void(Args...)>Callable;

    CallableTask(Callable f)
        : f_(f) {}

    void operator() (Args... args) { if (f_) f_(args...); }

private:
    Callable f_;
};


class TaskManager {
public:
    template<typename T>
    bool addTask(const std::string& msg, const T& callback);
    void runAll(void);

private:
    std::vector<TaskPtr> tasks_;
};

}  // namespace: cppbdd

#endif  // TASK_MANAGER_HPP
