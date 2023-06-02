#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectTrue_Passed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectTrue(true);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectTrue_Failed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectTrue(false);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: false\n"
        "    - rhs: true\n";

    EXPECT_EQ(output, expected);
}
