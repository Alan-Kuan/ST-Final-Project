#include <gtest/gtest.h>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectEqual_Passed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectEqual(0, 0);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectEqual_Failed) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectEqual(0, 1);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: 0\n"
        "    - rhs: 1\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectEqual_CString_Less) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectEqual("hello", "world");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"world\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectEqual_CString_Equal) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectEqual("hello", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectEqual_CString_Greater) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectEqual("world", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: \"world\"\n"
        "    - rhs: \"hello\"\n";

    EXPECT_EQ(output, expected);
}
