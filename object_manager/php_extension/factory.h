//
// Created by egordm on 09-09-19.
//

#pragma once


#include <phpcpp.h>

#include "../implementation/factory.h"

class Factory;
namespace php_extension {
    class Factory : public Php::Base {
    protected:
        object_manager::Factory factory;
        Php::Value object_manager_handle;

    public:
        Php::Value create(Php::Parameters &params);

        void set_object_manager(Php::Parameters &params);
    };
}