//
// Created by egordm on 09-09-19.
//

#pragma once


#include <phpcpp.h>
#include "../implementation/object_manager.h"

namespace php_extension {
    class ObjectManager : public Php::Base {
    protected:
        Php::Value config_handle;
        Php::Value factory_handle;
        object_manager::ObjectManager instance;

    public:
        ObjectManager() : instance(nullptr, nullptr, {}) {}

        void __construct(Php::Parameters &params);

        Php::Value create(Php::Parameters &params);

        Php::Value get(Php::Parameters &params);

        void configure(Php::Parameters &params);

        void add_shared_instance(Php::Parameters &params);

    public:
        object_manager::ObjectManager &get_instance() {
            return instance;
        }
    };
}