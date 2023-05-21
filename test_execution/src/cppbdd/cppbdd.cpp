#include "cppbdd/cppbdd.hpp"

namespace cppbdd {

TaskManager scenario_manager;

void Title(const string& msg) {
    cout << msg << endl;
    cout << string(msg.length(), '-') << endl;
}

void Scenario(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::SCENARIO, msg, callback);
    scenario_manager.addTask(task);
}

void Given(const char* const msg, CallableTask::Callable callback, TaskManager& stmt_manager) {
    auto task = new CallableTask(TaskName::GIVEN, msg, callback);
    stmt_manager.addTask(task);
}

void When(const char* const msg, CallableTask::Callable callback, TaskManager& stmt_manager) {
    auto task = new CallableTask(TaskName::WHEN, msg, callback);
    stmt_manager.addTask(task);
}

void Then(const char* const msg, CallableTask::Callable callback, TaskManager& stmt_manager) {
    auto task = new CallableTask(TaskName::THEN, msg, callback);
    stmt_manager.addTask(task);
}

void And(const char* const msg, CallableTask::Callable callback, TaskManager& stmt_manager) {
    auto task = new CallableTask(TaskName::AND, msg, callback);
    stmt_manager.addTask(task);
}

void runTests(void) {
    scenario_manager.runAll();
}

}  // namespace: cppbdd
