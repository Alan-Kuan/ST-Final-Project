#include "cppbdd/scenario_manager.hpp"

namespace cppbdd {

void ScenarioTask::operator() (Context& context) {
    this->PrintMessage();
    callback_(context);
}

bool ScenarioManager::AddScenario(ScenarioTask* const scenario) {
    if (!scenario) return false;
    scenarios_.emplace_back(scenario);
    return true;
}

void ScenarioManager::RunAll(void) {
    for (const auto& scenario : scenarios_) {
        ScenarioTask::Context context;
        (*scenario)(context);
        stmt_manager_.RunAll();
        stmt_manager_.clear();
    }
}

}  // namespace cppbdd
