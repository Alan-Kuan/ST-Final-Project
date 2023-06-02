#include "cppbdd/expect.hpp"

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

}  // namespace cppbdd
