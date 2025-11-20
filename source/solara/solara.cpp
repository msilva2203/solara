/**
 * @file solara.cpp
 * 
 * @author Marco Silva
 * @date 2025-11-18
 */

#include "solara.h"
#include "lexer.h"

#include <iostream>

namespace solara {

    void parse_settings(i32 argc, char* argv[], Settings& out_settings) {
        enum class ParseState {
            None = 0,
            InputFile,
            OutputFile
        };

        ParseState parse_state = ParseState::InputFile;

        for (i32 i = 1; i < argc; i++) {
            const std::string arg = argv[i];

            if (arg.empty()) {
                continue;
            }

            if (arg.at(0) == '-') {
                if (arg.compare("-s") == 0) {
                    parse_state = ParseState::InputFile;
                } else if (arg.compare("-o") == 0) {
                    parse_state = ParseState::OutputFile;
                } else {
                    parse_state = ParseState::None;
                }
            }

            switch (parse_state) {
                case ParseState::InputFile:
                out_settings.input_file = arg;
                break;
                case ParseState::OutputFile:
                out_settings.output_file = arg;
                break;
                default:
                break;
            }
        }
    }

    void init(const Settings& settings) {
        std::cout << "SOLARA: " << settings.input_file << " outputing to " << settings.output_file << std::endl;


    }

} /* solara */
