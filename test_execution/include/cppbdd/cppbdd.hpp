#ifndef CPPBDD_CPPBDD_HPP_
#define CPPBDD_CPPBDD_HPP_

#include <iostream>
#include <string>
#include <functional>

#include "cppbdd/task_manager.hpp"
#include "cppbdd/scenario_manager.hpp"

namespace cppbdd {

namespace internal {
    extern ScenarioManager scenario_manager;
}

void Title(const std::string& msg);

template<std::same_as<const char*>... Args>
void UserStory(Args... msgs) {
    for (const std::string& msg : {msgs...}) {
        std::cout << msg << std::endl;
    }
}

void Scenario(const char* const msg, ScenarioTask::Callable callback);
void Given(const char* const msg, CallableTask::Callable callback);
void When(const char* const msg, CallableTask::Callable callback);
void Then(const char* const msg, CallableTask::Callable callback);
void And(const char* const msg, CallableTask::Callable callback);

template<typename T>
void Given(
    const char* const msg,
    typename SingleArgCallableTask<T>::Callable callback,
    const std::vector<T>& test_cases
) {
    auto task = new SingleArgCallableTask<T>(TaskName::kGiven, msg, callback, test_cases);
    internal::scenario_manager.AddTaskToCurrStmtManager(task);
}

template<typename T>
void When(
    const char* const msg,
    typename SingleArgCallableTask<T>::Callable callback,
    const std::vector<T>& test_cases
) {
    auto task = new SingleArgCallableTask<T>(TaskName::kWhen, msg, callback, test_cases);
    internal::scenario_manager.AddTaskToCurrStmtManager(task);
}

template<typename T>
void Then(
    const char* const msg,
    typename SingleArgCallableTask<T>::Callable callback,
    const std::vector<T>& test_cases
) {
    auto task = new SingleArgCallableTask<T>(TaskName::kThen, msg, callback, test_cases);
    internal::scenario_manager.AddTaskToCurrStmtManager(task);
}

template<typename T>
void And(
    const char* const msg,
    typename SingleArgCallableTask<T>::Callable callback,
    const std::vector<T>& test_cases
) {
    auto task = new SingleArgCallableTask<T>(TaskName::kAnd, msg, callback, test_cases);
    internal::scenario_manager.AddTaskToCurrStmtManager(task);
}

void RunTests(void);

}  // namespace cppbdd

#endif  // CPPBDD_CPPBDD_HPP_
