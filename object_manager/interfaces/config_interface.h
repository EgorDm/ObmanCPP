//
// Created by egordm on 08-09-19.
//

#pragma once

#include <string>
#include <phpcpp.h>
#include "../structures.h"
#include "relations_interface.h"
#include "../wrappers/relations.h"

using namespace object_manager::structures;

namespace object_manager::interface {
    class ConfigInterface {
    public:
        virtual void set_relations(RelationsInterface *relations) = 0;

        virtual std::unordered_map<std::string, Argument>* get_arguments(KindId type) = 0;

        virtual bool is_shared(KindId type) = 0;

        virtual KindId get_instance_type(KindId type) = 0;

        virtual KindId get_preference(KindId type) = 0;

        virtual std::unordered_map<KindId, KindId> &get_virtual_types() = 0;

        virtual void extend(std::map<std::string, Php::Value> &configuration) = 0;

        virtual std::unordered_map<KindId, KindId> &get_preferences() = 0;
    };
}
