#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectNe_Passed) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect_ne(0, 1);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectNe_Failed) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect_ne(0, 0);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs != rhs\n"
        "    - lhs: 0\n"
        "    - rhs: 0\n";

    EXPECT_EQ(output, expected);
}
