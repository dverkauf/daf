#ifndef _OPTION_H_
#define _OPTION_H_

#include <string>
#include <ostream>
#include <sstream>
#include <functional>
#include <vector>

#include "DBasicClass.hpp"
#include "Exception.hpp"

#define _MAX_LENGTH_SHORT_ 1
#define _MAX_LENGTH_LONG_ 10
#define _MAX_LENGTH_DECRPTION_ 50

using namespace std::literals::string_literals;

namespace DAF {

class Application;

class Option : public DBasicClass{
    
    /*
    typedef std::function<void (void)> Callable;
    typedef std::function<void (std::string var)> Callable_with_value;
    */

    private:

    //Application *_app;

    // flags
    /*
    bool _haveShort{false};
    bool _haveLong{false};
    bool _haveCallback{false};
    bool _canBeRepeated{false};    
    */
    bool _takeValue{false};
    bool _isRequired{false};
    bool _wasTriggered{false};
    char _short;
    std::string _long;
    std::string _description;
    std::string _value;
    int *_flag;
    /*
    std::vector<std::string> _values;
    Callable _callback;
    Callable_with_value _callback_with_value;
    */

    public:

    //Option() {};
    /*
    Option(std::string s, std::string description) : _short{s}, _description{description} {
        _haveShort = true;
    };
    Option(std::string s, std::string description, Callable callback) : _short{s}, _description{description}, _callback{callback} {
        _haveShort = true;
    };
    Option(std::string s, std::string description, Callable_with_value callback) : _short{s}, _description{description}, _callback_with_value{callback} {
        _haveShort = true;
    };
    */
    Option(char s, std::string l, std::string description) : _short{s}, _long{l}, _description{description}, _flag{NULL} {};
    Option(char s, std::string l, std::string description, int *flag) : _short{s}, _long{l}, _description{description}, _flag{flag} {};
    /*
    Option(std::string s, std::string l, std::string description, Callable callback) : _short{s}, _long{l}, _description{description}, _callback{callback} {
        _haveShort = true;
        _haveLong = true;
    };
    Option(std::string s, std::string l, std::string description, Callable_with_value callback) : _short{s}, _long{l}, _description{description}, _callback_with_value{callback} {
        _haveShort = true;
        _haveLong = true;
    };*/
    
    //Option &bind(Application *app);

    char short_name() { return _short; };
    std::string long_name() { return _long; };
    int *flag() { return _flag; };
    void value(std::string value) { _value = value; };
    std::string value() { return _value; };
    //std::vector<std::string> values();
    //Option &feed(std::vector<std::string> &args); // feed with arguments
    Option &required();
    Option &takeValue();
    //Option &callback(Callable callback);
    //Option &callback(Callable_with_value callback);
    bool isRequired() { return _isRequired; };
    bool isTakingValue() { return _takeValue; };
    bool isTriggered() { return _wasTriggered; };
    void trigger() { _wasTriggered = true; };

    //bool is(std::string name) { return name == _short || name == _long; };
    std::string getHelp();

    friend std::ostream& operator<<(std::ostream& os, const Option& o);

};

}

#endif