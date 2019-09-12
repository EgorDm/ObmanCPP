//
// Created by egordm on 11-09-19.
//

#include "relations.h"

using namespace object_manager;

bool Relations::has(const KindAccessor &type) {
    Php::Value val = type;
    return Php::call("class_exists", val) || Php::call("interface_exists", val);
}

std::vector<std::string> Relations::get_parents(const KindAccessor &type) {
    Php::Value class_name = type;

    if(!Php::call("class_exists", class_name)) {
        return {};
    }

    std::vector<std::string> ret;
    auto parent_class = Php::call("get_parent_class", class_name);
    if(parent_class) {
        ret.push_back(parent_class);
        if(auto interfaces = Php::call("class_implements", class_name)) {
            if(auto parent_interfaces = Php::call("class_implements", parent_class)) {
                for(auto &[k, v] : Php::call("array_diff", interfaces, parent_interfaces)) {
                    ret.push_back(v);
                }
            } else {
                for(auto &[k, v] : interfaces) {
                    ret.push_back(v);
                }
            }
        }
    } else {
        for(auto &[k, v] : Php::call("class_implements", class_name)) {
            ret.push_back(v);
        }
    }

    return ret;
}
