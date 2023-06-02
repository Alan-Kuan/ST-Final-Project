#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectGreaterThanOrEqual_Passed_Greater) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThanOrEqual(1, 0);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectGreaterThanOrEqual_Passed_Equal) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThanOrEqual(0, 0);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectGreaterThanOrEqual_Failed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThanOrEqual(0, 1);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs >= rhs\n"
        "    - lhs: 0\n"
        "    - rhs: 1\n";

    EXPECT_EQ(output, expected);
}
