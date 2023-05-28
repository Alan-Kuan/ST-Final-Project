#include "cppbdd/cppbdd.hpp"

namespace cppbdd {

ScenarioManager SCENARIO_MANAGER;

void Title(const string& msg) {
    cout << msg << endl;
    cout << string(msg.length(), '-') << endl;
}

void Scenario(const char* const msg, ScenarioTask::Callable callback) {
    auto task = new ScenarioTask(msg, callback);
    SCENARIO_MANAGER.addScenario(task);
}

void Given(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::GIVEN, msg, callback);
    SCENARIO_MANAGER.addTaskToCurrStmtManager(task);
}

void When(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::WHEN, msg, callback);
    SCENARIO_MANAGER.addTaskToCurrStmtManager(task);
}

void Then(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::THEN, msg, callback);
    SCENARIO_MANAGER.addTaskToCurrStmtManager(task);
}

void And(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::AND, msg, callback);
    SCENARIO_MANAGER.addTaskToCurrStmtManager(task);
}

void runTests(void) {
    SCENARIO_MANAGER.runAll();
}

}  // namespace: cppbdd
