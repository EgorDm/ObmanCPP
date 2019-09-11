//
// Created by egordm on 08-09-19.
//

#pragma once

#include "../implementation/config.h"
#include "../transformers/argument_transformer.h"
#include "../wrappers/relations.h"

namespace php_extension {
    class Config : public Php::Base {
    protected:
        object_manager::Config instance;

    public:
        Config() : instance() {}

        void __construct(Php::Parameters &params)
        {
            if(params.size() > 0) {
                set_relations(params);
            }
        }

        void set_relations(Php::Parameters &params) {}

        void set_cache(Php::Parameters &params) {}

        Php::Value get_arguments(Php::Parameters &params);

        Php::Value is_shared(Php::Parameters &params);

        Php::Value get_instance_type(Php::Parameters &params);

        Php::Value get_preference(Php::Parameters &params);

        Php::Value get_virtual_types();

        void extend(Php::Parameters &params) {
            auto conf  = params[0].mapValue();
            instance.extend(conf);
        }

        Php::Value get_preferences();

    public:
        object_manager::Config &get_instance() {
            return instance;
        }
    };
}

