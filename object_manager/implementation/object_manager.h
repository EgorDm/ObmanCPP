//
// Created by egordm on 08-09-19.
//

#pragma once

#include "../interfaces/object_manager_interface.h"
#include "config.h"
#include "factory.h"

using namespace object_manager::interface;
using namespace object_manager::structures;

namespace object_manager {
    class ObjectManager : public ObjectManagerInterface {
    protected:
        ConfigInterface* config; // TODO: managed by php!
        FactoryInterface* factory;

        std::unordered_map<KindId, Instance> shared_instances;
    public:
        ObjectManager(Config *config, Factory *factory, const std::unordered_map<KindId, Instance> &shared_instances)
                : config(config), factory(factory), shared_instances(shared_instances) {}

        Instance create(const KindId &id, std::unordered_map<std::string, Argument> &arguments) override;

        Instance create(KindAccessor type, std::unordered_map<std::string, Argument> &arguments) override;

        Instance &get(const KindId &id) override;

        Instance &get(KindAccessor type) override;

        void configure(std::map<std::string, Php::Value> &configuration) override;

        ConfigInterface &get_config() const;

        void set_config(ConfigInterface *config);

        FactoryInterface &get_factory() const;

        void set_factory(FactoryInterface *factory);

        const std::unordered_map<KindId, Instance> &get_shared_instances() const;

        void set_shared_instances(const std::unordered_map<KindId, Instance> &shared_instances);

        void add_shared_instance(KindId kind, const Instance &instance);
    };
};


