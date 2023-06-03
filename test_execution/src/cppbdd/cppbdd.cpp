#include "cppbdd/cppbdd.hpp"

namespace cppbdd {

namespace internal {
    ScenarioManager scenario_manager;
}

void Title(const std::string& msg) {
    std::cout << msg << std::endl;
    std::cout << std::string(msg.length(), '-') << std::endl;
}

void Scenario(const char* const msg, ScenarioTask::Callable callback) {
    auto task = new ScenarioTask(msg, callback);
    internal::scenario_manager.AddScenario(task);
}

void Given(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::kGiven, msg, callback);
    internal::scenario_manager.AddTaskToCurrStmtManager(task);
}

void When(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::kWhen, msg, callback);
    internal::scenario_manager.AddTaskToCurrStmtManager(task);
}

void Then(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::kThen, msg, callback);
    internal::scenario_manager.AddTaskToCurrStmtManager(task);
}

void And(const char* const msg, CallableTask::Callable callback) {
    auto task = new CallableTask(TaskName::kAnd, msg, callback);
    internal::scenario_manager.AddTaskToCurrStmtManager(task);
}

void RunTests(void) {
    internal::scenario_manager.RunAll();
}

}  // namespace cppbdd
