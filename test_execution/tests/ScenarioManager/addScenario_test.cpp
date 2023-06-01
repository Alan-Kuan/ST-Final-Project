#include <gtest/gtest.h>
#include "cppbdd/ScenarioManager.hpp"

using namespace std;

TEST(TestExecutionScenarioManager, addScenario) {
    cppbdd::ScenarioManager manager;

    auto task = new cppbdd::ScenarioTask("", [](cppbdd::ScenarioTask::Context) {});
    bool ret = manager.addScenario(task);

    EXPECT_TRUE(ret);
}

TEST(TestExecutionScenarioManager, addScenarioNull) {
    cppbdd::ScenarioManager manager;

    cppbdd::ScenarioTask* task = nullptr;
    bool ret = manager.addScenario(task);

    EXPECT_FALSE(ret);
}
