//
// Created by egordm on 08-09-19.
//

#include "config.h"
#include "../utils.h"

using namespace php_extension;

Php::Value Config::get_arguments(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = instance.get_kind_table().get_id_or_insert(object_manager::utils::trim_slash(accessor)); // TODO: trim?
    auto args = instance.get_arguments(id);
    if(args != nullptr) {
        return object_manager::transformers::serialize_arguments(*args, instance.get_kind_table());
    } else {
        return Php::Array();
    }
}

Php::Value Config::is_shared(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = instance.get_kind_table().get_id_or_insert(object_manager::utils::trim_slash(accessor));
    return instance.is_shared(id);
}

Php::Value Config::get_instance_type(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = instance.get_kind_table().get_id_or_insert(object_manager::utils::trim_slash(accessor));
    auto ret = instance.get_instance_type(id);
    return instance.get_kind_table().get_accessor(ret);
}

Php::Value Config::get_preference(Php::Parameters &params) {
    auto accessor = params[0].stringValue();
    auto id = instance.get_kind_table().get_id_or_insert(object_manager::utils::trim_slash(accessor));
    auto ret = instance.get_preference(id);
    return instance.get_kind_table().get_accessor(ret);
}

Php::Value Config::get_virtual_types() {
    // TODO: cache this. Should never be called -> performace hit
    std::map<std::string, std::string> ret;
    auto kind_table = instance.get_kind_table();
    for(const auto &[from, to] : instance.get_virtual_types()) {
        ret.insert({kind_table.get_accessor(from), kind_table.get_accessor(to)});
    }
    return ret;
}

Php::Value Config::get_preferences() {
    // TODO: cache this. Should never be called -> performace hit
    std::map<std::string, std::string> ret;
    auto kind_table = instance.get_kind_table();
    for(const auto &[from, to] : instance.get_virtual_types()) {
        ret.insert({kind_table.get_accessor(from), kind_table.get_accessor(to)});
    }
    return ret;
}
