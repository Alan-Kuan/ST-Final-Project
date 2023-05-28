#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include "cppbdd/TaskManager.hpp"

using namespace std;

TEST(TestExecutionTaskManager, addTask) {
    cppbdd::TaskManager manager;

    auto task = new cppbdd::CallableTask(cppbdd::TaskName::GIVEN, "", [](void) {});
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}

TEST(TestExecutionTaskManager, addTaskMultiArg) {
    cppbdd::TaskManager manager;

    auto task = new cppbdd::SingleArgCallableTask<int>(
        cppbdd::TaskName::WHEN,
        "",
        [](int) {},
        vector<int> { 0 }
    );
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}
