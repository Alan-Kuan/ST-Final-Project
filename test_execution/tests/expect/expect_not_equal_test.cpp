#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectNotEqual_Passed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectNotEqual(0, 1);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectNotEqual_Failed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectNotEqual(0, 0);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs != rhs\n"
        "    - lhs: 0\n"
        "    - rhs: 0\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectNotEqual_CString_Less) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectNotEqual("hello", "world");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectNotEqual_CString_Equal) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectNotEqual("hello", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs != rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"hello\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectNotEqual_CString_Greater) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectNotEqual("world", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}
