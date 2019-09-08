//
// Created by egordm on 08-09-19.
//

#pragma once

#include <string>
#include <phpcpp.h>
#include "../structures/accessor.h"

using namespace object_manager::structures;

namespace object_manager::interface {
    class ObjectManagerInterface {
    public:
        virtual void create(KindId &type, std::map<std::string, Php::Value> &arguments) = 0; // TODO meta

        virtual void get(KindId &type) = 0;

        virtual void configure(std::map<std::string, Php::Value> &configuration) = 0;
    };
}
