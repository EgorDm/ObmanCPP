//
// Created by egordm on 08-09-19.
//

#include "utils.h"

using namespace object_manager;

std::string &utils::trim_slash(std::string &s) {
    if (s.size() > 0 && s[0] == '\\') s.erase(0, 1);
    return s;
}
