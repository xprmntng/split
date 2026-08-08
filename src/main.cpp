#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <expected>

#include "convert.hpp"
#include "split.hpp"
#include "types.hpp"

using types::u32;
using split::split_into;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <version string>" << std::endl;
        return 1;
    }
    const std::string version_string = argv[1];
    const auto result = split_into<u32>(version_string, '.');
    if (!result) {
        std::cout << result.error() << std::endl;
        return 1;
    }
    const auto& pieces = *result;
    for (const auto& piece : pieces) {
        std::cout << piece << " ";
    }
    std::cout << std::endl;
}
