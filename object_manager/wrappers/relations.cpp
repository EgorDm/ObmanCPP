//
// Created by egordm on 08-09-19.
//

#include "relations.h"

using namespace object_manager::wrappers;

Relations::Relations() {}

Relations::Relations(const Php::Value &instance) : instance(instance) {}

bool Relations::has(KindAccessor &type) {
    return instance.call("has", type);
}

std::vector<std::string> Relations::get_parents(KindAccessor &type) {
    return instance.call("getParents", type);
}
