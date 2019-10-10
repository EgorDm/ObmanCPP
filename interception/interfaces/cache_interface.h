//
// Created by egordm on 16-09-19.
//

#pragma once

#include <phpcpp.h>
#include <structures/accessor.h>

using namespace object_manager::structures;

namespace interception::interface {
    enum CacheCleanMode {
        CLEANING_MODE_ALL,
        CLEANING_MODE_OLD,
        CLEANING_MODE_MATCHING_TAG,
        CLEANING_MODE_NOT_MATCHING_TAG,
        CLEANING_MODE_MATCHING_ANY_TAG,
    };

    class CacheInterface {
    public:
        virtual bool test(std::string &identifier) = 0;

        virtual bool load(std::string &identifier) = 0;

        virtual bool save(bool data, std::string& identifier, std::vector<std::string> &tags, std::optional<int> lifetime) = 0;

        virtual bool clean(CacheCleanMode mode, std::vector<std::string> &tags) = 0;
    };
}
