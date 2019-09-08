//
// Created by egordm on 08-09-19.
//

#pragma once


#include "../interfaces/factory_interface.h"
#include "../interfaces.h"

using namespace object_manager::interface;

namespace object_manager {
    class Factory : public FactoryInterface {
    protected:
        ObjectManagerInterface* object_manager; // TODO: managed by php!
        ConfigInterface* config;
        DefinitionInterface* definitions;
        std::unordered_map<std::string, Php::Value> global_arguments;
        std::vector<KindId> creation_stack; // TODO: combine and unordered set and with a vector for O(1) check and last retrieval

    public:
        Instance create(KindId &requested_type, std::unordered_map<std::string, Argument> &arguments) override;

        std::vector<Php::Value> resolve_arguments(KindId requested_type, std::vector<Parameter> &parameters, std::unordered_map<std::string, Argument> &arguments);

        std::vector<Php::Value> resolve_arguments_in_runtime(KindId requested_type, std::vector<Parameter> &parameters, std::unordered_map<std::string, Argument> &arguments);

        Php::Value resolve_argument(Argument &argument, const Parameter &parameter, KindId requested_type);

        Php::Value resolve_argument_simple(Argument &argument, const Php::Value &default_value);

        Php::Value parse_array(Php::Value &array);

        void set_object_manager(ObjectManagerInterface *object_manager) override;
    };
};


