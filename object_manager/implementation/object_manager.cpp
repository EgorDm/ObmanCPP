//
// Created by egordm on 08-09-19.
//

#include "object_manager.h"
#include "../utils.h"

using namespace object_manager;

Instance ObjectManager::create(const KindId &id, std::unordered_map<std::string, Argument> &arguments) {
    auto pref_id = config->get_preference(id);
    return factory->create(pref_id, arguments);
}

Instance ObjectManager::create(KindAccessor type, std::unordered_map<std::string, Argument> &arguments) {
    auto id = KindTable::get_instance().get_id_or_insert(utils::trim_slash(type));
    return create(id, arguments);
}

Instance &ObjectManager::get(const KindId &id) {
    if(shared_instances.find(id) == shared_instances.end()) {
        std::unordered_map<std::string, Argument> args;
        shared_instances[id] = create(id, args);
    }

    return shared_instances[id];
}

Instance &ObjectManager::get(KindAccessor type) {
    auto id = KindTable::get_instance().get_id_or_insert(utils::trim_slash(type));
    return get(id);
}

void ObjectManager::configure(std::map<std::string, Php::Value> &configuration) {
    config->extend(configuration);
}

ConfigInterface &ObjectManager::get_config() const {
    return *config; // TODO: check if is not null
}

void ObjectManager::set_config(ConfigInterface *config) {
    ObjectManager::config = config;
}

FactoryInterface &ObjectManager::get_factory() const {
    return *factory;
}

void ObjectManager::set_factory(FactoryInterface *factory) {
    ObjectManager::factory = factory;
}

const std::unordered_map<KindId, Instance> &ObjectManager::get_shared_instances() const {
    return shared_instances;
}

void ObjectManager::set_shared_instances(const std::unordered_map<KindId, Instance> &shared_instances) {
    ObjectManager::shared_instances = shared_instances;
}

void ObjectManager::add_shared_instance(KindId kind, const Instance &instance) {
    shared_instances[kind] = instance;
}
