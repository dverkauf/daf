#ifndef _OPTION_H_
#define _OPTION_H_

#include <string>

namespace DAF {

class Option {

    private:

    std::string _short;
    std::string _long;
    bool _take_value;
    std::string _value;

    public:

    Option();
    Option(std::string s, bool take_value = false) : _short{s}, _take_value{take_value} {};
    Option(std::string s, std::string l, bool take_value = false) : _short{s}, _long{l}, _take_value{take_value} {};

    std::string short_name();
    std::string long_name();
    std::string value();
    void value(std::string value);
    void fish(std::string line);

};

}

#endif