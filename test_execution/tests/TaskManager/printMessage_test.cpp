#include <gtest/gtest.h>
#include <tuple>
#include "cppbdd/TaskManager.hpp"

typedef std::tuple<cppbdd::TaskName, std::string, std::string> Case;

class TestExecutionTaskPrintMessage
    : public ::testing::TestWithParam<Case> {};

INSTANTIATE_TEST_SUITE_P(
    AllTaskNames,
    TestExecutionTaskPrintMessage,
    ::testing::Values(
        Case(cppbdd::TaskName::SCENARIO, "a scenario", "Scenario: a scenario\n"),
        Case(cppbdd::TaskName::GIVEN, "a given statement", "Given a given statement\n"),
        Case(cppbdd::TaskName::WHEN, "a when statement", "When a when statement\n"),
        Case(cppbdd::TaskName::THEN, "a then statement", "Then a then statement\n"),
        Case(cppbdd::TaskName::AND, "an and statement", "And an and statement\n")
    )
);

TEST_P(TestExecutionTaskPrintMessage, printMessage) {
    auto params = GetParam();
    cppbdd::CallableTask task(std::get<0>(params), std::get<1>(params), []() {});

    ::testing::internal::CaptureStdout();
    task.printMessage();
    std::string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, std::get<2>(params));
}
