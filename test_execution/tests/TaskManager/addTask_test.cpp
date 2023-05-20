#include <gtest/gtest.h>
#include "cppbdd/TaskManager.hpp"

TEST(TestExecutionTaskManager, addTask) {
    cppbdd::TaskManager manager;

    auto task = new cppbdd::CallableTask(cppbdd::TaskName::GIVEN, "", [](void) {});
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}

TEST(TestExecutionTaskManager, addTaskMultiArg) {
    cppbdd::TaskManager manager;

    auto task = new cppbdd::MultiArgCallableTask<int>(
        cppbdd::TaskName::WHEN,
        "",
        [](int) {},
        std::vector<std::tuple<int>> { std::tuple<int>(0) }
    );
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}
