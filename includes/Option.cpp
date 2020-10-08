#include "Option.hpp"

namespace DAF {

std::ostream& operator<<(std::ostream& os, const Option& o) {

    return os;
};

std::string Option::getHelp() {
    std::stringstream s;
    s << *this;
    return s.str();
};

}