#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <chrono>
#include <iomanip>
#include <iostream>

namespace logger {

enum class log_level {
    INFO,
    WARNING,
    ERROR
};

inline void log(const char* message, log_level level) {
    auto raw_time = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(raw_time);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(raw_time.time_since_epoch()).count() % 1000;

    std::cout << std::put_time(std::localtime(&time), "%F %T") << '.';
    std::cout << std::setfill('0') << std::setw(3) << ms << " | ";

    switch (level) {
        case log_level::INFO:
            std::cout << "\033[1;32mINFO: " << message << "\033[0m" << std::endl;
            break;
        case log_level::WARNING:
            std::cout << "\033[1;33mWARNING: " << message << "\033[0m" << std::endl;
            break;
        case log_level::ERROR:
            std::cout << "\033[1;31mERROR: " << message << "\033[0m" << std::endl;
            break;
    }
}

inline void error(const char* message) {
    log(message, log_level::ERROR);
}

inline void error(const char* message, const char* extended_message) {
    log(message, log_level::ERROR);
    std::cout << extended_message << std::endl;
}

inline void warning(const char* message) {
    log(message, log_level::WARNING);
}

inline void info(const char* message) {
    log(message, log_level::INFO);  
}

}




#endif  // __LOGGER_H__