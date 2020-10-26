#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <functional>

#include "DBasicClass.hpp"
#include "Option.hpp"

namespace DAF {

class Application;

class Command : public DBasicClass {

    private:

    typedef std::function<void (void)> Callable;

    std::string _name;
    std::string _description;
    std::vector<Option> _options;
    std::string _help;
    Callable _callback;

    protected:

    Application *_app;

    public:

    Command(const std::string &name, const std::string &description);
    Command(const std::string &name, const std::string &description, Callable callback);
    //void bind(Application *app);
    //void feed(std::vector<std::string> &args); // feed with arguments
    Command &need(Option &option) { return this->option(option); }; // need an option with value
    Command &option(Option &option); // need an option with value
    Command &help(std::string text);
    Command &callback(Callable callback);
    bool is(std::string name) { return _name == name; }
    void invoke() { _callback(); };
    std::string getHelp();
    const std::string name() const { return _name; };
    const std::string description() const { return _description; };
    //Option &option(std::string name); // find a certain option
    const std::vector<Option> options() const { return _options; };
    friend std::ostream& operator<<(std::ostream& os, const Command& c);

    //Command &need(Option *option); // need an option with value
    //bool need(std::string arg); // is this arg needed
    
    //virtual void run();

};

}

#endif