#include <gtest/gtest.h>
#include <vector>
#include "cppbdd/task_manager.hpp"

using namespace std;

TEST(CallableTask, OperatorParenthesis) {
    int a = 0;
    cppbdd::CallableTask task(cppbdd::TaskName::kScenario, "", [&]() { a = 1; });

    task();

    EXPECT_EQ(a, 1);
}

TEST(SingleArgCallableTask, OperatorParenthesis) {
    vector<int> a;
    cppbdd::SingleArgCallableTask<int>task(
        cppbdd::TaskName::kGiven,
        "a = {}",
        [&](int x) { a.push_back(x); },
        vector<int> {1, 2}
    );

    task();
    task();

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
}
