#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>

namespace DAF {

struct Util {

    static std::string replace(std::string subject, const std::string &from, const std::string &to);

};

}

#endif