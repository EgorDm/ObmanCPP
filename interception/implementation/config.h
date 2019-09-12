//
// Created by egordm on 12-09-19.
//

#pragma once

#include <implementation/config.h>
#include "../interfaces/config.h"

namespace interception {
    class Config : public interface::ConfigInterface {
    protected:
        object_manager::Config *om_config;
        object_manager::interface::RelationsInterface *relations;
        object_manager::interface::DefinitionInterface *definitions;

        std::unordered_map<KindId, bool> intercepted;
        // TODO: config reader, scope list, cache

    public:
    private:
        bool has_plugins(KindId type) override;

        void initialize(std::vector<KindId> &class_definitons) override;

    protected:
        bool inherit_interception(KindId type);

        void initialize_uncompiled(std::vector<KindId> &class_definitons);

        void generate_intercepted(std::vector<KindId> &class_definitons);
    };

}
