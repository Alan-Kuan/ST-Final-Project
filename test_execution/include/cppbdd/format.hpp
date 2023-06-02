#ifndef CPPBDD_FORMAT_HPP_
#define CPPBDD_FORMAT_HPP_

#include <string>
#include <string_view>
#include <format>

namespace cppbdd {

template <typename... Args>
std::string dyna_format(std::string_view fmt, Args&&... args) {
    return vformat(fmt, std::make_format_args(args...));
}

}  // namespace cppbdd

#endif  // CPPBDD_FORMAT_HPP_
