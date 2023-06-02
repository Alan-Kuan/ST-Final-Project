#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectGreaterThan_Passed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThan(1, 0);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectGreaterThan_Failed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThan(0, 1);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs > rhs\n"
        "    - lhs: 0\n"
        "    - rhs: 1\n";

    EXPECT_EQ(output, expected);
}
