#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectFalse_Passed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectFalse(false);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectFalse_Failed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectFalse(true);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: true\n"
        "    - rhs: false\n";

    EXPECT_EQ(output, expected);
}
