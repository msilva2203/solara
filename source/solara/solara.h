/**
 * @file solara.h
 * 
 * @author Marco Silva
 * @date 2025-11-18
 */

#pragma once

#include "common.h"
#include "stringtable.h"

#include <string>

namespace solara {

    struct CompilerSettings {
        std::string input_file = "";
        std::string output_file = "";
    };

    struct CompilerContext {
        CompilerSettings settings;
        StringTable string_table;
    };

    /**
     * 
     */
    void parse_settings(i32 argc, char* argv[], CompilerSettings& out_settings);

    /**
     * 
     */
    void init(const CompilerSettings& settings);

} /* solara */
