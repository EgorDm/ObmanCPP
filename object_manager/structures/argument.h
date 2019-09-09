//
// Created by egordm on 08-09-19.
//

#pragma once

#include <phpcpp.h>
#include <utility>
#include <variant>
#include "accessor.h"

namespace object_manager::structures {
    enum ArgumentType : unsigned char {
        Value,
        GlobalValue,
        Kind,
        Array, // TODO: Add type to cache the array values if they are arguments
    };

    class Argument {
        ArgumentType type;
        std::variant<Php::Value, std::string, KindId> value;

    public:
        Argument() = default;

        Argument(ArgumentType type, std::variant<Php::Value, std::string, KindId> value) : type(type), value(std::move(value)) {}

        ArgumentType get_type() const {
            return type;
        }

        const Php::Value &get_value() const {
            return std::get<Php::Value>(value);
        }

        const std::string &get_global_value() const {
            return std::get<std::string>(value);
        }

        KindId get_kind() const {
            return std::get<KindId>(value);
        }

        Php::Value &get_array() {
            return std::get<Php::Value>(value);
        }

        void merge(Argument &argument) {
            // Merge only if arrays
            if(get_type() == argument.get_type() && get_type() == ArgumentType::Array) {
                value = Php::call("array_merge_recursive", get_array(), argument.get_array());
            }
        }
    };
}
