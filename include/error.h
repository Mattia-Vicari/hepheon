#ifndef __ERROR_H__
#define __ERROR_H__

#include <iostream>

inline void error(const char* message) {
    std::cerr << "ERROR: " << message << std::endl;
}

inline void error(const char* message, const char* log) {
    std::cerr << "ERROR: " << message << "\n" << log << std::endl;
}


#endif  // __ERROR_H__