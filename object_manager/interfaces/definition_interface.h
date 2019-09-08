//
// Created by egordm on 08-09-19.
//

#pragma once

#include "../structures/accessor.h"
#include "../structures/parameter.h"

using namespace object_manager::structures;

namespace object_manager::interface {
    class DefinitionInterface {
    public:
        virtual std::vector<Parameter> get_parameters(KindId kind_id) = 0;

        virtual std::vector<std::string> get_classes() = 0;
    };
}