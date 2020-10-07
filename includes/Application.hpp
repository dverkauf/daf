#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <vector>
#include <string>
#include <functional>

#include "DBasicClass.hpp"
#include "Logger.hpp"
#include "ConsoleLoggingChannel.hpp"
#include "Command.hpp"
#include "Option.hpp"
#include "Interactor.hpp"

namespace DAF {

class Application: public DBasicClass {

    protected:

    std::string _name;
    std::string _command;
    std::vector<std::string> _argv;
    std::bitset<Logger::numberOfLevels> _loggingLevels;
    std::vector<Command> _commands;

    public:

    virtual void run() = 0;
    virtual void config() = 0;

    void setLoggingLevels(std::bitset<Logger::numberOfLevels> loggingLevels);
    void init(const int &argc, char *argv[]);
    const std::vector<std::string> &argv();
    Application &addCommand(const Command &command);

};

}

#define CALLBACK(method) std::bind(&method, this)

#define LETS_DO_IT(CLASS) \
int main(int argc, char *argv[]) { \
    CLASS app; \
    app.config(); \
    app.init(argc, argv); \
    app.run(); \
}

#endif