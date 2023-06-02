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

TEST(Expect, ExpectLessThan_CString_Less) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThan("hello", "world");
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  - Passed!\n");
}

TEST(Expect, ExpectLessThan_CString_Equal) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThan("hello", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs < rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"hello\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectLessThan_CString_Greater) {
    ::testing::internal::CaptureStdout();
    cppbdd::ExpectLessThan("world", "hello");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs < rhs\n"
        "    - lhs: \"world\"\n"
        "    - rhs: \"hello\"\n";

    EXPECT_EQ(output, expected);
}
