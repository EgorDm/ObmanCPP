//
// Created by egordm on 12-09-19.
//

#pragma once

#include <string>
#include <cstring>

namespace interception::utils {
    bool str_starts_with(std::string const &value, std::string const &prefix) {
        size_t valueSize = value.size();
        size_t prefixSize = prefix.size();

        if (prefixSize > valueSize) {
            return false;
        }

        return memcmp(value.data(), prefix.data(), prefixSize) == 0;
    }

    bool str_ends_with(std::string const &value, std::string const &suffix) {
        size_t valueSize = value.size();
        size_t suffixSize = suffix.size();

        if (suffixSize > valueSize) {
            return false;
        }

        const char *valuePtr = value.data() + valueSize - suffixSize;

        return memcmp(valuePtr, suffix.data(), suffixSize) == 0;
    }
}


