/**
 * @file log.h
 */

#pragma once

#include "common.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace solara {

    enum LogLevel {
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    class Logger {
    public:
        Logger(const std::filesystem::path& path);
        ~Logger();

        void log(const LogLevel level, const std::string& message);

    private:
        std::ofstream output_file_;
    };

} /* solara */