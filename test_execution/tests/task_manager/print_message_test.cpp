#include <gtest/gtest.h>
#include <tuple>
#include <vector>
#include <string>
#include "cppbdd/task_manager.hpp"

using namespace std;

typedef tuple<cppbdd::TaskName, string, string> Case;

class Task: public ::testing::TestWithParam<Case> {};

INSTANTIATE_TEST_SUITE_P(
    AllTaskNames,
    Task,
    ::testing::Values(
        Case(cppbdd::TaskName::kScenario, "a scenario", "\nScenario: a scenario\n"),
        Case(cppbdd::TaskName::kGiven, "a given statement", "\n  Given a given statement\n"),
        Case(cppbdd::TaskName::kWhen, "a when statement", "  When a when statement\n"),
        Case(cppbdd::TaskName::kThen, "a then statement", "  Then a then statement\n"),
        Case(cppbdd::TaskName::kAnd, "an and statement", "  And an and statement\n")
    )
);

TEST_P(Task, PrintMessage) {
    auto params = GetParam();
    cppbdd::CallableTask task(get<0>(params), get<1>(params), []() {});

    ::testing::internal::CaptureStdout();
    task.PrintMessage();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, get<2>(params));
}

TEST(SingleArgCallableTask, PrintMessage_Bool) {
    cppbdd::SingleArgCallableTask<bool> task(
        cppbdd::TaskName::kScenario,
        "a = {}",
        [](bool) {},
        vector<bool> {true}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\nScenario: a = true\n");
}

TEST(SingleArgCallableTask, PrintMessage_Char) {
    cppbdd::SingleArgCallableTask<char> task(
        cppbdd::TaskName::kGiven,
        "b = '{}'",
        [](char) {},
        vector<char> {'x'}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\n  Given b = 'x'\n");
}

TEST(SingleArgCallableTask, PrintMessage_Int) {
    cppbdd::SingleArgCallableTask<int> task(
        cppbdd::TaskName::kWhen,
        "c = {}",
        [](int) {},
        vector<int> {1}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  When c = 1\n");
}

TEST(SingleArgCallableTask, PrintMessage_Double) {
    cppbdd::SingleArgCallableTask<double> task(
        cppbdd::TaskName::kThen,
        "d = {}",
        [](double) {},
        vector<double> {3.14}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  Then d = 3.14\n");
}

TEST(SingleArgCallableTask, PrintMessage_String) {
    cppbdd::SingleArgCallableTask<string> task(
        cppbdd::TaskName::kAnd,
        "e = \"{}\"",
        [](string) {},
        vector<string> {"hi"}
    );

    ::testing::internal::CaptureStdout();
    task();
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  And e = \"hi\"\n");
}
