//
// Created by egordm on 09-09-19.
//

#pragma once


#include <phpcpp.h>

#include "../implementation/factory.h"

namespace php_extension {
    class Factory : public Php::Base {
    protected:
        object_manager::Factory instance;
        Php::Value object_manager_handle;
        Php::Value config_handle;
        Php::Value definitions_handle;

    public:
        Factory() : instance(nullptr, nullptr, nullptr, {}) {};

        void __construct(Php::Parameters &params);

        Php::Value create(Php::Parameters &params);

        void set_object_manager(Php::Parameters &params);

    public:
        object_manager::Factory &get_instance() {
            return instance;
        }
    };
}