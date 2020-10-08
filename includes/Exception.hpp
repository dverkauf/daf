#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>
#include <vector>
#include <array>
#include <iostream>

#include "Util.hpp"

namespace DAF {

class Exception : public std::exception {

    private:

    int _reason;
    std::string _info;

    public:

    enum REASONS {

        UNKNOWN_COMMAND = 0,
        NO_COMMAND_SPECIFIED
    };
    static REASONS Reason;

    const std::vector<std::string> Messages {
        "Unkown command (%info%)",
        "No command specified"
    };

    Exception(int reason);
    Exception(int reason, std::string info);

    virtual const char* what() const noexcept override;

    const std::string getMessage() const;
    const std::string getInfo() const;
    const int reason() const;


};

}

#endif