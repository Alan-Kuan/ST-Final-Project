#include <gtest/gtest.h>
#include <tuple>
#include <vector>
#include <string>
#include "cppbdd/TaskManager.hpp"

using namespace std;

typedef tuple<cppbdd::TaskName, string, string> Case;

class TestExecutionTask
    : public ::testing::TestWithParam<Case> {};

INSTANTIATE_TEST_SUITE_P(
    AllTaskNames,
    TestExecutionTask,
    ::testing::Values(
        Case(cppbdd::TaskName::SCENARIO, "a scenario", "\nScenario: a scenario\n"),
        Case(cppbdd::TaskName::GIVEN, "a given statement", "\n  Given a given statement\n"),
        Case(cppbdd::TaskName::WHEN, "a when statement", "  When a when statement\n"),
        Case(cppbdd::TaskName::THEN, "a then statement", "  Then a then statement\n"),
        Case(cppbdd::TaskName::AND, "an and statement", "  And an and statement\n")
    )
);

TEST_P(TestExecutionTask, printMessage) {
    auto params = GetParam();
    cppbdd::CallableTask task(get<0>(params), get<1>(params), []() {});

    ::testing::internal::CaptureStdout();
    task.printMessage();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, get<2>(params));
}

TEST(TestExecutionSingleArgCallableTask, printMessageWithBool) {
    cppbdd::SingleArgCallableTask<bool> task(
        cppbdd::TaskName::SCENARIO,
        "a = {}",
        [](bool) {},
        vector<bool> {true}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\nScenario: a = true\n");
}

TEST(TestExecutionSingleArgCallableTask, printMessageWithChar) {
    cppbdd::SingleArgCallableTask<char> task(
        cppbdd::TaskName::GIVEN,
        "b = '{}'",
        [](char) {},
        vector<char> {'x'}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\n  Given b = 'x'\n");
}

TEST(TestExecutionSingleArgCallableTask, printMessageWithInt) {
    cppbdd::SingleArgCallableTask<int> task(
        cppbdd::TaskName::WHEN,
        "c = {}",
        [](int) {},
        vector<int> {1}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  When c = 1\n");
}

TEST(TestExecutionSingleArgCallableTask, printMessageWithDouble) {
    cppbdd::SingleArgCallableTask<double> task(
        cppbdd::TaskName::THEN,
        "d = {}",
        [](double) {},
        vector<double> {3.14}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  Then d = 3.14\n");
}

TEST(TestExecutionSingleArgCallableTask, printMessageWithString) {
    cppbdd::SingleArgCallableTask<string> task(
        cppbdd::TaskName::AND,
        "e = \"{}\"",
        [](string) {},
        vector<string> {"hi"}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  And e = \"hi\"\n");
}
