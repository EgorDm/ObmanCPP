//
// Created by egordm on 05-09-19.
//

#pragma once


#include <unordered_map>

namespace object_manager::datastructures {

    template<typename L, typename R>
    class BidirectionalMap {
    protected:
        std::unordered_map<L, R> map;
        std::unordered_map<R, L> map_rev;

    public:
        BidirectionalMap() : map(), map_rev() {}

        bool contains(L &left) {
            return map.find(left) != map.end();
        }

        R& get(L &left) {
           return map[left];
        }

        bool insert(L left, R right) {
            return map.insert({left, right}).second && map_rev.insert({right, left}).second;
        }

        bool contains_rev(R &right) {
            return map_rev.find(right) != map_rev.end();
        }

        L& get_rev(R &right) {
            return map_rev[right];
        }

        ulong size() {
            return map.size();
        }
    };

}
