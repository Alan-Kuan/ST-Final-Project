#include <gtest/gtest.h>
#include <tuple>
#include "cppbdd/TaskManager.hpp"

class TestExecutionTaskPrintMessage
    : public ::testing::TestWithParam<std::tuple<cppbdd::TaskName, std::string, std::string>> {};

INSTANTIATE_TEST_SUITE_P(
    AllTaskNames,
    TestExecutionTaskPrintMessage,
    ::testing::Combine(
        ::testing::Values(
            cppbdd::TaskName::SCENARIO,
            cppbdd::TaskName::GIVEN,
            cppbdd::TaskName::WHEN,
            cppbdd::TaskName::THEN,
            cppbdd::TaskName::AND
        ),
        ::testing::Values(
            "a scenario",
            "a given statement",
            "a when statement",
            "a then statement",
            "an and statement"
        ),
        ::testing::Values(
            "Scenario: a scenario",
            "Given a given statement",
            "When a when statement",
            "Then a then statement",
            "And an and statement"
        )
    )
);

TEST_P(TestExecutionTaskPrintMessage, printMessage) {
    auto params = GetParam();
    cppbdd::Task task(std::get<0>(params), std::get<1>(params));

    ::testing::internal::CaptureStdout();
    task.printMessage();
    std::string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, std::get<2>(params));
}
