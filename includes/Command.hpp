#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <vector>
#include <string>
#include <functional>

#include "Option.hpp"

namespace DAF {

class Command {

    private:

    std::string _name;
    std::string _description;
    std::function<void()> _callback;
    std::vector<Option> _options;
    std::string _help;

    protected:

    

    public:

    Command(std::string name, std::string description);
    Command(std::string name, std::string description, std::function<void()> callback);
    Command &need(Option &option);
    Command &callback(std::function<void()> callback);
    Command &help(std::string text);

    virtual void run();
    static void genericCallBack();

};

}

#endif