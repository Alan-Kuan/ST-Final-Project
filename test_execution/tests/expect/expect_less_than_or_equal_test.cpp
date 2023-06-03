#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectLessThanOrEqual_Less) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThanOrEqual(0, 1);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectLessThanOrEqual_Equal) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThanOrEqual(0, 0);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectLessThanOrEqual_Greater) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThanOrEqual(1, 0);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs <= rhs\n"
        "    - lhs: 1\n"
        "    - rhs: 0\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectLessThanOrEqual_CString_Less) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThanOrEqual("hello", "world");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectLessThanOrEqual_CString_Equal) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThanOrEqual("hello", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectLessThanOrEqual_CString_Greater) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThanOrEqual("world", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs <= rhs\n"
        "    - lhs: \"world\"\n"
        "    - rhs: \"hello\"\n";

    EXPECT_EQ(output, expected);
}
