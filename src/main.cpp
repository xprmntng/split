#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <expected>

#include "convert.hpp"
#include "split.hpp"
#include "types.hpp"

using types::u32;
using convert::from_string;

std::expected<std::vector<u32>, std::string> split_version(std::string version_string);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <version string>" << std::endl;
        return 1;
    }
    const std::string version_string = argv[1];
    for (const auto& piece : split(version_string, '.')) {
        std::cout << "'" << piece << "' ";
    }
    std::cout << std::endl;
    // const auto result = split_version(version_string);
    // if (!result) {
    //     std::cout << result.error() << std::endl;
    //     return 1;
    // }
    // const auto pieces = *result;
    // for (const auto& piece : pieces) {
    //     std::cout << piece << " ";
    // }
    // std::cout << std::endl;
}

std::expected<std::vector<u32>, std::string> split_version(std::string version_string) {
    std::vector<u32> pieces;

    std::istringstream stream(version_string);
    std::string token_out;
    const char delimeter = '.';
    while (std::getline(stream, token_out, delimeter)) {
        const auto result = from_string<u32>(token_out);
        if (!result) {
            return std::unexpected(result.error());
        }
        pieces.push_back(*result);
    }
    return pieces;
}
