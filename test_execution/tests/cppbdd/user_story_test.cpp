#include <gtest/gtest.h>
#include <string>
#include "cppbdd/cppbdd.hpp"

using namespace std;

TEST(Cppbdd, UserStory) {
    ::testing::internal::CaptureStdout();
    cppbdd::UserStory("As a user,", "I want to ooo,", "so that I can xxx.");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "As a user,\n"
        "I want to ooo,\n"
        "so that I can xxx.\n";
    
    EXPECT_EQ(output, expected);
}
