#ifndef EXPECT_HPP
#define EXPECT_HPP

#include <iostream>
#include <sstream>
#include <type_traits>

namespace cppbdd {

using namespace std;

extern int TOTAL_TESTS;
extern int PASSED_TESTS;

void showResults(void);

template<typename T>
static void showExpectedMessage(const string& op, const T& lhs, const T& rhs) {
    stringstream lhs_ss, rhs_ss;

    cout << "  - Failed!" << endl;
    cout << "    Expect lhs " << op << " rhs" << endl;

    if constexpr (is_same_v<T, bool>) {
        lhs_ss << (lhs ? "true" : "false");
        rhs_ss << (rhs ? "true" : "false");
    } else if constexpr (is_same_v<T, char>) {
        lhs_ss << '\'' << lhs << '\'';
        rhs_ss << '\'' << rhs << '\'';
    } else if constexpr (is_same_v<T, char*> || is_same_v<T, const char*> || is_same_v<T, string>) {
        lhs_ss << '"' << lhs << '"';
        rhs_ss << '"' << rhs << '"';
    } else {
        lhs_ss << lhs;
        rhs_ss << rhs;
    }

    cout << "    - lhs: " << lhs_ss.str() << endl;
    cout << "    - rhs: " << rhs_ss.str() << endl;
}

bool expect(bool condition);

void expect_true(bool actual);
void expect_false(bool actual);

template<typename T>
void expect_eq(T lhs, T rhs) {
    if (expect(lhs == rhs)) return;
    showExpectedMessage("==", lhs, rhs);
}

template<typename T>
void expect_ne(T lhs, T rhs) {
    if (expect(lhs != rhs)) return;
    showExpectedMessage("!=", lhs, rhs);
}

template<typename T>
void expect_lt(T lhs, T rhs) {
    if (expect(lhs < rhs)) return;
    showExpectedMessage("<", lhs, rhs);
}

template<typename T>
void expect_le(T lhs, T rhs) {
    if (expect(lhs <= rhs)) return;
    showExpectedMessage("<=", lhs, rhs);
}

template<typename T>
void expect_gt(T lhs, T rhs) {
    if (expect(lhs > rhs)) return;
    showExpectedMessage(">", lhs, rhs);
}

template<typename T>
void expect_ge(T lhs, T rhs) {
    if (expect(lhs >= rhs)) return;
    showExpectedMessage(">=", lhs, rhs);
}

}  // namespace cppbdd

#endif  // EXPECT_HPP
