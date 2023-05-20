#include "cppbdd/cppbdd.hpp"

namespace cppbdd {

TaskManager scenario_manager;

void Scenario(const std::string& msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::SCENARIO, msg, callback);
    scenario_manager.addTask(task);
}

void Given(const std::string& msg, CallableTask::Callable callback, TaskManager& stmt_manager) {
    auto task = new CallableTask(TaskName::GIVEN, msg, callback);
    stmt_manager.addTask(task);
}

void When(const std::string& msg, CallableTask::Callable callback, TaskManager& stmt_manager) {
    auto task = new CallableTask(TaskName::WHEN, msg, callback);
    stmt_manager.addTask(task);
}

void Then(const std::string& msg, CallableTask::Callable callback, TaskManager& stmt_manager) {
    auto task = new CallableTask(TaskName::THEN, msg, callback);
    stmt_manager.addTask(task);
}

void And(const std::string& msg, CallableTask::Callable callback, TaskManager& stmt_manager) {
    auto task = new CallableTask(TaskName::AND, msg, callback);
    stmt_manager.addTask(task);
}

void runTests(void) {
    scenario_manager.runAll();
}

}  // namespace: cppbdd
