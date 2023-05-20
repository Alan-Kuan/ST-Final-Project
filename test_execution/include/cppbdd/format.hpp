#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <string>
#include <string_view>
#include <format>

namespace cppbdd {

using namespace std;

template <typename... Args>
string dyna_format(string_view fmt, Args&&... args) {
    return vformat(fmt, make_format_args(args...));
}

}  // namespace: cppbdd

#endif  // FORMAT_HPP
