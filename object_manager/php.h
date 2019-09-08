#ifndef OBJECT_MANAGER_LIBRARY_H
#define OBJECT_MANAGER_LIBRARY_H

#include "implementation/config.h"
#include "transformers/argument_transformer.h"

namespace php_extension {
    class Config : public Php::Base {
    protected:
        object_manager::Config config;

    public:
        void set_relations(Php::Parameters &params) {
            config.set_relations(object_manager::Relations(params[0]));
        }

        void set_cache(Php::Parameters &params) {}

        Php::Value get_arguments(Php::Parameters &params) {
            auto accessor = params[0].stringValue();
            auto id = config.get_kind_table().get_id_or_insert(accessor);
            auto args = config.get_arguments(id);
            if(args != nullptr) {
                return object_manager::transformers::serialize_arguments(*args, config.get_kind_table());
            } else {
                return Php::Array();
            }
        }

        Php::Value is_shared(Php::Parameters &params) {
            auto accessor = params[0].stringValue();
            auto id = config.get_kind_table().get_id_or_insert(accessor);
            return config.is_shared(id);
        }

        Php::Value get_instance_type(Php::Parameters &params) {
            auto accessor = params[0].stringValue();
            auto id = config.get_kind_table().get_id_or_insert(accessor);
            auto ret = config.get_instance_type(id);
            return config.get_kind_table().get_accessor(ret);
        }

        Php::Value get_preference(Php::Parameters &params) {
            auto accessor = params[0].stringValue();
            auto id = config.get_kind_table().get_id_or_insert(accessor);
            auto ret = config.get_preference(id);
            return config.get_kind_table().get_accessor(ret);
        }

        Php::Value get_virtual_types() {
            // TODO: cache this. Should never be called -> performace hit
            std::map<std::string, std::string> ret;
            auto kind_table = config.get_kind_table();
            for(const auto &[from, to] : config.get_virtual_types()) {
                ret.insert({kind_table.get_accessor(from), kind_table.get_accessor(to)});
            }
            return ret;
        }

        void extend(Php::Parameters &params) {
            auto conf  = params[0].mapValue();
            config.extend(conf);
        }

        Php::Value get_preferences() {
            // TODO: cache this. Should never be called -> performace hit
            std::map<std::string, std::string> ret;
            auto kind_table = config.get_kind_table();
            for(const auto &[from, to] : config.get_virtual_types()) {
                ret.insert({kind_table.get_accessor(from), kind_table.get_accessor(to)});
            }
            return ret;
        }
    };
}

#endif //OBJECT_MANAGER_LIBRARY_H