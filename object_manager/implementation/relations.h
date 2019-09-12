//
// Created by egordm on 11-09-19.
//

#pragma once

#include "../interfaces.h"

namespace object_manager {
    class Relations : public interface::RelationsInterface {
    public:
        Relations() {}

        bool has(const KindAccessor &type) override;

        std::vector<std::string> get_parents(const KindAccessor &type) override;
    };
}


