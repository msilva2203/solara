/**
 * @file solara.h
 * 
 * @author Marco Silva
 * @date 2025-11-18
 */

#pragma once

#include "common.h"

#include <string>

namespace solara {

    struct Settings {
        std::string input_file = "";
        std::string output_file = "";
    };

    /**
     * 
     */
    void parse_settings(i32 argc, char* argv[], Settings& out_settings);

    /**
     * 
     */
    void init(const Settings& settings);

} /* solara */
