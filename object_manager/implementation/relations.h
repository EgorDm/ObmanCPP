//
// Created by egordm on 11-09-19.
//

#pragma once

#include "../interfaces.h"

namespace object_manager {
    class Relations : public interface::RelationsInterface {
    public:
        Relations() {}

        bool has(KindAccessor &type) override;

        std::vector<std::string> get_parents(KindAccessor &type) override;
    };
}


