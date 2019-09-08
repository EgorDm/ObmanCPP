#include "config.h"
#include "../utils.h"
#include "../transformers/argument_transformer.h"

using namespace object_manager;

void Config::set_relations(RelationsInterface *relations) {
    this->relations = relations;
}

std::unordered_map<std::string, Argument> *Config::get_arguments(KindId type) {
    if(merged_arguments.find(type) == merged_arguments.end()) {
        std::unordered_map<std::string, Argument> res;

        auto virtual_type = virtual_types.find(type);
        if(virtual_type != virtual_types.end()) {
            res = *get_arguments(virtual_type->second);
        } else if(relations->has(kind_table.get_accessor(type))) {
            auto relations = this->relations->get_parents(kind_table.get_accessor(type));
            for(auto &relation : relations) {
                if(!relation.empty()) {
                    auto relation_id = kind_table.get_id_or_insert(relation);
                    auto relation_arguments = get_arguments(relation_id);
                    if(relation_arguments != nullptr) {
                        for(const auto &[param, arg] : *relation_arguments) {
                            res[param] = arg;
                        }
                    }
                }
            }
        }

        auto arguments_it = arguments.find(type);
        if(arguments_it != arguments.end()) {
            for(const auto &[param, arg] : arguments_it->second) {
                res[param] = arg;
            }
        }

        merged_arguments[type] = res;
    }

    auto res = merged_arguments.find(type);
    if (res != merged_arguments.end()) return &res->second;
    else return nullptr;
}

KindId Config::get_instance_type(KindId instance_type) {
    auto res = virtual_types.find(instance_type);
    auto  uu = res != virtual_types.end();
    if (res != virtual_types.end()) return get_instance_type(res->second);
    else return instance_type;
}

bool Config::is_shared(KindId type) {
    return non_shared_types.find(type) == non_shared_types.end();
}

KindId Config::get_preference(KindId type) {
    auto res = preferences.find(type);
    if (res != preferences.end()) return res->second;
    else return type;
}

std::unordered_map<KindId, KindId> &Config::get_virtual_types() {
    return virtual_types;
}

void Config::extend(std::map<std::string, Php::Value> &configuration) {
    for (auto const&[key, cur_config] : configuration) {
        if (key == "preferences") {
            for (auto const&[from, to] : cur_config) {
                auto from_val = from.stringValue();
                auto to_val = to.stringValue();

                preferences[kind_table.get_id_or_insert(utils::trim_slash(from_val))]
                    = kind_table.get_id_or_insert(utils::trim_slash(to_val));
            }
        } else {
            auto key_val = key;
            auto key_id = kind_table.get_id_or_insert(utils::trim_slash(key_val));

            if(cur_config.contains("type")) {
                std::string to_val = cur_config["type"].stringValue();
                virtual_types[key_id] = kind_table.get_id_or_insert(utils::trim_slash(to_val));
            }
            if(cur_config.contains("arguments")) {
                auto args = transformers::parse_arguments(cur_config.get("arguments"), kind_table);
                auto current_args_it = arguments.find(key_id);

                if(current_args_it != arguments.end()) {
                    for (auto const&[param, arg] : args) {
                        current_args_it->second[param] = arg;
                    }
                } else {
                    arguments[key_id] = args;
                }
            }
            if(cur_config.contains("shared")) {
                if(cur_config.get("shared").boolValue()) {
                    non_shared_types.erase(key_id);
                } else {
                    non_shared_types.insert(key_id);
                }
            }
        }
    }
}

std::unordered_map<KindId, KindId> &Config::get_preferences() {
    return preferences;
}
