//
// Created by egordm on 08-09-19.
//

#pragma once

#include <string>
#include <phpcpp.h>
#include "../structures/accessor.h"
#include "../structures.h"

using namespace object_manager::structures;

namespace object_manager::interface {
    class ObjectManagerInterface {
    public:
        virtual Instance create(KindAccessor type, std::unordered_map<std::string, Argument> &arguments) = 0;

        virtual Instance create(const KindId &type, std::unordered_map<std::string, Argument> &arguments) = 0;

        virtual Instance &get(KindAccessor type) = 0;

        virtual Instance &get(const KindId &type) = 0;

        virtual void configure(std::map<std::string, Php::Value> &configuration) = 0;
    };
}
