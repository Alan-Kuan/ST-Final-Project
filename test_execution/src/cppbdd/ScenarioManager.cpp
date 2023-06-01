#include "cppbdd/ScenarioManager.hpp"

namespace cppbdd {

void ScenarioTask::operator() (Context& context) {
    this->printMessage();
    callback_(context);
}

bool ScenarioManager::addScenario(ScenarioTask *const scenario) {
    if (!scenario) return false;
    scenarios_.emplace_back(scenario);
    return true;
}

void ScenarioManager::runAll(void) {
    for (const auto& scenario : scenarios_) {
        ScenarioTask::Context context;
        (*scenario)(context);
        stmt_manager_.runAll();
        stmt_manager_.clear();
    }
}

}  // namespace: cppbdd
