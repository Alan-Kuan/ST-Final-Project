#include <gtest/gtest.h>
#include <vector>
#include "cppbdd/TaskManager.hpp"

using namespace std;

TEST(TestExecution, CallableTaskOperatorParenthesis) {
    int a = 0;
    cppbdd::CallableTask task(cppbdd::TaskName::SCENARIO, "", [&]() { a = 1; });

    task();

    EXPECT_EQ(a, 1);
}

TEST(TestExecution, MultiArgCallableTaskOperatorParenthesis) {
    vector<int> a;
    cppbdd::SingleArgCallableTask<int>task(
        cppbdd::TaskName::GIVEN,
        "a = {}",
        [&](int x) { a.push_back(x); },
        vector<int> {1, 2}
    );

    task();
    task();

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
}
