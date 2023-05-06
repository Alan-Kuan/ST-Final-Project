#include "cppbdd/ScenarioManager.hpp"
#include <iostream>

namespace cppbdd {

bool ScenarioManager::addScenario(const std::string& msg, Scenario::Callback callback) {
    scenarios_.emplace_back(msg, callback);
    return true;
}

bool ScenarioManager::runAll(void) {
    for (const auto& scenario : scenarios_) {
        std::cout << "Scenario: " << scenario.msg << std::endl;
        scenario.callback();
    }
    return true;
}

}  // namespace: cppbdd
