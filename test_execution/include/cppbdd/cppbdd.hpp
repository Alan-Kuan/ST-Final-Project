#ifndef CPPBDD_HPP
#define CPPBDD_HPP

#include <iostream>
#include <string>
#include <functional>

#include "cppbdd/TaskManager.hpp"
#include "cppbdd/ScenarioManager.hpp"

namespace cppbdd {

using namespace std;

extern ScenarioManager SCENARIO_MANAGER;

void Title(const string& msg);

template<same_as<const char*>... Args>
void UserStory(Args... msgs) {
    for (const string& msg : {msgs...}) {
        cout << msg << endl;
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
    const vector<T>& test_cases
) {
    auto task = new SingleArgCallableTask<T>(TaskName::GIVEN, msg, callback, test_cases);
    SCENARIO_MANAGER.addTaskToCurrStmtManager(task);
}

template<typename T>
void When(
    const char* const msg,
    typename SingleArgCallableTask<T>::Callable callback,
    const vector<T>& test_cases
) {
    auto task = new SingleArgCallableTask<T>(TaskName::WHEN, msg, callback, test_cases);
    SCENARIO_MANAGER.addTaskToCurrStmtManager(task);
}

template<typename T>
void Then(
    const char* const msg,
    typename SingleArgCallableTask<T>::Callable callback,
    const vector<T>& test_cases
) {
    auto task = new SingleArgCallableTask<T>(TaskName::THEN, msg, callback, test_cases);
    SCENARIO_MANAGER.addTaskToCurrStmtManager(task);
}

template<typename T>
void And(
    const char* const msg,
    typename SingleArgCallableTask<T>::Callable callback,
    const vector<T>& test_cases
) {
    auto task = new SingleArgCallableTask<T>(TaskName::AND, msg, callback, test_cases);
    SCENARIO_MANAGER.addTaskToCurrStmtManager(task);
}

void runTests(void);

}  // namespace cppbdd

#endif  // CPPBDD_HPP
