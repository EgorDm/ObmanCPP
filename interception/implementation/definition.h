//
// Created by egordm on 16-09-19.
//

#pragma once


#include "../interfaces/definition_interface.h"

namespace interception {

    class Definition : public interface::DefinitionInterface {
    protected:
        static const unsigned int PREFIX_LENGTHS[3];
        static const char* PREFIXES[3];

    public:
        std::vector<std::string> get_method_list(KindAccessor type) override;

    protected:
        interface::ListenerType get_listener_type(const std::string &s);
    };
}


