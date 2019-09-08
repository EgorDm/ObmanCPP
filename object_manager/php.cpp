#include "php.h"
#include <phpcpp.h>


extern "C" {
PHPCPP_EXPORT void *get_module() {
    static Php::Extension extension("object_manager", "1.0");

    Php::Class<php_extension::Config> config("EgorDm\\Obman\\Config");
    config.method<&php_extension::Config::set_relations>("setRelations");
    config.method<&php_extension::Config::set_cache>("setCache");
    config.method<&php_extension::Config::get_arguments>("getArguments");
    config.method<&php_extension::Config::is_shared>("isShared");
    config.method<&php_extension::Config::get_preference>("getPreference");
    config.method<&php_extension::Config::get_instance_type>("getInstanceType");
    config.method<&php_extension::Config::get_virtual_types>("getVirtualType");
    config.method<&php_extension::Config::extend>("extend");
    config.method<&php_extension::Config::get_preferences>("getPreferences");

    extension.add(std::move(config));

   /* Php::Class<php_extension::ObjectManager> object_manager("ObjectManager");
    object_manager.method<&php_extension::ObjectManager::get_instance>("getInstance");
    object_manager.method<&php_extension::ObjectManager::create>("create");
    object_manager.method<&php_extension::ObjectManager::get>("get");
    object_manager.method<&php_extension::ObjectManager::add_preference>("addPreference");
    object_manager.method<&php_extension::ObjectManager::add_argument>("addArgument");
    object_manager.method<&php_extension::ObjectManager::add_non_shared>("addNonShared");
    object_manager.method<&php_extension::ObjectManager::add_virtual_type>("addVirtualType");
    object_manager.method<&php_extension::ObjectManager::add_shared_instance>("addSharedInstance");*/
    //extension.add(std::move(object_manager));

    return extension;
}
}