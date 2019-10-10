//
// Created by egordm on 16-09-19.
//

#include <phpcpp.h>
#include "definition.h"
#include "../utils.h"

using namespace interception;

const unsigned int Definition::PREFIX_LENGTHS[3] = {6, 6, 5};
const char* Definition::PREFIXES[3] = {"befor", "aroun", "after",};


std::vector<std::string> Definition::get_method_list(KindAccessor type) {
    std::vector<std::string> methods;
    if(auto all_methods = Php::call("get_class_methods", type)) {
        auto all_method_names = all_methods.vectorValue<std::string>();
        for(const auto &method : all_method_names) {
            auto type = get_listener_type(method);
            if(type >= 0) {

            }

            auto prefix = method.substr(0, 5);
        }
    }
    
    return std::vector<std::string>();
}

interface::ListenerType Definition::get_listener_type(const std::string &s) {
    if(utils::str_starts_with(s, PREFIXES[0])) return interface::ListenerType::LISTENER_BEFORE;
    else if(utils::str_starts_with(s, PREFIXES[1])) return interface::ListenerType::LISTENER_AROUND;
    else if(utils::str_starts_with(s, PREFIXES[2])) return interface::ListenerType::LISTENER_AFTER;
    else return interface::ListenerType::None;
}
