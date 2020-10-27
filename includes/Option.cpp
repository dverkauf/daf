#include "Option.hpp"

namespace DAF {

/*Option &Option::bind(Application *app) {
    _app = app;
    return *this;
};*/

std::string Option::getHelp() {
    std::stringstream s;
    s << *this;
    return s.str();
};

/*

std::vector<std::string> Option::values() {
    return _values;
};

bool Option::triggered() {
    return _wasTriggered;
};

Option &Option::feed(std::vector<std::string> &args) {
    std::string prefix = "Option::feed";
    TRACE("option = " + _short + " " + _long);
    // iterate through args
    for(int a = 0; a < args.size(); a++) {
        TRACE("Checking arg (" + args[a] + ")");
        
        // cut the '-'
        //std::string arg = args[a].substr(1);
        TRACE("if(" + args[a] + " == (\"-" + _short + "\") || " + args[a] + " == (\"-" + _long + "\")) {");
        if(args[a] == ("-" + _short) || args[a] == ("-" + _long)) {
            TRACE("Option found (" + (args[a] == ("-" + _short) ? _short : _long) + ")");
            _wasTriggered = true;
            args.erase(args.begin() + a);
            if(_takeValue) {
                TRACE("taking parameter");
                if(args[a][0] == '-') {
                    std::string param = _short.length() == 0 ? _long : _short;
                    throw Exception(Exception::NO_VALUE_FOR_PARAMETER, param);
                }
                */
                /*
                if(_canBeRepeated || _values.size() == 0) {
                    _values.push_back(args[a]);
                } else {
                    _values[0] = args[a];
                }
                */
               /*
                TRACE("option=" + _short + " setting _value=" + args[a]);
                _value = args[a];
                args.erase(args.begin() + a);
                TRACE("parameter value=" + _value);
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
        TRACE("not found");
    }
    return *this;
};
*/

Option &Option::required() {
    _isRequired = true;
    return *this;
};

Option &Option::takeValue() {
    _takeValue = true;
    return *this;
};

/*
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
*/

std::ostream& operator<<(std::ostream& os, const Option& o) {
    std::string s(1 + _MAX_LENGTH_SHORT_ + 1 + _MAX_LENGTH_LONG_ + 1 +_MAX_LENGTH_DECRPTION_ + 1, ' ');
    s.replace(0, 1 + _MAX_LENGTH_SHORT_, "-"s + o._short);
    std::string s_long = "-"s + o._long.substr(0, _MAX_LENGTH_LONG_);
    s.replace(1 + _MAX_LENGTH_SHORT_ + 1, s_long.length(), s_long);
    s.replace(1 + _MAX_LENGTH_SHORT_ + 1 + _MAX_LENGTH_LONG_ + 1, _MAX_LENGTH_DECRPTION_, o._description);
    os << s;
    return os;
};

}