/**
 * @file stringtable.h
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "common.h"

namespace solara {
    
    class StringTable {
    public:
        u64 add(const std::string_view string);
        u64 get_index(const std::string_view string);
        std::string_view get_string(const u64 index);

        bool is_valid_index(const u64 index);
        bool is_valid_string(const std::string_view string);

    private:
        std::vector<std::string> strings;
        std::unordered_map<std::string_view, u64> table;
    };

}