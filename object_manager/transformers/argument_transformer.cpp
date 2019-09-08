//
// Created by egordm on 08-09-19.
//

#include "argument_transformer.h"
#include "../utils.h"

using namespace object_manager;

std::unordered_map<std::string, Argument>
transformers::parse_arguments(const Php::Value &value, KindTable &kind_table) {
    std::unordered_map<std::string, Argument> ret;
    for (auto const&[param, value] : value) {
        ret.insert({param.stringValue(), transform_argument(value, kind_table)});
    }

    return ret;
}

Argument transformers::transform_argument(const Php::Value &value, KindTable &kind_table) {
    if (value.isArray()) {
        if (value.contains("instance")) {
            auto kind = value.get("instance").stringValue();
            auto kind_id = kind_table.get_id_or_insert(utils::trim_slash(kind));
            return Argument(ArgumentType::Kind, kind_id);
        } else if (value.contains("argument")) {
            return Argument(ArgumentType::GlobalValue, value.get("argument").stringValue());
        } else {
            return Argument(ArgumentType::Array, value);
        }
    } else {
        return Argument(ArgumentType::Value, value);
    }
}

Php::Value
transformers::serialize_arguments(std::unordered_map<std::string, Argument> &arguments, KindTable &kind_table) {
    std::map<std::string, Php::Value> ret;
    for (auto &[param, value] : arguments) {
        ret.insert({param, transformers::serialize_argument(value, kind_table)});
    }
    return ret;
}

Php::Value transformers::serialize_argument(Argument &argument, KindTable &kind_table) {
    switch (argument.get_type()) {
        case Value: return argument.get_value();
        case GlobalValue: return Php::Array(std::map<std::string, Php::Value>({{"argument", argument.get_global_value()}}));
        case Kind: return Php::Array(std::map<std::string, Php::Value>({{"instance", kind_table.get_accessor(argument.get_kind())}}));
        case Array: return argument.get_array();
    }
}
