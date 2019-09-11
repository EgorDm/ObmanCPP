//
// Created by egordm on 08-09-19.
//

#include "definition.h"

std::vector<Parameter> object_manager::Definition::get_parameters(KindId kind_id) {
    KindAccessor accessor = KindTable::get_instance().get_accessor(kind_id); // TODO fill
    if (definitions.find(kind_id) == definitions.end()) { // TODO: class reader
        Php::Object reflection("\\ReflectionClass", accessor);
        Php::Value constructor = reflection.call("getConstructor");
        std::vector<Parameter> result;

        if (constructor.isObject()) {
            for (auto &[key, parameter] : constructor.call("getParameters")) {
                auto class_object = parameter.call("getClass");
                auto class_name = class_object.isObject() ? std::optional<std::string>(class_object.call("getName"))
                                                          : std::nullopt;
                auto required = !parameter.call("isOptional").boolValue() &&
                                !parameter.call("isDefaultValueAvailable").boolValue();
                auto default_value = parameter.call("isDefaultValueAvailable").boolValue()
                                     ? std::optional<Php::Value>(parameter.call("getDefaultValue"))
                                     : std::nullopt;

                result.emplace_back(
                        parameter.call("getName"),
                        class_name,
                        required,
                        default_value
                );
            }
        }

        definitions[kind_id] = result;
    }

    return definitions[kind_id];
}

std::vector<std::string> object_manager::Definition::get_classes() {
    return std::vector<std::string>();
}
