//
// Created by egordm on 08-09-19.
//

#pragma once

#include "../implementation/config.h"
#include "../transformers/argument_transformer.h"

namespace php_extension {
    class Config : public Php::Base {
    protected:
        Php::Value relations;
        object_manager::Config instance;

    public:
        Config() : instance(nullptr) {}

        void __construct(Php::Parameters &params)
        {
            if(params.size() > 0) {
                set_relations(params);
            }
        }

        void set_relations(Php::Parameters &params) {
            relations = params[0];
//            config.set_relations(relations.implementation<RelationsInterface>());
           instance.set_relations(new object_manager::Relations(relations)); // TODO: this is a memory leak. Store first
        }

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

