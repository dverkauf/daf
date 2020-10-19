#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <array>
#include <iostream>

#include "Util.hpp"

namespace DAF {

class Exception : public std::exception {

    private:

    int _reason;
    std::string _info;
    const char *_file_name;
    const int _line_number;
    const char *_class_name;
    const char *_method_name;

    public:

    enum REASONS {

        UNKNOWN_COMMAND = 0,
        NO_COMMAND_SPECIFIED,
        NO_VALUE_FOR_PARAMETER,
        WRONG_FORMAT_OF_PARAMETER,
        REQUIRED_PARAMETER_MISSING,
        CONFIG_JSON_EXCEPTION
    };
    static REASONS Reason;

    const std::vector<std::string> Messages {
        "Unkown command (%info%)",
        "No command specified",
        "No value given for paramenter (%info%)",
        "Wrong format of parameter (%info%)",
        "A required parameter is missing (%info%)",
        "Something went wrong while parsing your config file (%info%)"
    };

    Exception(int reason);
    Exception(int reason, std::string info);
    Exception(int reason, std::string info, const char *file_name, int line_number, const char *class_name, const char *method_name);

    virtual const char* what() const noexcept override;

    const std::string getMessage() const;
    const std::string getDebugMessage() const;
    const std::string getInfo() const;
    const int reason() const;


};

}

#define EXCEPTION_0 Exception()

#define EXCEPTION_1(reason) \
    (_debug_on) ? \
        Exception(reason) : \
        Exception(reason, "", __FILE__, __LINE__, __CLASS__, __METHOD__)

#define EXCEPTION_2(reason, info) \
    (_debug_on) ? \
        Exception(reason, info) : \
        Exception(reason, info, __FILE__, __LINE__, __CLASS__, __METHOD__)

#define FUNC_CHOOSER(_f1, _f2, _f3, ...) _f3
#define FUNC_RECOMPOSER(argsWithParentheses) FUNC_CHOOSER argsWithParentheses
#define CHOOSE_FROM_ARG_COUNT(...) FUNC_RECOMPOSER((__VA_ARGS__, EXCEPTION_2, EXCEPTION_1, ))
#define NO_ARG_EXPANDER() ,,EXCEPTION_0
#define MACRO_CHOOSER(...) CHOOSE_FROM_ARG_COUNT(NO_ARG_EXPANDER __VA_ARGS__ ())
#define EXCEPTION(...) MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

/*
#define EXCEPTION_1(reason, info) \
    (_debug_on) ? \
        (DAF::Util::exists(info) ? Exception(reason, info) : Exception(reason)) : \
        (DAF::Util::exists(info) ? Exception(reason, info, __FILE__, __LINE__, __CLASS__, __METHOD__) : Exception(reason, "", __FILE__, __LINE__, __CLASS__, __METHOD__))
*/

#endif