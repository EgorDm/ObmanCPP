//
// Created by egordm on 05-09-19.
//

#pragma once

#include "accessor.h"
#include "datastructures/bidirectional_map.hpp"

using namespace object_manager::datastructures;

namespace object_manager::structures {
    class KindTable {
        BidirectionalMap<KindAccessor, KindId> table;
        KindId counter;

    public:
        KindTable() : table(), counter(0) {}

        KindId get_id_or_insert(const KindAccessor &a) {
            if(a.empty()) {
                auto i = 0;
            }

            if(!table.contains(a)) {
                table.insert(a, counter++);
            }

            return table.get(a);
        }

        std::optional<KindId> get_id(const KindAccessor &a) {
            if(table.contains(a)) return table.get(a); // TODO use iter result?
            else return std::nullopt;
        }

        KindAccessor& get_accessor(KindId id) {
            return table.get_rev(id); // TODO: make get opt
        }
    };
}