#include <gtest/gtest.h>
#include "cppbdd/TaskManager.hpp"

TEST(TestExecutionTaskManager, runAll) {
    int a, b;
    bool res = false;
    cppbdd::TaskManager manager;
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
