#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <functional>

#include "Option.hpp"

namespace DAF {

class Application;

class Command {

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
    void bind(Application *app);
    void feed(std::vector<std::string> &args); // feed with arguments
    Command &need(Option &option); // need an option with value
    Command &need(Option *option); // need an option with value
    bool need(std::string arg); // is this arg needed
    Command &option(Option &option); // need an option with value
    Command &help(std::string text);
    Command &callback(Callable callback);
    void invoke();
    bool is(std::string name) { return _name == name; }
    friend std::ostream& operator<<(std::ostream& os, const Command& c);
    std::string getHelp();
    //virtual void run();
    const std::string name() const;
    const std::string description() const;

};

}

#endif