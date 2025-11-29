/**
 * @file log.cpp
 */

#include "log.h"

#include <iostream>
#include <sstream>
#include <ctime>

namespace solara {

    static std::string log_level_name(const LogLevel level) {
        switch (level) {
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            case CRITICAL:
                return "CRITICAL";
            default:
                return "?";
        }
    }

    Logger::Logger(const std::filesystem::path& path) {
        output_file_.open(path);
        if (!output_file_.is_open()) {
            std::cerr << "Error opening log file: " << path << std::endl;
        }
    }

    Logger::~Logger() {
        output_file_.close();
    }

    void Logger::log(const LogLevel level, const std::string& message) {
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

        std::ostringstream ss;
        ss << "[" << timestamp << "] " << log_level_name(level) << ": " << message << std::endl;

        const std::string entry = ss.str();
        std::cout << entry;
        if (output_file_.is_open()) {
            output_file_ << entry;
            output_file_.flush();
        }
    }

} /* solara */