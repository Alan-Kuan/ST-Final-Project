#ifndef CPPBDD_EXPECT_HPP_
#define CPPBDD_EXPECT_HPP_

#include <iostream>
#include <sstream>
#include <type_traits>

namespace cppbdd {

namespace internal {

extern int total_tests;
extern int passed_tests;

bool Expect(bool condition);

template<typename T>
static void ShowExpectation(const std::string& op, const T& lhs, const T& rhs) {
    std::stringstream lhs_ss, rhs_ss;

    std::cout << "  - Failed!" << std::endl;
    std::cout << "    Expect lhs " << op << " rhs" << std::endl;

    if constexpr (std::is_same_v<T, bool>) {
        lhs_ss << (lhs ? "true" : "false");
        rhs_ss << (rhs ? "true" : "false");
    } else if constexpr (std::is_same_v<T, char>) {
        lhs_ss << '\'' << lhs << '\'';
        rhs_ss << '\'' << rhs << '\'';
    } else if constexpr (std::is_same_v<T, char*> || 
                         std::is_same_v<T, const char*> ||
                         (std::is_array_v<T> && std::is_same_v<std::remove_extent_t<T>, char>) ||
                         std::is_same_v<T, std::string>) {
        lhs_ss << '"' << lhs << '"';
        rhs_ss << '"' << rhs << '"';
    } else {
        lhs_ss << lhs;
        rhs_ss << rhs;
    }

    std::cout << "    - lhs: " << lhs_ss.str() << std::endl;
    std::cout << "    - rhs: " << rhs_ss.str() << std::endl;
}

}  // namespace internal

void ShowResults(void);

void ExpectTrue(bool actual);
void ExpectFalse(bool actual);

template<typename T>
void ExpectEqual(T lhs, T rhs) {
    if (internal::Expect(lhs == rhs)) return;
    internal::ShowExpectation("==", lhs, rhs);
}

template<typename T>
void ExpectNotEqual(T lhs, T rhs) {
    if (internal::Expect(lhs != rhs)) return;
    internal::ShowExpectation("!=", lhs, rhs);
}

template<typename T>
void ExpectLessThan(T lhs, T rhs) {
    if (internal::Expect(lhs < rhs)) return;
    internal::ShowExpectation("<", lhs, rhs);
}

template<typename T>
void ExpectLessThanOrEqual(T lhs, T rhs) {
    if (internal::Expect(lhs <= rhs)) return;
    internal::ShowExpectation("<=", lhs, rhs);
}

template<typename T>
void ExpectGreaterThan(T lhs, T rhs) {
    if (internal::Expect(lhs > rhs)) return;
    internal::ShowExpectation(">", lhs, rhs);
}

template<typename T>
void ExpectGreaterThanOrEqual(T lhs, T rhs) {
    if (internal::Expect(lhs >= rhs)) return;
    internal::ShowExpectation(">=", lhs, rhs);
}

// NOTE: C-string comparison should not compare the pointers directly
void ExpectEqual(const char* lhs, const char* rhs);
void ExpectNotEqual(const char* lhs, const char* rhs);
void ExpectLessThan(const char* lhs, const char* rhs);
void ExpectLessThanOrEqual(const char* lhs, const char* rhs);
void ExpectGreaterThan(const char* lhs, const char* rhs);
void ExpectGreaterThanOrEqual(const char* lhs, const char* rhs);

}  // namespace cppbdd

#endif  // CPPBDD_EXPECT_HPP_
