#include <gtest/gtest.h>
#include <vector>
#include "cppbdd/TaskManager.hpp"

using namespace std;

TEST(TaskManager, addTask) {
    cppbdd::TaskManager manager;

    auto task = new cppbdd::CallableTask(cppbdd::TaskName::GIVEN, "", [](void) {});
    bool ret = manager.addTask(task);

    EXPECT_TRUE(ret);
}

TEST(TaskManager, addTaskNull) {
    cppbdd::TaskManager manager;

    cppbdd::CallableTask* task = nullptr;
    bool ret = manager.addTask(task);

    EXPECT_FALSE(ret);
}

TEST(TaskManager, addTaskSingleArg) {
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

TEST(TaskManager, addTaskSingleArgNull) {
    cppbdd::TaskManager manager;

    cppbdd::SingleArgCallableTask<int>* task = nullptr;
    bool ret = manager.addTask(task);

    EXPECT_FALSE(ret);
}
