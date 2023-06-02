#include <gtest/gtest.h>
#include "cppbdd/scenario_manager.hpp"

using namespace std;

TEST(ScenarioTask, OperatorParenthesis) {
    cppbdd::ScenarioTask task("", [&](cppbdd::ScenarioTask::Context& context) {
        context["test"] = 1;
    });

    cppbdd::ScenarioTask::Context context;
    task(context);

    EXPECT_EQ(any_cast<int>(context["test"]), 1);
}
