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
    std::string prefix = __CLASS__ + "::"s + __METHOD__ + ": "s;
    _logger->trace(prefix + " option = " + _short + " " + _long);
    // iterate through args
    for(int a = 0; a < args.size(); a++) {
        _logger->trace(prefix + "Checking arg (" + args[a] + ")");
        
        // cut the '-'
        //std::string arg = args[a].substr(1);
        _logger->trace(prefix + "if(" + args[a] + " == (\"-" + _short + "\") || " + args[a] + " == (\"-" + _long + "\")) {");
        if(args[a] == ("-" + _short) || args[a] == ("-" + _long)) {
            _logger->trace(prefix + "Option found (" + (args[a] == ("-" + _short) ? _short : _long) + ")");
            _wasTriggered = true;
            args.erase(args.begin() + a);
            if(_takeValue) {
                _logger->trace(prefix + "taking parameter");
                if(args[a][0] == '-') {
                    std::string param = _short.length() == 0 ? _long : _short;
                    throw EXCEPTION(Exception::NO_VALUE_FOR_PARAMETER, param);
                }
                if(_canBeRepeated || _values.size() == 0) {
                    _values.push_back(args[a]);
                } else {
                    _values[0] = args[a];
                }
                args.erase(args.begin() + a);
            }
            a--;
        }
    }
    if(_isRequired && !_wasTriggered) {
        throw Exception(Exception::REQUIRED_PARAMETER_MISSING, _short + " " + _long);
    }
    if(_wasTriggered && (_callback != NULL || _callback_with_value != NULL)) {
        if(_callback != NULL) {
            _callback();
        } else if(_callback_with_value != NULL) {
            _callback_with_value(_values[0]);
        }
    }
    if(!_wasTriggered) {
        _logger->trace(prefix + "not found");
    }
    return *this;
};

Option &Option::required() {
    _isRequired = true;
    return *this;
};

Option &Option::takeValue() {
    _takeValue = true;
    return *this;
};

Option &Option::callback(Callable callback) {
    _callback_with_value = NULL;
    _callback = callback;
    return *this;
};

Option &Option::callback(Callable_with_value callback) {
    _callback = NULL;
    _callback_with_value = callback;
    return *this;
};

}