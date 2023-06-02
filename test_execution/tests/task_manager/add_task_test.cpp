#include <gtest/gtest.h>
#include <vector>
#include "cppbdd/task_manager.hpp"

using namespace std;

TEST(TaskManager, AddTask) {
    cppbdd::TaskManager manager;

    auto task = new cppbdd::CallableTask(cppbdd::TaskName::kGiven, "", [](void) {});
    bool ret = manager.AddTask(task);

    EXPECT_TRUE(ret);
}

TEST(TaskManager, AddTask_Null) {
    cppbdd::TaskManager manager;

    cppbdd::CallableTask* task = nullptr;
    bool ret = manager.AddTask(task);

    EXPECT_FALSE(ret);
}

TEST(TaskManager, AddTask_SingleArg) {
    cppbdd::TaskManager manager;

    auto task = new cppbdd::SingleArgCallableTask<int>(
        cppbdd::TaskName::kWhen,
        "",
        [](int) {},
        vector<int> { 0 }
    );
    bool ret = manager.AddTask(task);

    EXPECT_TRUE(ret);
}

TEST(TaskManager, AddTask_SingleArg_Null) {
    cppbdd::TaskManager manager;

    cppbdd::SingleArgCallableTask<int>* task = nullptr;
    bool ret = manager.AddTask(task);

    EXPECT_FALSE(ret);
}
