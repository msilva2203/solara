/**
 * @file main.cpp
 * 
 * @author Marco Silva
 * @date 2025-11-18
 */

#include "solara/solara.h"

int main(int argc, char* argv[]) {
    // parse arguments
    solara::Settings settings;
    solara::parse_settings(argc, argv, settings);

    // init solara compiler
    solara::init(settings);

    return 0;
}