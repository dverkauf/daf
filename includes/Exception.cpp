#include "Exception.hpp"

namespace DAF{

Exception::Exception(int reason) : _reason{reason}, _info{std::string("")}, _file_name{NULL}, _line_number{0}, _class_name{NULL}, _method_name{NULL} {};
Exception::Exception(int reason, std::string info) : _reason{reason}, _info{info}, _file_name{NULL}, _line_number{0}, _class_name{NULL}, _method_name{NULL} {};
Exception::Exception(int reason, std::string info, const char *file_name, int line_number, const char *class_name, const char *method_name) 
    : _reason{reason}, _info{info}, _file_name{file_name}, _line_number{line_number}, _class_name{class_name}, _method_name{method_name} {};

const char* Exception::what() const noexcept {
    std::string msg = getMessage();
    std::size_t size = msg.length();
    char *buffer = new char[size];
    strncpy(buffer, msg.c_str(), size);
    return buffer;
};

const std::string Exception::getMessage() const {
    std::string msg = Messages[_reason];
    return Util::replace(msg, "%info%", _info);
};

const std::string Exception::getDebugMessage() const {
    std::stringstream msg;
    if(_file_name != NULL) {
        msg << _file_name << ":" << _line_number;
    }
    if(_class_name != NULL) {
        msg << " (" << _class_name;
        if(_method_name != NULL) {
            msg << "::" << _method_name;
        }
        msg << "): ";
    }
    //std::string msg = Messages[_reason];
    msg << Util::replace(Messages[_reason], "%info%", _info);
    return msg.str();
};

const std::string Exception::getInfo() const {
    return _info;
};

const int Exception::reason() const {
    return _reason;
};

}