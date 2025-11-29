/**
 * @file stringtable.cpp
 */

#include "stringtable.h"
#include "solara.h"

#include <iostream>
#include <sstream>

namespace solara {

    StringTable::StringTable(CompilerContext* ctx) {
        assert(ctx != nullptr);
        ctx_ = ctx;
    }

    u64 StringTable::add(const std::string_view string) {
        auto it = table.find(string);
        if (it != table.end()) {
            return it->second;
        }

        u64 index = strings.size();
        strings.emplace_back(string);
        table.emplace(string, index);

        std::ostringstream ss;
        ss << "Added new element to String Table at " << index << ": \"" << string << "\".";
        ctx_->logger_.log(
            DEBUG,
            ss.str()
        );

        return index;
    }

    u64 StringTable::get_index(const std::string_view string) {
        auto it = table.find(string);
        if (it != table.end()) {
            return it->second;
        }
        return 0;
    }

    std::string_view StringTable::get_string(const u64 index) {
        if (is_valid_index(index)) {
            return strings[index];
        }
        return "";
    }

    bool StringTable::is_valid_index(const u64 index) {
        return index < strings.size();
    }

    bool StringTable::is_valid_string(const std::string_view string) {
        return table.find(string) != table.end();
    }

}