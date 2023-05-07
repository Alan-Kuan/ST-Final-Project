#include <gtest/gtest.h>
#include "cppbdd/TaskManager.hpp"

TEST(TestExecutionTaskManager, runAll) {
    int a, b;
    bool res = false;
    cppbdd::TaskManager manager(1);
    cppbdd::CallableTask given(cppbdd::TaskName::GIVEN, "a = 0", [&](void) { a = 0; });
    cppbdd::CallableTask when(cppbdd::TaskName::WHEN, "let b = a + 1", [&](void) { b = a + 1; });
    cppbdd::CallableTask then(cppbdd::TaskName::THEN, "b = 1", [&](void) { res = (b == 1); });
    manager.addTask(given);
    manager.addTask(when);
    manager.addTask(then);

    manager.runAll();

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1);
    EXPECT_TRUE(res);
}

TEST(TestExecutionTaskManager, runAllMultiArgs) {
    int a, b, c;
    bool res;
    cppbdd::TaskManager manager(1);
    cppbdd::MultiArgsCallableTask<int> given(
        cppbdd::TaskName::GIVEN,
        "a = {}",
        [&](int x) { a = x; },
        std::vector<cppbdd::MultiArgsCallableTask<int>::TestCase> {
            cppbdd::MultiArgsCallableTask<int>::TestCase(1),
        }
    );
    cppbdd::MultiArgsCallableTask<int> and_given(
        cppbdd::TaskName::AND,
        "b = {}",
        [&](int x) { b = x; },
        std::vector<cppbdd::MultiArgsCallableTask<int>::TestCase> {
            cppbdd::MultiArgsCallableTask<int>::TestCase(3),
        }
    );
    cppbdd::CallableTask when(
        cppbdd::TaskName::WHEN,
        "let c = a + b", [&](void) { c = a + b; }
    );
    cppbdd::MultiArgsCallableTask<int> then(
        cppbdd::TaskName::THEN,
        "c = {}",
        [&](int x) { res = (c == x); },
        std::vector<cppbdd::MultiArgsCallableTask<int>::TestCase> {
            cppbdd::MultiArgsCallableTask<int>::TestCase(4),
        }
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
