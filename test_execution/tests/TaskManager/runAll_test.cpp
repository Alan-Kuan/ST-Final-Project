#include <gtest/gtest.h>
#include <vector>
#include "cppbdd/TaskManager.hpp"

using namespace std;

TEST(TaskManager, runAll) {
    int a, b;
    bool res = false;
    cppbdd::TaskManager manager;
    auto given = new cppbdd::CallableTask(cppbdd::TaskName::GIVEN, "a = 0", [&](void) { a = 0; });
    auto when = new cppbdd::CallableTask(cppbdd::TaskName::WHEN, "let b = a + 1", [&](void) { b = a + 1; });
    auto then = new cppbdd::CallableTask(cppbdd::TaskName::THEN, "b = 1", [&](void) { res = (b == 1); });
    manager.addTask(given);
    manager.addTask(when);
    manager.addTask(then);

    manager.runAll();

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1);
    EXPECT_TRUE(res);
}

TEST(TaskManager, runAllSingleArg) {
    int a, b, c;
    bool res;
    cppbdd::TaskManager manager;
    auto given = new cppbdd::SingleArgCallableTask<int>(
        cppbdd::TaskName::GIVEN,
        "a = {}",
        [&](int x) { a = x; },
        vector<int> {1}
    );
    auto and_given = new cppbdd::SingleArgCallableTask<int>(
        cppbdd::TaskName::AND,
        "b = {}",
        [&](int x) { b = x; },
        vector<int> {3}
    );
    auto when = new cppbdd::CallableTask(
        cppbdd::TaskName::WHEN,
        "let c = a + b", [&](void) { c = a + b; }
    );
    auto then = new cppbdd::SingleArgCallableTask<int>(
        cppbdd::TaskName::THEN,
        "c = {}",
        [&](int x) { res = (c == x); },
        vector<int> {4}
    );
    manager.addTask(given);
    manager.addTask(and_given);
    manager.addTask(when);
    manager.addTask(then);

    manager.runAll();

    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 3);
    EXPECT_EQ(c, 4);
    EXPECT_TRUE(res);
}
