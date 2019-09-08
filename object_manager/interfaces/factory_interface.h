//
// Created by egordm on 08-09-19.
//

#pragma once

#include <string>
#include <phpcpp.h>
#include "object_manager_interface.h"

using namespace object_manager::structures;

namespace object_manager::interface {
    class FactoryInterface {
        virtual void create(KindId &requested_type, std::map<std::string, Php::Value> &arguments) = 0;

        virtual void set_object_manager(ObjectManagerInterface *object_manager) = 0;
    };
}
