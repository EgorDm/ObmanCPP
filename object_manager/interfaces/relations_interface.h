//
// Created by egordm on 08-09-19.
//

#pragma once

#include "../structures.h"

using namespace object_manager::structures;

namespace object_manager::interface {
    class RelationsInterface {
    public:
        virtual bool has(const KindAccessor &type) = 0;

        virtual std::vector<std::string> get_parents(const KindAccessor &type) = 0;
    };
}
