#include <gtest/gtest.h>
#include <string>
#include "cppbdd/expect.hpp"

using namespace std;

TEST(Expect, ShowExpectedMessage_Bool) {
    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", true, false);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: true\n"
        "    - rhs: false\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_BoolInv) {
    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", false, true);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: false\n"
        "    - rhs: true\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_Char) {
    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", 'a', 'b');
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: 'a'\n"
        "    - rhs: 'b'\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_Int) {
    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", 0, -1);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: 0\n"
        "    - rhs: -1\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_Double) {
    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", 1.0, 3.14);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: 1\n"
        "    - rhs: 3.14\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_CharArr) {
    char a[] = "hello";
    char b[] = "world";

    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", a, b);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"world\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_ConstCharArr) {
    const char a[] = "hello";
    const char b[] = "world";

    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", a, b);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"world\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_CharPtr) {
    char a[] = "hello";
    char b[] = "world";
    char* x = a;
    char* y = b;

    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", x, y);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"world\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_ConstCharPtr) {
    char a[] = "hello";
    char b[] = "world";
    const char* x = a;
    const char* y = b;

    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", x, y);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"world\"\n";

    EXPECT_EQ(output, expected);
}

TEST(Expect, ShowExpectedMessage_String) {
    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", string("hello"), string("world"));
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: \"hello\"\n"
        "    - rhs: \"world\"\n";

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

TEST(Expect, ShowExpectedMessage_CustomClass) {
    CustomClass c1(0), c2(1);

    ::testing::internal::CaptureStdout();
    cppbdd::internal::ShowExpectedMessage("==", c1, c2);
    string output = ::testing::internal::GetCapturedStdout();

    string expected =
        "  - Failed!\n"
        "    Expect lhs == rhs\n"
        "    - lhs: C(0)\n"
        "    - rhs: C(1)\n";

    EXPECT_EQ(output, expected);
}
