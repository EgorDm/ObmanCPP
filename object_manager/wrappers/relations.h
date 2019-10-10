//
// Created by egordm on 08-09-19.
//

#pragma once

#include "../interfaces/relations_interface.h"

using namespace object_manager::interface;

namespace object_manager::wrappers {
    class Relations : public RelationsInterface {
    protected:
        Php::Value instance;
    public:
        Relations();

        Relations(const Php::Value &instance);

        bool has(const KindAccessor &type) override;

        std::vector<std::string> get_parents(const KindAccessor &type) override;
    };
}



