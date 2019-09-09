//
// Created by egordm on 09-09-19.
//

#include "factory.h"
#include "../transformers/argument_transformer.h"
#include "../implementation/definition.h"
#include "../utils.h"
#include "definition.h"
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

    if (params.size() > 2) definitions_handle = params[2];
    auto definitions_impl = definitions_handle.implementation<DefinitionInterface>();
    if (definitions_impl) {
        instance.set_definitions(definitions_handle.implementation<DefinitionInterface>());
    } else {
        instance.set_definitions(reinterpret_cast<DefinitionInterface *>(
                                         new object_manager::Definition(config_instance ? &config_instance->get_instance() : nullptr)
                                 )); // TODO memory leak
    }

    std::unordered_map<std::string, Php::Value> global_arguments;
    if (params.size() > 3) {
        for (const auto &[key, value] : params[3]) global_arguments.insert({key, value});
    }
    instance.set_global_arguments(global_arguments);
}

Php::Value Factory::create(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = instance.get_config().get_kind_table().get_id_or_insert(object_manager::utils::trim_slash(accessor));
    std::unordered_map<std::string, Argument> arguments;
    if (params.size() > 1) {
        arguments = object_manager::transformers::parse_arguments(params[1], instance.get_config().get_kind_table());
    }
    return instance.create(id, arguments).value;
}

void Factory::set_object_manager(Php::Parameters &params) {
    object_manager_handle = params[0];
    auto object_manager_instance = object_manager_handle.implementation<ObjectManager>();
    instance.set_object_manager(object_manager_instance ? &object_manager_instance->get_instance() : nullptr);
}
