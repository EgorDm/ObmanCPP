//
// Created by egordm on 12-09-19.
//

#include "config.h"
#include "../utils.h"

using namespace interception;

void Config::initialize(std::vector<KindId> &class_definitons) {
    generate_intercepted(class_definitons);

    // TODO: cache save
}

bool Config::has_plugins(KindId type) {
    auto res = intercepted.find(type);
    if (res != intercepted.end()) {
        return res->second;
    }

    return inherit_interception(type);
}

bool Config::inherit_interception(KindId type) {
    auto res = intercepted.find(type);
    if (res != intercepted.end()) {
        return res->second;
    } else {
        auto real_type = om_config->get_instance_type(type);// TODO get original instead
        if (type != real_type) {
            if (inherit_interception(real_type)) {
                intercepted[type] = true;
                return true;
            }
        } else {
            const auto &accessor = KindTable::get_instance().get_accessor(type);
            if (!utils::str_ends_with(accessor, "\\Interceptor") && relations->has(accessor)) {
                auto relations = this->relations->get_parents(accessor);
                for (const auto &relation : relations) {
                    auto relation_id = KindTable::get_instance().get_id_or_insert(relation);
                    if (inherit_interception(relation_id)) {
                        intercepted[type] = true;
                        return true;
                    }
                }
            }
        }

        intercepted[type] = false;
        return false;
    }
}

void Config::initialize_uncompiled(std::vector<KindId> &class_definitons) {
    // TODO clear cache
    generate_intercepted(class_definitons);
    // TODO write to cache
}

void Config::generate_intercepted(std::vector<KindId> &class_definitons) {
    Php::Value config;
    // TODO: read scope config and unset preferences
    std::vector<KindId> type_ids;
    for (const auto &[type_name, type_config] : config) {
        auto id = KindTable::get_instance().get_id_or_insert(type_name); // TODO trim
        type_ids.push_back(id);
        if (type_config.contains("plugins")) {
            intercepted[id] = true;
        }
    }

    for (const auto &id : type_ids) {
        has_plugins(id);
    }

    for (const auto &id : class_definitons) {
        has_plugins(id);
    }
}
