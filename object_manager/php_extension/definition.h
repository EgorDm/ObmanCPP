//
// Created by egordm on 09-09-19.
//

#pragma once


#include <phpcpp.h>
#include "../implementation/definition.h"


namespace php_extension {
    class Definition : public Php::Base {
    protected:
        object_manager::Definition instance;

    public:
        //Definition() {}

        // TODO: need to implement? Mb a global instance of kind table needed? Not threadsafe anyway
    };
}

