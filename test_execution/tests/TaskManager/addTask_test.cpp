#include <gtest/gtest.h>
#include "cppbdd/TaskManager.hpp"

TEST(TestExecutionTaskManager, addTask) {
    cppbdd::TaskManager manager(1);

    cppbdd::CallableTask task(cppbdd::TaskName::GIVEN, "", [](void) {});
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}

TEST(TestExecutionTaskManager, addTaskMultiArg) {
    cppbdd::TaskManager manager(1);

    cppbdd::MultiArgCallableTask<int> task(
        cppbdd::TaskName::WHEN,
        "",
        [](int) {},
        std::vector<std::tuple<int>> { std::tuple<int>(0) }
    );
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}
