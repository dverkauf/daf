#include "Option.hpp"

namespace DAF {

Option &Option::bind(Application *app) {
    _app = app;
    return *this;
};

std::ostream& operator<<(std::ostream& os, const Option& o) {

    return os;
};

std::string Option::getHelp() {
    std::stringstream s;
    s << *this;
    return s.str();
};

std::string Option::value() {
    #undef __METHOD__
    #define __METHOD__ "value"
    if(_values.size() > 0) {
        return _values[0];
    }
    return NULL;
};

std::vector<std::string> Option::values() {
    #undef __METHOD__
    #define __METHOD__ "values"
    return _values;
};

bool Option::triggered() {
    return _wasTriggered;
};

Option &Option::feed(std::vector<std::string> &args) {
    #undef __METHOD__
    #define __METHOD__ "feed"
    _logger->trace(__CLASS__ + "::"s + __METHOD__);
    // iterate through args
    for(int a = 0; a < args.size(); a++) {
        _logger->trace(__CLASS__ + "::"s + __METHOD__ + " Checking arg (" + args[a] + ")");
        if(args[a][0] != '-') {
            throw EXCEPTION(Exception::WRONG_FORMAT_OF_PARAMETER, args[a]);
        }
        // cut the '-'
        std::string arg = args[a].substr(1);
        if(args[a] == ("-" +_short) || args[a] == ("-" + _long)) {
            _logger->trace(__CLASS__ + "::"s + __METHOD__ + " Option found (" + (args[a] == ("-" + _short) ? _short : _long) + ")");
            _wasTriggered = true;
            if(_takeValue) {
                a++;
                if(args[a][0] == '-') {
                    std::string param = _short.length() == 0 ? _long : _short;
                    throw EXCEPTION(Exception::NO_VALUE_FOR_PARAMETER, param);
                }
                if(_canBeRepeated || _values.size() == 0) {
                    _values.push_back(args[a]);
                } else {
                    _values[0] = args[a];
                }
                
            }
        }
    }
    if(_wasTriggered) {
        _callback();
    }
    return *this;
};

Option &Option::required() {
    _isRequired = true;
    return *this;
};

}