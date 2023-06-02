#ifndef EXPECT_HPP
#define EXPECT_HPP

#include <iostream>
#include <type_traits>

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

        if (is_same<T, bool>()) {
            cout << "  - Actual: " << (actual ? "true" : "false") << endl;
            cout << "  - Expected: " << (expected ? "true" : "false") << endl;
        } else if (is_same<T, char>()) {
            cout << "  - Actual: " << '\'' << actual << '\'' << endl;
            cout << "  - Expected: " << '\'' << expected << '\'' << endl;
        } else if (is_same<T, char*>() || 
                   is_same<T, const char*>() ||
                   is_same<T, char* const>() ||
                   is_same<T, const char* const>() ||
                   is_same<T, string>()) {
            cout << "  - Actual: " << '"' << actual << '"' << endl;
            cout << "  - Expected: " << '"' << expected << '"' << endl;
        } else {
            cout << "  - Actual: " << actual << endl;
            cout << "  - Expected: " << expected << endl;
        }
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
