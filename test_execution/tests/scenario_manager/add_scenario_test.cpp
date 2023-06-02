#include <gtest/gtest.h>
#include "cppbdd/scenario_manager.hpp"

using namespace std;

TEST(ScenarioManager, AddScenario) {
    cppbdd::ScenarioManager manager;

    auto task = new cppbdd::ScenarioTask("", [](cppbdd::ScenarioTask::Context) {});
    bool ret = manager.AddScenario(task);

    EXPECT_TRUE(ret);
}

TEST(ScenarioManager, AddScenario_Null) {
    cppbdd::ScenarioManager manager;

    cppbdd::ScenarioTask* task = nullptr;
    bool ret = manager.AddScenario(task);

    EXPECT_FALSE(ret);
}
