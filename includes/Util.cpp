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

}