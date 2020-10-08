#include "Exception.hpp"

namespace DAF{

Exception::Exception(int reason) : _reason{reason}, _info{std::string("")} {};
Exception::Exception(int reason, std::string info) : _reason{reason}, _info{info} {};

const char* Exception::what() const noexcept {
    return getMessage().c_str();
};

const std::string Exception::getMessage() const {
    std::string msg = Messages[_reason];
    return Util::replace(msg, "%info%", _info);
};

const std::string Exception::getInfo() const {
    return _info;
};

const int Exception::reason() const {
    return _reason;
};

}