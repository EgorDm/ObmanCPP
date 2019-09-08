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
    auto id = config->get_kind_table().get_id_or_insert(utils::trim_slash(type));
    return create(id, arguments);
}

Instance &ObjectManager::get(const KindId &id) {
    if(shared_instances.find(id) == shared_instances.end()) {
        std::map<std::string, Php::Value> args;
        shared_instances[id] = create(id, args);
    }

    return shared_instances[id];
}

Instance &ObjectManager::get(KindAccessor type) {
    auto id = config->get_kind_table().get_id_or_insert(utils::trim_slash(type));
    return get(id);
}

void ObjectManager::configure(std::map<std::string, Php::Value> &configuration) {
    config->extend(configuration);
}
