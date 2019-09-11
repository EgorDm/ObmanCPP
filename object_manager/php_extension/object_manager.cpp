//
// Created by egordm on 09-09-19.
//

#include "object_manager.h"
#include "../utils.h"
#include "../transformers/argument_transformer.h"
#include "config.h"
#include "factory.h"

using namespace php_extension;

void ObjectManager::__construct(Php::Parameters &params) {
    config_handle = params[0];
    auto config_instance = config_handle.implementation<Config>();
    instance.set_config(config_instance ? &config_instance->get_instance() : nullptr);

    factory_handle = params[1];
    auto factory_instance = factory_handle.implementation<Factory>();
    instance.set_factory(factory_instance ? &factory_instance->get_instance() : nullptr);

    std::unordered_map<KindId, Instance> shared_instances;
    if(params.size() > 2) {
        for(const auto &[key, value] : params[2]) {
            std::string accessor = key;
            auto id = KindTable::get_instance().get_id_or_insert(object_manager::utils::trim_slash(accessor));
            shared_instances.insert({id, Instance(value)});
        }
    }
    instance.set_shared_instances(shared_instances);
}

Php::Value ObjectManager::create(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = KindTable::get_instance().get_id_or_insert(object_manager::utils::trim_slash(accessor));
    std::unordered_map<std::string, Argument> arguments;
    if(params.size() > 1) {
        arguments = object_manager::transformers::parse_arguments(params[1], KindTable::get_instance());
    }
    return instance.create(id, arguments).value;
}

Php::Value ObjectManager::get(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = KindTable::get_instance().get_id_or_insert(object_manager::utils::trim_slash(accessor));
    return instance.get(id).value;
}

void ObjectManager::configure(Php::Parameters &params) {
    std::map<std::string, Php::Value> configuration = params[0];
    instance.configure(configuration);
}

void ObjectManager::add_shared_instance(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = KindTable::get_instance().get_id_or_insert(object_manager::utils::trim_slash(accessor));
    instance.add_shared_instance(id, params[1]);
}
