#include <gtest/gtest.h>
#include <string>
#include "cppbdd/cppbdd.hpp"

using namespace std;

TEST(Cppbdd, Title) {
    ::testing::internal::CaptureStdout();
    cppbdd::Title("title");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "title\n"
        "-----\n";

    EXPECT_EQ(output, expected);
}
