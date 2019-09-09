//
// Created by egordm on 09-09-19.
//

#include "factory.h"
#include "../transformers/argument_transformer.h"

using namespace php_extension;

Php::Value php_extension::Factory::create(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = factory.get_config().get_kind_table().get_id_or_insert(accessor);
    std::unordered_map<std::string, Argument> arguments;
    if(params.size() > 1) {
        arguments = object_manager::transformers::parse_arguments(params[1], factory.get_config().get_kind_table());
    }
    return factory.create(id, arguments).value;
}

void php_extension::Factory::set_object_manager(Php::Parameters &params) {
    object_manager_handle = params[0];
    factory.set_object_manager(object_manager_handle.implementation<ObjectManagerInterface>());
}
