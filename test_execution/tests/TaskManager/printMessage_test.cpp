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
        Case(cppbdd::TaskName::SCENARIO, "a scenario", "\nScenario: a scenario\n"),
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

typedef tuple<cppbdd::TaskName,
              string,
              tuple<bool, char, int, double, string>,
              string> CaseWithArgs;

class TestExecutionTaskPrintMessageFormatted
    : public ::testing::TestWithParam<CaseWithArgs> {};

INSTANTIATE_TEST_SUITE_P(
    AllTaskNamesWithArgs,
    TestExecutionTaskPrintMessageFormatted,
    ::testing::Values(
        CaseWithArgs(
            cppbdd::TaskName::SCENARIO,
            "a = {}, b = '{}', c = {}, d = {}, e = \"{}\"",
            tuple<bool, char, int, double, string>(true, 'x', 1, 3.14, "hi"),
            "\nScenario: a = true, b = 'x', c = 1, d = 3.14, e = \"hi\"\n"
        ),
        CaseWithArgs(
            cppbdd::TaskName::GIVEN,
            "a = {}, b = '{}', c = {}, d = {}, e = \"{}\"",
            tuple<bool, char, int, double, string>(false, 'y', 0, 3.14, "hi"),
            "Given a = false, b = 'y', c = 0, d = 3.14, e = \"hi\"\n"
        ),
        CaseWithArgs(
            cppbdd::TaskName::WHEN,
            "a = {}, b = '{}', c = {}, d = {}, e = \"{}\"",
            tuple<bool, char, int, double, string>(true, 'x', -1, 3.0, "hi"),
            "When a = true, b = 'x', c = -1, d = 3, e = \"hi\"\n"
        ),
        CaseWithArgs(
            cppbdd::TaskName::THEN,
            "a = {}, b = '{}', c = {}, d = {}, e = \"{}\"",
            tuple<bool, char, int, double, string>(true, 'x', 1, 3.14, ""),
            "Then a = true, b = 'x', c = 1, d = 3.14, e = \"\"\n"
        ),
        CaseWithArgs(
            cppbdd::TaskName::AND,
            "a = {}, b = '{}', c = {}, d = {}, e = \"{}\"",
            tuple<bool, char, int, double, string>(true, 'x', 1, 3.14, "hi"),
            "And a = true, b = 'x', c = 1, d = 3.14, e = \"hi\"\n"
        )
    )
);

TEST_P(TestExecutionTaskPrintMessageFormatted, printMessageFormatted) {
    auto params = GetParam();
    cppbdd::MultiArgCallableTask<bool, char, int, double, string> task(
        get<0>(params),
        get<1>(params),
        [](bool, char, int, double, string) {},
        vector<cppbdd::MultiArgCallableTask<bool, char, int, double, string>::TestCase> {
            get<2>(params)
        }
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, get<3>(params));
}
