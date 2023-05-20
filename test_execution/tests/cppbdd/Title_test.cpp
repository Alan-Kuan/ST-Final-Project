#include <gtest/gtest.h>
#include <string>
#include "cppbdd/cppbdd.hpp"

using namespace std;

TEST(TestExecutionCppbdd, Title) {
    ::testing::internal::CaptureStdout();
    cppbdd::Title("title");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "title\n-----\n");
}
