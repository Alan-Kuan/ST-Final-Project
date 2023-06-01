#include <gtest/gtest.h>
#include "cppbdd/ScenarioManager.hpp"

using namespace std;

TEST(ScenarioManager, runAll) {
    int a = 0, b = 0;
    cppbdd::ScenarioManager manager;
    auto scenario1 = new cppbdd::ScenarioTask("a = 0", [&](cppbdd::ScenarioTask::Context&) {
        a = 1;
    });
    auto scenario2 = new cppbdd::ScenarioTask("b = \"hello, world!\"", [&](cppbdd::ScenarioTask::Context&) {
        b = 2;
    });
    manager.addScenario(scenario1);
    manager.addScenario(scenario2);

    manager.runAll();

    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 2);
}
