#ifndef CPPBDD_HPP
#define CPPBDD_HPP

#include <string>
#include <functional>

#include "cppbdd/TaskManager.hpp"

namespace cppbdd {

extern TaskManager scenario_manager;

void Scenario(const std::string& msg, CallableTask::Callable callback);
void Given(const std::string& msg, CallableTask::Callable callback, TaskManager& stmt_manager);
void When(const std::string& msg, CallableTask::Callable callback, TaskManager& stmt_manager);
void Then(const std::string& msg, CallableTask::Callable callback, TaskManager& stmt_manager);
void And(const std::string& msg, CallableTask::Callable callback, TaskManager& stmt_manager);

template<typename... Args>
void Given(
    const std::string& msg,
    typename MultiArgCallableTask<Args...>::Callable callback,
    const std::vector<std::tuple<Args...>>& test_cases,
    TaskManager& stmt_manager
) {
    auto task = new MultiArgCallableTask<Args...>(TaskName::GIVEN, msg, callback, test_cases);
    stmt_manager.addTask(task);
}

template<typename... Args>
void When(
    const std::string& msg,
    typename MultiArgCallableTask<Args...>::Callable callback,
    const std::vector<std::tuple<Args...>>& test_cases,
    TaskManager& stmt_manager
) {
    auto task = new MultiArgCallableTask<Args...>(TaskName::WHEN, msg, callback, test_cases);
    stmt_manager.addTask(task);
}

template<typename... Args>
void Then(
    const std::string& msg,
    typename MultiArgCallableTask<Args...>::Callable callback,
    const std::vector<std::tuple<Args...>>& test_cases,
    TaskManager& stmt_manager
) {
    auto task = new MultiArgCallableTask<Args...>(TaskName::THEN, msg, callback, test_cases);
    stmt_manager.addTask(task);
}

template<typename... Args>
void And(
    const std::string& msg,
    typename MultiArgCallableTask<Args...>::Callable callback,
    const std::vector<std::tuple<Args...>>& test_cases,
    TaskManager& stmt_manager
) {
    auto task = new MultiArgCallableTask<Args...>(TaskName::AND, msg, callback, test_cases);
    stmt_manager.addTask(task);
}

void runTests(void);

}  // namespace: cppbdd

#endif  // CPPBDD_HPP
