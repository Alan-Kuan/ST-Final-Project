#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectLessThan_Passed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThan(0, 1);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectLessThan_Failed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThan(1, 0);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs < rhs\n"
        "    - lhs: 1\n"
        "    - rhs: 0\n";

    EXPECT_EQ(output, expected);
}
