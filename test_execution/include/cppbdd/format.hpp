#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <string>
#include <string_view>
#include <format>

namespace cppbdd {

template <typename... Args>
std::string dyna_format(std::string_view fmt, Args&&... args) {
    return std::vformat(fmt, std::make_format_args(args...));
}

}  // namespace: cppbdd

#endif  // FORMAT_HPP
