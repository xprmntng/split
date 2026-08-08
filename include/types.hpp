#pragma once

#include <cstdint>
#include <typeinfo>
#include <memory>
#include <cxxabi.h>

namespace types {
    using u32 = std::uint32_t;

    template <typename T>
    std::string get_type_name() {
        const char* mangled_name = typeid(T).name();
        int status = 0;
        // abi::__cxa_demangle allocates a raw C-string using std::malloc
        char* demangled = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);

        if (status == 0 && demangled != nullptr) {
            // Wrap in a unique_ptr to prevent a dynamic memory leak
            std::unique_ptr<char, void(*)(void*)> cleanup(demangled, std::free);
            return std::string(demangled);
        }
        return mangled_name;
    }
};
