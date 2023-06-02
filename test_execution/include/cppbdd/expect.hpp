#ifndef EXPECT_HPP
#define EXPECT_HPP

#include <iostream>

namespace cppbdd {

using namespace std;

extern int TOTAL_TESTS;
extern int PASSED_TESTS;

void showResults(void);

template<typename T>
static void expect(bool condition, T actual, T expected) {
    if (condition) {
        cout << "  Passed!" << endl;
        PASSED_TESTS++;
    } else {
        cout << "  Failed!" << endl;
        cout << "  - Actual: " << actual << endl;
        cout << "  - Expected: " << expected << endl;
    }
    TOTAL_TESTS++;
}

void expect_true(bool actual);
void expect_false(bool actual);

template<typename T>
void expect_eq(T actual, T expected) {
    expect(actual == expected, actual, expected);
}

template<typename T>
void expect_ne(T actual, T expected) {
    expect(actual != expected, actual, expected);
}

template<typename T>
void expect_lt(T actual, T expected) {
    expect(actual < expected, actual, expected);
}

template<typename T>
void expect_le(T actual, T expected) {
    expect(actual <= expected, actual, expected);
}

template<typename T>
void expect_gt(T actual, T expected) {
    expect(actual > expected, actual, expected);
}

template<typename T>
void expect_ge(T actual, T expected) {
    expect(actual >= expected, actual, expected);
}

}  // namespace cppbdd

#endif  // EXPECT_HPP
