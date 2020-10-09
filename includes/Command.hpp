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

    typedef std::function<void (void)> Callback;

    std::string _name;
    std::string _description;
    std::vector<Option> _options;
    std::string _help;
    Callback _callback;

    protected:

    Application *_app;

    public:

    Command(const std::string &name, const std::string &description);
    void bind(Application *app);
    void feed(std::vector<std::string> &args); // feed with arguments
    Command &need(Option &option);
    Command &help(std::string text);
    Command &callback(Callback callback);
    void invoke();
    bool is(std::string name) { return _name == name; }
    bool need(std::string arg);
    friend std::ostream& operator<<(std::ostream& os, const Command& c);
    std::string getHelp();
    //virtual void run();
    const std::string name() const;
    const std::string description() const;

};

}

#endif