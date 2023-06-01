#include <gtest/gtest.h>
#include <string>
#include "cppbdd/cppbdd.hpp"

using namespace std;

TEST(Cppbdd, UserStory) {
    ::testing::internal::CaptureStdout();
    cppbdd::UserStory("As a user,", "I want to ooo,", "so that I can xxx.");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "As a user,\nI want to ooo,\nso that I can xxx.\n");
}
