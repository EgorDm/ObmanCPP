//
// Created by egordm on 09-09-19.
//

#include "factory.h"
#include "../transformers/argument_transformer.h"
#include "../implementation/definition.h"
#include "../utils.h"
#include "config.h"
#include "object_manager.h"

using namespace php_extension;

void Factory::__construct(Php::Parameters &params) {
    config_handle = params[0];
    auto config_instance = config_handle.implementation<Config>();
    instance.set_config(config_instance ? &config_instance->get_instance() : nullptr);

    if (params.size() > 1) object_manager_handle = params[1];
    auto object_manager_instance = object_manager_handle.implementation<ObjectManager>();
    instance.set_object_manager(object_manager_instance ? &object_manager_instance->get_instance() : nullptr);

    if (params.size() > 2) {
        // do nothing. We dont need magneto's definitions class
    }

    std::unordered_map<std::string, Php::Value> global_arguments;
    if (params.size() > 3) {
        for (const auto &[key, value] : params[3]) global_arguments.insert({key, value});
    }
    instance.set_global_arguments(global_arguments);
}

Php::Value Factory::create(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = KindTable::get_instance().get_id_or_insert(object_manager::utils::trim_slash(accessor));
    std::unordered_map<std::string, Argument> arguments;
    if (params.size() > 1) {
        arguments = object_manager::transformers::parse_arguments(params[1], KindTable::get_instance());
    }
    return instance.create(id, arguments).value;
}

void Factory::set_object_manager(Php::Parameters &params) {
    object_manager_handle = params[0];
    auto object_manager_instance = object_manager_handle.implementation<ObjectManager>();
    instance.set_object_manager(object_manager_instance ? &object_manager_instance->get_instance() : nullptr);
}
