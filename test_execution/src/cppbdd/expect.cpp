#include "cppbdd/expect.hpp"

namespace cppbdd {

int TOTAL_TESTS = 0;
int PASSED_TESTS = 0;

void showResults(void) {
    cout << endl << string(20, '=') << endl;
    cout << "Passed: " << PASSED_TESTS << '/' << TOTAL_TESTS << endl;
}

void expect_true(bool actual) {
    expect(actual == true, actual, true);
}

void expect_false(bool actual) {
    expect(actual == false, actual, false);
}

}  // namespace cppbdd
