#include "cppbdd/expect.hpp"

#include <cstring>
#include <iostream>

namespace cppbdd {

namespace internal {

int total_tests = 0;
int passed_tests = 0;

bool Expect(bool condition) {
    total_tests++;
    if (condition) {
        std::cout << "  - Passed!" << std::endl;
        passed_tests++;
    }
    return condition;
}

}  // namespace internal

void ShowResults(void) {
    std::cout << std::endl << std::string(20, '=') << std::endl;
    std::cout << "Passed: " << internal::passed_tests << '/';
    std::cout << internal::total_tests << std::endl;
}

void ExpectTrue(bool actual) {
    ExpectEqual(actual, true);
}

void ExpectFalse(bool actual) {
    ExpectEqual(actual, false);
}

void ExpectEqual(const char* lhs, const char* rhs) {
    if (internal::Expect(strcmp(lhs, rhs) == 0)) return;
    internal::ShowExpectation("==", lhs, rhs);
}

void ExpectNotEqual(const char* lhs, const char* rhs) {
    if (internal::Expect(strcmp(lhs, rhs) != 0)) return;
    internal::ShowExpectation("!=", lhs, rhs);
}

void ExpectLessThan(const char* lhs, const char* rhs) {
    if (internal::Expect(strcmp(lhs, rhs) < 0)) return;
    internal::ShowExpectation("<", lhs, rhs);
}

void ExpectLessThanOrEqual(const char* lhs, const char* rhs) {
    if (internal::Expect(strcmp(lhs, rhs) <= 0)) return;
    internal::ShowExpectation("<=", lhs, rhs);
}

void ExpectGreaterThan(const char* lhs, const char* rhs) {
    if (internal::Expect(strcmp(lhs, rhs) > 0)) return;
    internal::ShowExpectation(">", lhs, rhs);
}

void ExpectGreaterThanOrEqual(const char* lhs, const char* rhs) {
    if (internal::Expect(strcmp(lhs, rhs) >= 0)) return;
    internal::ShowExpectation(">=", lhs, rhs);
}

}  // namespace cppbdd
