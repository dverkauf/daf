#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <vector>
#include <string>
#include <functional>

#include "Application.hpp"
#include "Option.hpp"

namespace DAF {

class Application;

class Command {

    private:

    std::string _name;
    std::string _description;
    std::vector<Option> _options;
    std::string _help;

    protected:

    Application *_app;

    public:

    Command(const std::string &name, const std::string &description);
    void bind(const Application *app);
    Command &need(Option &option);
    Command &help(std::string text);
    template<class C>
    Command &callback( C *object, void (C::*func)() );

    virtual void run();

};

}

#endif