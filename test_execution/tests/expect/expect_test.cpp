#include <gtest/gtest.h>
#include <string>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ExpectPassed) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect(true, 0, 0);
    string output = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "  Passed!\n");
}

TEST(Expect, ExpectFailedBool) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, true, false);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: true\n"
        "  - Expected: false\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectFailedBoolRev) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, false, true);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: false\n"
        "  - Expected: true\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectFailedChar) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, 'a', 'b');
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: 'a'\n"
        "  - Expected: 'b'\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectFailedInt) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, 0, -1);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: 0\n"
        "  - Expected: -1\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectFailedDouble) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, 1.0, 3.14);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: 1\n"
        "  - Expected: 3.14\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectFailedCharPtr) {
    char a[] = "hello";
    char b[] = "world";

    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, a, b);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: \"hello\"\n"
        "  - Expected: \"world\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectFailedConstCharPtr) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, "hello", "world");
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: \"hello\"\n"
        "  - Expected: \"world\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ExpectFailedString) {
    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, string("hello"), string("world"));
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: \"hello\"\n"
        "  - Expected: \"world\"\n";

    EXPECT_EQ(output, expected);
}

class CustomClass {
public:
    CustomClass(int x): x_(x) {}
    bool operator== (const CustomClass& other) const {
        return this->x_ == other.x_;
    }
    friend ostream& operator<< (ostream& os, const CustomClass& c);

private:
    int x_;
};

ostream& operator<< (ostream& os, const CustomClass& c) {
    return os << "C(" << c.x_ << ')';
}

TEST(Expect, ExpectFailedCustomClass) {
    CustomClass c1(0), c2(1);

    ::testing::internal::CaptureStdout();
    cppbdd::expect(false, c1, c2);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  Failed!\n"
        "  - Actual: C(0)\n"
        "  - Expected: C(1)\n";

    EXPECT_EQ(output, expected);
}
