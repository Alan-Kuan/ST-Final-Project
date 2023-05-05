#ifndef SCENARIO_MANAGER_HPP
#define SCENARIO_MANAGER_HPP

#include <functional>
#include <string>
#include <vector>

namespace cppbdd {

struct Scenario {
    typedef std::function<void(void)> Callback;

    std::string msg;
    Callback callback;
};

class ScenarioManager {
public:
    bool addScenario(const std::string& msg, Scenario::Callback callback);
    bool runAll(void);

private:
    std::vector<Scenario> scenarios;
};

}  // namespace: cppbdd

#endif  // SCENARIO_MANAGER_HPP
