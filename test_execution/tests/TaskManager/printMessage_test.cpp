#include <gtest/gtest.h>
#include <tuple>
#include <vector>
#include <string>
#include "cppbdd/TaskManager.hpp"

using namespace std;

typedef tuple<cppbdd::TaskName, string, string> Case;

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
    cppbdd::CallableTask task(get<0>(params), get<1>(params), []() {});

    ::testing::internal::CaptureStdout();
    task.printMessage();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, get<2>(params));
}

TEST(TestExecution, printMessageFormated) {
    cppbdd::MultiArgCallableTask<bool, char, int, double, string> task(
        cppbdd::TaskName::GIVEN,
        "a = {}, b = '{}', c = {}, d = {}, e = \"{}\"",
        [](bool, char, int, double, string) {},
        vector<cppbdd::MultiArgCallableTask<bool, char, int, double, string>::TestCase> {
            cppbdd::MultiArgCallableTask<bool, char, int, double, string>::TestCase(true, 'x', 1, 3.14, "hi")
        }
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "a = true, b = 'x', c = 1, d = 3.14, e = \"hi\"\n");
}
