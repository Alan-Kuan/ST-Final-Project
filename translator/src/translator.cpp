#include "include/translator.hpp"

#include <strings.h>
#include <unistd.h>
#include <yaml-cpp/node/detail/iterator_fwd.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/node/type.h>
#include <yaml-cpp/null.h>
#include <yaml-cpp/yaml.h>

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <inja/inja.hpp>
#include <iostream>
#include <optional>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "inja/environment.hpp"

const char* help_str = "usage: translator input.yml [output.cpp]";

std::unordered_map<std::string, std::vector<std::optional<std::string>>> parse_cases(
    YAML::Node& n, std::unordered_map<std::string, size_t>& size) {
    std::unordered_map<std::string, std::vector<std::optional<std::string>>> case_map;
    YAML::Node key, val;
    for (YAML::iterator it = n.begin(); it != n.end(); ++it) {
        key = it->first;
        val = it->second;
        std::string key_str = key.as<std::string>();
        if (key_str == "given" || key_str == "when" || key_str == "then") {
            size_t case_size = size[key_str];
            std::vector<std::optional<std::string>> values;
            switch (val.Type()) {
                case YAML::NodeType::Scalar: {
                    if (case_size != 1) {
                        fprintf(stderr,
                                "Mismatched test case number: %lu case(s) required, found 1 case(s), abort...\n",
                                case_size);
                        exit(1);
                    }
                    values.push_back(val.as<std::string>());
                    break;
                }
                case YAML::NodeType::Null:
                    values.push_back({});
                case YAML::NodeType::Sequence: {
                    size_t case_cnt = val.size();
                    if (case_size != case_cnt) {
                        fprintf(stderr,
                                "Mismatched test case number: %lu case(s) required, found %lu case(s), abort...\n",
                                case_size, case_cnt);
                        exit(1);
                    }
                    for (size_t i = 0; i < case_cnt; i++) {
                        if (val[i].IsScalar()) {
                            values.push_back(val[i].as<std::string>());
                        } else {
                            values.push_back({});
                        }
                    }
                    break;
                }
                default:
                    break;
            }
            case_map[key_str] = values;
        }
    }
    return case_map;
}

// only 0 ~ 1 argument is allowed
inja::json parse_fmt_with_type(YAML::Node& n) {
    inja::json data;
    if (!n.IsScalar()) {
        fprintf(stderr, "Error: given or when contained non-string data, abort...\n");
        exit(1);
    }
    std::string val_str = n.as<std::string>();
    std::regex rgx("\\{(.*)\\}");
    std::smatch matches;
    std::string type, fmt;
    if (std::regex_search(val_str, matches, rgx)) {
        // if the regex matches, the capture group must have captured something,
        // even an empty string counts
        type = matches[1];  // value of capture group
        fmt = val_str.erase(matches.position(1), matches[1].length());
    } else {
        type = "void";
        fmt = val_str;
    }
    data["type"] = type;
    data["fmt"] = fmt;
    return data;
}

inja::json parse_scenario(YAML::Node& n) {
    inja::json data;
    std::unordered_map<std::string, size_t> size;
    YAML::Node key, val;
    size["given"] = 0;
    size["when"] = 0;
    size["then"] = 0;
    for (YAML::iterator it = n.begin(); it != n.end(); ++it) {
        key = it->first;
        val = it->second;
        std::string key_str = key.as<std::string>();
        if (key_str == "scenario") {
            data["scenario"] = val.as<std::string>();
        } else if (key_str == "given" || key_str == "when" || key_str == "then") {
            std::vector<inja::json> fmts;
            switch (val.Type()) {
                case YAML::NodeType::Scalar: {
                    fmts.push_back(parse_fmt_with_type(val));
                    size[key_str] += 1;
                    break;
                }
                case YAML::NodeType::Sequence: {
                    size_t fmt_cnt = val.size();
                    for (size_t i = 0; i < fmt_cnt; i++) {
                        YAML::Node fmt = val[i];
                        fmts.push_back(parse_fmt_with_type(fmt));
                    }
                    size[key_str] += fmt_cnt;
                    break;
                }
                default:
                    fprintf(stderr, "Error: Malformed when or when, abort...\n");
                    exit(1);
            }
            data[key_str] = fmts;
        } else if (key_str == "cases") {
            if (!val.IsSequence()) {
                fprintf(stderr, "Error: Malformed scenarios, abort...\n");
                exit(1);
            }
            size_t case_count = val.size();
            std::string keys[3] = {"given", "when", "then"};
            for (const std::string& k : keys) {
                for (size_t j = 0; j < size[k]; j++) {
                    data[k][j]["cases"] = std::vector<std::string>();
                }
            }
            for (size_t i = 0; i < case_count; i++) {
                YAML::Node case_node = val[i];
                auto case_map = parse_cases(case_node, size);
                for (const std::string& k : keys) {
                    for (size_t j = 0; j < case_map[k].size(); j++) {
                        if (case_map[k][j] == std::nullopt) {
                            continue;
                        }
                        data[k][j]["cases"].push_back(*case_map[k][j]);
                    }
                }
            }
        }
    }
    return data;
}

inja::json parse_spec(YAML::Node& n) {
    inja::json data;
    YAML::Node key, val;
    for (YAML::iterator it = n.begin(); it != n.end(); ++it) {
        key = it->first;
        val = it->second;
        std::string key_str = key.as<std::string>();
        if (key_str == "title") {
            if (!val.IsScalar()) {
                fprintf(stderr, "Error: Title contained non-string data, abort...\n");
                exit(1);
            }
            data["title"] = val.as<std::string>();
        } else if (key_str == "user_story") {
            std::vector<std::string> stories;
            switch (val.Type()) {
                case YAML::NodeType::Scalar:
                    stories.push_back(val.as<std::string>());
                    break;
                case YAML::NodeType::Sequence:
                    for (size_t i = 0; i < val.size(); i++) {
                        if (!val[i].IsScalar()) {
                            fprintf(stderr, "Error: User story contained non-string data, abort...\n");
                            exit(1);
                        }
                        stories.push_back(val[i].as<std::string>());
                    }
                    break;
                case YAML::NodeType::Null:
                case YAML::NodeType::Undefined:
                    stories.push_back("No story :(");
                    break;
                case YAML::NodeType::Map:
                    fprintf(stderr, "Error: User story contained non-string data, abort...\n");
                    exit(1);
            }
            data["user_story"] = stories;
        } else if (key_str == "scenarios") {
            if (!val.IsSequence()) {
                fprintf(stderr, "Error: Malformed scenarios, abort...\n");
                exit(1);
            }
            size_t scenario_count = val.size();
            std::vector<inja::json> scenarios;
            for (size_t i = 0; i < scenario_count; i++) {
                YAML::Node scenario = val[i];
                scenarios.push_back(parse_scenario(scenario));
            }
            data["scenarios"] = scenarios;
        }
    }
    return data;
}

int main(int argc, char** argv) {
    inja::Environment env;
    const char* output_file = "a.cpp";
    if (argc == 1) {
        std::cout << help_str << "\n";
        return 1;
    } else if (argc > 2) {
        output_file = argv[2];
    }
    YAML::Node root, key, val;
    const char* target = argv[1];
    if (access(target, F_OK) != 0) {
        perror("access");
        return 1;
    }
    root = YAML::LoadFile(target);
    inja::json data = parse_spec(root);
    std::string render_result = env.render(spec_template, data);
    std::ofstream output;
    output.open(output_file);
    output << render_result;
    output.close();
    printf("Written spec to %s.\n", output_file);
    return 0;
}
