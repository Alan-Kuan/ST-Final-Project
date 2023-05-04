#pragma once

#include <string>
#include <variant>

enum value_type {
    Bool,
    Char,
    Int,
    Double,
    String,
};

std::string value_type_str(value_type t);
