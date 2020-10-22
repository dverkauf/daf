#ifndef _OPTION_H_
#define _OPTION_H_

#include <string>
#include <ostream>
#include <sstream>
#include <functional>
#include <vector>

#include "DBasicClass.hpp"
#include "Exception.hpp"

#define _MAX_LENGTH_SHORT_ 2
#define _MAX_LENGTH_LONG_ 10
#define _MAX_LENGTH_DECRPTION_ 50

using namespace std::literals::string_literals;

namespace DAF {

class Application;

class Option : public DBasicClass{
    #undef __CLASS__
    #define __CLASS__ "Option"

    typedef std::function<void (void)> Callable;
    typedef std::function<void (std::string var)> Callable_with_value;

    private:

    Application *_app;

    // flags

    bool _haveShort{false};
    bool _haveLong{false};
    bool _haveCallback{false};
    bool _takeValue{false};
    bool _canBeRepeated{false};
    bool _isRequired{false};

    bool _wasTriggered{false};

    std::string _short;
    std::string _long;
    std::string _description;
    std::vector<std::string> _values;
    Callable _callback;
    Callable_with_value _callback_with_value;

    public:

    //Option() {};
    Option(std::string s, std::string description) : _short{s}, _description{description} {
        _haveShort = true;
    };
    Option(std::string s, std::string description, Callable callback) : _short{s}, _description{description}, _callback{callback} {
        _haveShort = true;
    };
    Option(std::string s, std::string description, Callable_with_value callback) : _short{s}, _description{description}, _callback_with_value{callback} {
        _haveShort = true;
    };
    Option(std::string s, std::string l, std::string description) : _short{s}, _long{l}, _description{description} {
        _haveShort = true;
        _haveLong = true;
    };
    Option(std::string s, std::string l, std::string description, Callable callback) : _short{s}, _long{l}, _description{description}, _callback{callback} {
        _haveShort = true;
        _haveLong = true;
    };
    Option(std::string s, std::string l, std::string description, Callable_with_value callback) : _short{s}, _long{l}, _description{description}, _callback_with_value{callback} {
        _haveShort = true;
        _haveLong = true;
    };
    /*Option(std::string s, std::string description, bool take_value) : _short{s}, _description{description}, _takeValue{take_value} {
        _haveShort = true;
    };
    Option(std::string s, std::string description, bool take_value, Callable callback) : _short{s}, _description{description}, _takeValue{take_value}, _callback{callback} {
        _haveShort = true;
        _haveCallback = true;
    };
    */
    /*Option(const char *s, const char *l) : _short{std::string(s)}, _long{std::string(l)} {
        _haveShort = true;
        _haveLong = true;
    };*/
    
    /*
    Option(std::string s, std::string l, std::string description, bool take_value) : _short{s}, _long{l}, _description{description}, _takeValue{take_value} {
        _haveShort = true;
        _haveLong = true;
    };
    Option(std::string s, std::string l, std::string description, bool take_value, Callable callback) : _short{s}, _long{l}, _description{description}, _takeValue{take_value}, _callback{callback} {
        _haveShort = true;
        _haveLong = true;
        _haveCallback = true;
    };
    */

    Option &bind(Application *app);

    std::string short_name();
    std::string long_name();
    std::string value();
    std::vector<std::string> values();
    Option &feed(std::vector<std::string> &args); // feed with arguments
    Option &required();
    Option &takeValue();
    Option &callback(Callable callback);
    Option &callback(Callable_with_value callback);
    bool isRequired();
    bool triggered();
    bool is(std::string name) { return name == _short || name == _long; };
    std::string getHelp();

    friend std::ostream& operator<<(std::ostream& os, const Option& o);

};

}

#endif