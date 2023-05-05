#include <gtest/gtest.h>
#include <cstdio>
#include "cppbdd/ScenarioManager.hpp"

TEST(TestExecution, addScenario) {
    cppbdd::ScenarioManager manager;
    bool ret = manager.addScenario("", []() {});
    EXPECT_TRUE(ret);
}

TEST(TestExecution, runAll) {
    cppbdd::ScenarioManager manager;
    manager.addScenario("", []() {});
    manager.addScenario("hello", []() {});
    manager.addScenario("", []() { printf("world\n"); });
    bool ret = manager.runAll();
    EXPECT_TRUE(ret);
}
