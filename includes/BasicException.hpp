#ifndef _ABSTRACTEXCEPTION_H_
#define _ABSTRACTEXCEPTION_H_

#include <exception>
#include <string>

#include "Util.hpp"

namespace DAF {

class BasicException : public std::exception {

    protected:
    std::string _message;
    std::string _info;

    BasicException(std::string message, std::string info) : _message{message}, _info{info} {};
    BasicException(std::string message, std::string info, std::string file_name, int line_number, std::string prefix) : 
        _message{std::string(file_name) + ":" + std::to_string(line_number) + " " + prefix + ": " + message}, _info{info} {};

    public:
    virtual const char *what() const noexcept {
        std::string msg = Util::replace(_message, "%info%", _info);
        std::size_t size = msg.length();
        char *buffer = new char[size];
        strncpy(buffer, msg.c_str(), size);
        return buffer;
    };


};

}

#endif