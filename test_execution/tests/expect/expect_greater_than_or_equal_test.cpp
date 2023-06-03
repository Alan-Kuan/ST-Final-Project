#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectGreaterThanOrEqual_Less) {
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

TEST(Expect, ExpectGreaterThanOrEqual_Equal) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThanOrEqual(0, 0);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectGreaterThanOrEqual_Greater) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThanOrEqual(1, 0);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectGreaterThanOrEqual_CString_Less) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThanOrEqual("hello", "world");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs >= rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"world\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectGreaterThanOrEqual_CString_Equal) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThanOrEqual("hello", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectGreaterThanOrEqual_CString_Greater) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectGreaterThanOrEqual("world", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}
