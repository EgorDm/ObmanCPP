//
// Created by egordm on 16-09-19.
//

#pragma once
#include <vector>
#include <structures/accessor.h>

using namespace object_manager::structures;

namespace interception::interface {
    enum ListenerType {
        None = -1,
        LISTENER_BEFORE = 0,
        LISTENER_AROUND = 1,
        LISTENER_AFTER = 2
    };

    class DefinitionInterface {
    public:
        virtual std::vector<std::string> get_method_list(KindAccessor type) = 0;
    };
}
