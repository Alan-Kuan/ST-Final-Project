#include "cppbdd.hpp"

std::vector<Scenario> scenarios;

void Scenario_(const std::string& fmt_str, std::function<void(void)> callback) {
    scenarios.emplace_back(fmt_str, callback);
}
