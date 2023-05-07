#include <gtest/gtest.h>
#include "cppbdd/TaskManager.hpp"

TEST(TestExecutionTaskManager, addTask) {
    cppbdd::TaskManager manager;

    cppbdd::CallableTask task(cppbdd::TaskName::GIVEN, "", [](void) {});
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}

TEST(TestExecutionTaskManager, addTaskMultiArgs) {
    cppbdd::TaskManager manager;

    cppbdd::MultiArgsCallableTask<int> task(cppbdd::TaskName::WHEN, "", [](int) {});
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}
