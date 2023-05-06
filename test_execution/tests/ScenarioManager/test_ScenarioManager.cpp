#include <gtest/gtest.h>
#include <string>
#include "cppbdd/ScenarioManager.hpp"

TEST(TestExecution, addScenario) {
    cppbdd::ScenarioManager manager;

    bool ret = manager.addScenario("", []() {});

    EXPECT_TRUE(ret);
}

TEST(TestExecution, runAll) {
    int a = 0, b = 10, c = -2;
    cppbdd::ScenarioManager manager;
    manager.addScenario("a", [&]() { a++; });
    manager.addScenario("b", [&]() { b *= 2; });
    manager.addScenario("c", [&]() { c = 33; });

    ::testing::internal::CaptureStdout();
    bool ret = manager.runAll();
    std::string output = ::testing::internal::GetCapturedStdout();

    EXPECT_TRUE(ret);
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 20);
    EXPECT_EQ(c, 33);
    EXPECT_EQ(output, "Scenario: a\nScenario: b\nScenario: c\n");
}
