#ifndef CPPBDD_HPP
#define CPPBDD_HPP

#include <cstdio>
#include <functional>
#include <string>
#include <vector>
#include <list>
#include <cassert>
#include <any>

#define FUNC(arg...) function<void(arg)>([&] (arg)

#define Given_  add_task
#define Then_   add_task
#define When_   add_task

struct Scenario {
public:
    Scenario(const std::string& msg, const std::function<void(void)>& callback)
        : msg(msg),
          callback(callback) {}
    
    std::string msg;
    std::function<void(void)> callback;
};

void Scenario_(const std::string& fmt_str, std::function<void(void)> callback);

extern std::vector<Scenario> scenarios;

#endif  // CPPBDD_HPP
