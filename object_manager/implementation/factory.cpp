//
// Created by egordm on 08-09-19.
//

#include <iostream>
#include "factory.h"
#include "../transformers/argument_transformer.h"

using namespace object_manager;

Instance Factory::create(KindId &requested_type, std::unordered_map<std::string, Argument> &arguments) {
    KindId type = config->get_instance_type(requested_type);
    auto accessor = config->get_kind_table().get_accessor(type);
    auto parameters = definitions->get_parameters(type);
    if (parameters.empty()) {
        return Instance(Php::Object(accessor));
    }

    if (std::find(creation_stack.begin(), creation_stack.end(), type) != creation_stack.end()) {
        std::cerr << "Circular dependency: " << config->get_kind_table().get_accessor(requested_type) << " depends on "
                  << config->get_kind_table().get_accessor(creation_stack.back()) << " and vice versa.";
        creation_stack.clear();
        throw std::runtime_error("Found circular dependency!");
    }

    creation_stack.push_back(requested_type);
    std::vector<Php::Value> args = resolve_arguments(requested_type, parameters, arguments);
    creation_stack.pop_back();

    return Instance(Php::Object(accessor.c_str(), args.size(), args.data()));
}

void Factory::set_object_manager(ObjectManagerInterface *object_manager) {
    this->object_manager = object_manager;
}

std::vector<Php::Value> Factory::resolve_arguments(KindId requested_type, std::vector<Parameter> &parameters,
                                                   std::unordered_map<std::string, Argument> &arguments) {
    // Get default arguments from config, merge with supplied arguments
    auto default_arguments = config->get_arguments(requested_type);
    if (default_arguments != nullptr) {
        if (!default_arguments->empty()) {
            for (auto &[name, argument] : *default_arguments) {
                arguments[name] = argument;
            }
        } else {
            arguments.clear();
        }
    }

    return resolve_arguments_in_runtime(requested_type, parameters, arguments);
}

std::vector<Php::Value> Factory::resolve_arguments_in_runtime(KindId requested_type, std::vector<Parameter> &parameters,
                                                              std::unordered_map<std::string, Argument> &arguments) {
    std::vector<Php::Value> resolved_arguments;
    for (const auto &parameter : parameters) {
        if (arguments.find(parameter.get_name()) != arguments.end()) {
            // TODO: reuse find
            auto &argument = arguments[parameter.get_name()];
            resolved_arguments.push_back(resolve_argument(arguments[parameter.get_name()], parameter, requested_type));
        } else if (parameter.is_required()) {
            if (parameter.get_type().has_value()) {
                auto parameter_kind = config->get_kind_table().get_id_or_insert(parameter.get_type().value());
                auto argument = Argument(ArgumentType::Kind, parameter_kind);
                resolved_arguments.push_back(resolve_argument(argument, parameter, requested_type));
            } else {
                creation_stack.clear();
                std::cerr << "Missing required argument $" << parameter.get_name() << " of "
                          << config->get_kind_table().get_accessor(requested_type) << "." << std::endl;
                throw std::runtime_error("Missing required argument");
            }
        } else {
            // TODO: unchecked .value()
            auto argument = Argument(ArgumentType::Value, parameter.get_default_val().value());
            resolved_arguments.push_back(resolve_argument(argument, parameter, requested_type));
        }
    }

    return resolved_arguments;
}

Php::Value Factory::resolve_argument(Argument &argument, const Parameter &parameter, KindId requested_type) {
    auto default_value = parameter.get_default_val().has_value()
                         ? parameter.get_default_val().value()
                         : Php::Value(nullptr); // TODO: make null value a static constant
    return resolve_argument_simple(argument, default_value);
}

Php::Value Factory::resolve_argument_simple(Argument &argument, const Php::Value &default_value) {
    switch (argument.get_type()) {
        case Kind: {
            auto is_shared = config->is_shared(argument.get_kind());
            if (is_shared) {
                return object_manager->get(argument.get_kind()).value;
            } else {
                std::unordered_map<std::string, Argument> args; // TODO: constant anyway
                return object_manager->create(argument.get_kind(), args).value;
            }
        }
        case GlobalValue: {
            if (global_arguments.find(argument.get_global_value()) != global_arguments.end()) {
                return global_arguments[argument.get_global_value()];
            } else {
                return default_value;
            }
        }
        case Value: {
            return argument.get_value();
        }
        case Array: {
            if(argument.get_array().size()) {
                return parse_array(argument.get_array());
            } else {
                return argument.get_array();
            }
        }
    }

    return Php::Value();
}

Php::Value Factory::parse_array(Php::Value &array) {
    for(auto &[key, value] : array) {
        if(!value.isArray()) continue;

        auto argument = transformers::transform_argument(value, config->get_kind_table());
        array[key] = resolve_argument_simple(argument, value);
    }

    return array;
}
