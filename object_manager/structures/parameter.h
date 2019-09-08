//
// Created by egordm on 08-09-19.
//

#pragma once

#include <string>
#include <optional>
#include <phpcpp.h>

namespace object_manager::structures {
    class Parameter {
    private:
        std::string name;
        std::optional<std::string> type;
        bool required;
        std::optional<Php::Value> default_val;

    public:
        Parameter(const std::string &name, const std::optional<std::string> &type, bool required,
                  const std::optional<Php::Value> &default_val)
                  : name(name), type(type), required(required), default_val(default_val) {}

        const std::string &get_name() const {
            return name;
        }

        const std::optional<std::string> &get_type() const {
            return type;
        }

        bool is_required() const {
            return required;
        }

        const std::optional<Php::Value> &get_default_val() const {
            return default_val;
        }
    };
}
