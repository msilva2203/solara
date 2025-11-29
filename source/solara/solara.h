/**
 * @file solara.h
 * 
 * @author Marco Silva
 * @date 2025-11-18
 */

#pragma once

#include "common.h"
#include "stringtable.h"
#include "log.h"

#include <string>

namespace solara {

    struct CompilerSettings {
        std::string input_file_ = "";
        std::string output_file_ = "";
        std::filesystem::path log_output_file_;

        CompilerSettings() {
            log_output_file_ = "logs/solara.log";
        }
    };

    struct CompilerContext {
        CompilerSettings settings_;
        StringTable string_table_;
        Logger logger_;

        CompilerContext(const CompilerSettings& settings)
            : settings_(settings)
            , string_table_(this)
            , logger_(settings.log_output_file_)
        {}
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
