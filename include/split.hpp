#pragma once

#include <concepts>
#include <expected>
#include <string>
#include <vector>

#include "convert.hpp"

namespace split {
    std::vector<std::string> split(const std::string& str, char delimeter);

    template <typename T>
    requires std::integral<T> || std::floating_point<T>
    std::expected<std::vector<T>, std::string> split_into(const std::string& str, char delimeter) {
        std::vector<std::string> pieces = split(str, delimeter);
        std::vector<T> pieces_converted;
        pieces_converted.reserve(pieces.size());
        for (const auto& piece : pieces) {
            const auto result = convert::from_string<T>(piece);
            if (!result) {
                return std::unexpected(result.error());
            }
            pieces_converted.push_back(*result);
        }
        return pieces_converted;
    }
}
