#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
#include <vector>

namespace DAF {

struct Util {

    static std::string replace(std::string subject, const std::string &from, const std::string &to);
    bool exists();
    template <typename T>
    bool exists(T variable);
    static std::string vector2string(std::vector<std::string> vec);
    static std::string vector2string(std::vector<std::string> vec, std::string separator);

};

}

#endif