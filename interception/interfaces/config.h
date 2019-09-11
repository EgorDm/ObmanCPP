//
// Created by egordm on 11-09-19.
//

#pragma once

#include <phpcpp.h>
#include <structures/accessor.h>

using namespace object_manager::structures;

namespace interception::interface {
    class ConfigInterface {
        virtual bool has_plugins(KindId type) = 0;

        virtual void initialize(Php::Value class_definitions) = 0; // TODO lookup possible types
    };
}
