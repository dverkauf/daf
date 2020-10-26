#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "BasicException.hpp"

namespace DAF {

class Exception : public BasicException {

    public:

    enum REASONS {
        UNKNOWN_COMMAND = 0,
        NO_COMMAND_SPECIFIED,
        NO_VALUE_FOR_PARAMETER,
        WRONG_FORMAT_OF_PARAMETER,
        REQUIRED_PARAMETER_MISSING,
        CONFIG_JSON_EXCEPTION,
        UNKNOWN_OPTION
    };

    const static inline std::vector<std::string> _messages = {
        "Unkown command (%info%)",
        "No command specified",
        "No value given for paramenter (%info%)",
        "Wrong format of parameter (%info%)",
        "A required parameter is missing (%info%)",
        "Something went wrong while parsing your config file (%info%)",
        "Unknown option (%info%)"
    };

    Exception(std::string message, std::string info) : BasicException{message, info} {};
    Exception(std::string message, std::string info, std::string file_name, int line_number, std::string prefix) : 
        BasicException{message, info, file_name, line_number, prefix} {};
    Exception(int reason) : BasicException{_messages.at(reason), ""} {};
    Exception(int reason, std::string file_name, int line_number, std::string prefix) : 
        BasicException{_messages.at(reason), "", file_name, line_number, prefix} {};
    Exception(int reason, std::string info) : BasicException{_messages.at(reason), info} {};
    Exception(int reason, std::string info, std::string file_name, int line_number, std::string prefix) : 
        BasicException{_messages.at(reason), info, file_name, line_number, prefix} {};
    
};


}

#endif