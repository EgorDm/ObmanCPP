#include <phpcpp.h>
#include "config.h"
#include "factory.h"
#include "object_manager.h"


extern "C" {
PHPCPP_EXPORT void *get_module() {
    static Php::Extension extension("object_manager", "1.0");

    Php::Class<php_extension::Config> config("EgorDm\\Obman\\Cpp\\Config");
    config.method<&php_extension::Config::__construct>("__construct");
    config.method<&php_extension::Config::set_relations>("setRelations");
    config.method<&php_extension::Config::set_cache>("setCache");
    config.method<&php_extension::Config::get_arguments>("getArguments");
    config.method<&php_extension::Config::is_shared>("isShared");
    config.method<&php_extension::Config::get_preference>("getPreference");
    config.method<&php_extension::Config::get_instance_type>("getInstanceType");
    config.method<&php_extension::Config::get_virtual_types>("getVirtualTypes");
    config.method<&php_extension::Config::extend>("extend");
    config.method<&php_extension::Config::get_preferences>("getPreferences");
    extension.add(std::move(config));

    Php::Class<php_extension::Factory> factory("EgorDm\\Obman\\Cpp\\Factory");
    factory.method<&php_extension::Factory::__construct>("__construct");
    factory.method<&php_extension::Factory::create>("create");
    factory.method<&php_extension::Factory::set_object_manager>("setObjectManager");
    extension.add(std::move(factory));

    Php::Class<php_extension::ObjectManager> object_manager("EgorDm\\Obman\\Cpp\\ObjectManager");
    object_manager.method<&php_extension::ObjectManager::__construct>("__construct");
    object_manager.method<&php_extension::ObjectManager::create>("create");
    object_manager.method<&php_extension::ObjectManager::get>("get");
    object_manager.method<&php_extension::ObjectManager::configure>("configure");
    object_manager.method<&php_extension::ObjectManager::add_shared_instance>("addSharedInstance");
    extension.add(std::move(object_manager));

    return extension;
}
}