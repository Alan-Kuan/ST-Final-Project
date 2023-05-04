#include "include/translator.hpp"

#include <strings.h>
#include <unistd.h>
#include <yaml-cpp/node/detail/iterator_fwd.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/node/type.h>
#include <yaml-cpp/null.h>
#include <yaml-cpp/yaml.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

const char* help_str = "usage: translator [input.yml]";

std::string value_type_str(value_type t) {
    switch (t) {
        case value_type::Bool:
            return std::string("bool");
        case value_type::Char:
            return std::string("char");
        case value_type::Int:
            return std::string("int");
        case value_type::Double:
            return std::string("double");
        case value_type::String:
            return std::string("std::string");
    }
}

void print_node(YAML::Node n, int level) {
    YAML::Node key, val;
    for (YAML::iterator it = n.begin(); it != n.end(); ++it) {
        key = it->first;
        val = it->second;
        std::string key_str = key.as<std::string>();
        std::string padding(level * 2, ' ');
        std::cout << padding << key_str << ":";
        switch (val.Type()) {
            case YAML::NodeType::Map:
                std::cout << "\n";
                print_node(val, level + 1);
                break;
            case YAML::NodeType::Sequence:
                std::cout << "\n";
                padding = std::string((level + 1) * 2, ' ');
                for (size_t i = 0; i < val.size(); i++) {
                    std::cout << padding << key_str;
                    printf("[%lu]:", i);
                    if (val[i].IsScalar()) {
                        std::cout << " " << val[i].as<std::string>() << "\n";
                    } else {
                        std::cout << "\n";
                        print_node(val[i], level + 2);
                    }
                }
                break;
            case YAML::NodeType::Null:
            case YAML::NodeType::Undefined:
                std::cout << " (nil)\n";
                break;
            case YAML::NodeType::Scalar:
                std::cout << " " << val.as<std::string>() << "\n";
                break;
        }
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << help_str << "\n";
        return 1;
    }
    YAML::Node root, key, val;
    const char* target = argv[1];
    if (access(target, F_OK) != 0) {
        perror("access");
        return 1;
    }
    printf("opening %s...\n", target);
    root = YAML::LoadFile(target);
    printf("size: %ld\n", root.size());
    print_node(root, 0);
    return 0;
}
