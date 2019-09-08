//
// Created by egordm on 08-09-19.
//

#pragma once


#include <phpcpp.h>
#include "../structures.h"

using namespace object_manager::structures;

namespace object_manager::transformers {
    std::unordered_map<std::string, Argument> parse_arguments(const Php::Value &value, KindTable &kind_table);

    Argument transform_argument(const Php::Value &value, KindTable &kind_table);

    Php::Value serialize_arguments(std::unordered_map<std::string, Argument> &arguments, KindTable &kind_table);

    Php::Value serialize_argument(Argument &argument, KindTable &kind_table);
}
