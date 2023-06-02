#include <gtest/gtest.h>
#include "cppbdd/scenario_manager.hpp"

using namespace std;

TEST(ScenarioManager, RunAll) {
    int a = 0, b = 0;
    cppbdd::ScenarioManager manager;
    auto scenario1 = new cppbdd::ScenarioTask("a = 0", [&](cppbdd::ScenarioTask::Context&) {
        a = 1;
    });
    auto scenario2 = new cppbdd::ScenarioTask("b = \"hello, world!\"", [&](cppbdd::ScenarioTask::Context&) {
        b = 2;
    });
    manager.AddScenario(scenario1);
    manager.AddScenario(scenario2);

    manager.RunAll();

    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 2);
}
