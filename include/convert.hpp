#pragma once

#include <expected>
#include <string>
#include <charconv>

#include "types.hpp"

namespace convert {

    template <typename T>
    std::expected<T, std::string> from_string(std::string str) {
        T out;
        const char* start = str.data();
        const char* end = str.data() + str.size();
        auto [ptr, ec] = std::from_chars(start, end, out);
        bool value_found = ec == std::errc();
        bool entire_string_consumed = ptr == end;
        if (!value_found || !entire_string_consumed) {
            return std::unexpected("String `" + str + "` could not be converted to " + types::get_type_name<T>());
        }
        return out;
    }

};