#include "cppbdd/expect.hpp"

namespace cppbdd {

int TOTAL_TESTS = 0;
int PASSED_TESTS = 0;

void showResults(void) {
    cout << endl << string(20, '=') << endl;
    cout << "Passed: " << PASSED_TESTS << '/' << TOTAL_TESTS << endl;
}

bool expect(bool condition) {
    TOTAL_TESTS++;
    if (condition) {
        cout << "  - Passed!" << endl;
        PASSED_TESTS++;
    }
    return condition;
}

void expect_true(bool actual) {
    expect_eq(actual, true);
}

void expect_false(bool actual) {
    expect_eq(actual, false);
}

}  // namespace cppbdd
