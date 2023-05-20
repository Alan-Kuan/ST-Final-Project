#ifndef CPPBDD_HPP
#define CPPBDD_HPP

#include <iostream>
#include <string>
#include <functional>

#include "cppbdd/TaskManager.hpp"

namespace cppbdd {

using namespace std;

extern TaskManager scenario_manager;

void Scenario(char* const msg, CallableTask::Callable callback);
void Given(char* const msg, CallableTask::Callable callback, TaskManager& stmt_manager);
void When(char* const msg, CallableTask::Callable callback, TaskManager& stmt_manager);
void Then(char* const msg, CallableTask::Callable callback, TaskManager& stmt_manager);
void And(char* const msg, CallableTask::Callable callback, TaskManager& stmt_manager);

template<typename... Args>
void Given(
    char* const msg,
    typename MultiArgCallableTask<Args...>::Callable callback,
    const vector<tuple<Args...>>& test_cases,
    TaskManager& stmt_manager
) {
    auto task = new MultiArgCallableTask<Args...>(TaskName::GIVEN, msg, callback, test_cases);
    stmt_manager.addTask(task);
}

template<typename... Args>
void When(
    char* const msg,
    typename MultiArgCallableTask<Args...>::Callable callback,
    const vector<tuple<Args...>>& test_cases,
    TaskManager& stmt_manager
) {
    auto task = new MultiArgCallableTask<Args...>(TaskName::WHEN, msg, callback, test_cases);
    stmt_manager.addTask(task);
}

template<typename... Args>
void Then(
    char* const msg,
    typename MultiArgCallableTask<Args...>::Callable callback,
    const vector<tuple<Args...>>& test_cases,
    TaskManager& stmt_manager
) {
    auto task = new MultiArgCallableTask<Args...>(TaskName::THEN, msg, callback, test_cases);
    stmt_manager.addTask(task);
}

template<typename... Args>
void And(
    char* const msg,
    typename MultiArgCallableTask<Args...>::Callable callback,
    const vector<tuple<Args...>>& test_cases,
    TaskManager& stmt_manager
) {
    auto task = new MultiArgCallableTask<Args...>(TaskName::AND, msg, callback, test_cases);
    stmt_manager.addTask(task);
}

void runTests(void);

}  // namespace: cppbdd

#endif  // CPPBDD_HPP
