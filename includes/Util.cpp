#include "Util.hpp"

namespace DAF {

std::string Util::replace(std::string subject, const std::string &from, const std::string &to) {

    // find first occurrence
    std::size_t pos = subject.find(from);
    // replce and repeat until the end
    while(pos != std::string::npos) {
        subject.replace(pos, from.size(), to);
        pos = subject.find(from, pos + to.size());
    }
    return subject;
};

bool Util::exists() {
    return false;
};

template <typename T>
bool Util::exists(T variable) {
    return true;
};

std::string Util::vector2string(std::vector<std::string> vec) {
    return Util::vector2string(vec, " ");
};

std::string Util::vector2string(std::vector<std::string> vec, std::string separator) {
    std::string retval;
    for(std::string &s: vec) {
        retval += s + separator;
    }
    return retval;
};

}