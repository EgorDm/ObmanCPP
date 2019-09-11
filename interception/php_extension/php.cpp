//
// Created by egordm on 11-09-19.
//

#include <phpcpp.h>

extern "C" {
PHPCPP_EXPORT void *get_module() {
    static Php::Extension extension("interception", "1.0");

    return extension;
}
}