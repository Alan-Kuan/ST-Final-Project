#include "include/translator.hpp"

#include <iostream>

#include "yaml-cpp/yaml.h"

#define PROJECT_NAME "translator"

int main(int argc, char **argv) {
    if (argc != 1) {
        std::cout << argv[0] << "takes no arguments.\n";
        return 1;
    }
    std::cout << "This is project " << PROJECT_NAME << ".\n";
    return 0;
}
