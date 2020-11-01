#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <filesystem>

#include "json.hpp"

namespace DAF {

struct Util {

    static std::string replace(std::string subject, const std::string &from, const std::string &to);
    static std::string vector2string(std::vector<std::string> vec);
    static std::string vector2string(std::vector<std::string> vec, std::string separator);
    static bool fileIsReadable(const std::string &file);
    static std::string baseName(const std::string &path);
    static bool fileIsValidJson(const std::string &file);
    static std::string trim(const std::string &s);

    enum OS {
        UNKNOWN = 0,
        LINUX,
        MACOS,
        WINDOWS
    };

    static int getOS() {
        #if defined(__linux__)
        return OS::LINUX;
        #elif defined(__APPLE__)
        return OS::MACOS;
        #elif defined(_WIN32)
        return OS::WINDOWS
        #elif defined(_WIN64)
        return OS::WINDOWS;
        #endif
    };

};

}

#endif