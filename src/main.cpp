#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <expected>
#include <unordered_map>

#include "convert.hpp"
#include "split.hpp"
#include "types.hpp"

using types::u32;
using split::split_into;

int main(int argc, const char** argv) {
    std::unordered_map<std::string, int> choices = {
        {"--major", 0},
        {"--minor", 1},
        {"--patch", 2}
    };
    if (argc < 3 || !choices.contains(argv[1])) {
        std::cout << "Usage: " << argv[0] << " [--major|--minor|--patch] <version string>" << std::endl;
        return 1;
    }
    const int choice = choices[argv[1]];
    const std::string version_string = argv[2];
    const auto result = split_into<u32>(version_string, '.');
    if (!result) {
        std::cout << result.error() << std::endl;
        return 1;
    }
    auto pieces = *result;
    pieces[choice] += 1;
    for (int i = choice + 1; i < 3; i++) {
        pieces[i] = 0;
    }
    for (const auto& piece : pieces) {
        std::cout << piece << " ";
    }
    std::cout << std::endl;
}
