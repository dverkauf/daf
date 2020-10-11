#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <vector>
#include <string>
#include <functional>
#include <sstream>
#include <ostream>

#include "DBasicClass.hpp"
#include "Exception.hpp"
#include "Logger.hpp"
#include "ConsoleLoggingChannel.hpp"
#include "Command.hpp"
#include "Option.hpp"
#include "Interactor.hpp"

using namespace std::literals::string_literals;

namespace DAF {

class Application: public DBasicClass {
    #undef __CLASS__
    #define __CLASS__ "Application"

    protected:

    std::string _name;
    std::string _description;
    std::string _command;
    std::vector<std::string> _argv;
    std::bitset<Logger::numberOfLevels> _loggingLevels;
    std::vector<Command> _commands;
    bool _useCommands{true};
    bool _useDefaultCommands{true};
    std::vector<Option> _options;
    bool _useDefaultOptions{true};

    void processCommandLineArguments();

    public:

    virtual void run() = 0;
    virtual void config() = 0;

    void setLoggingLevels(std::bitset<Logger::numberOfLevels> loggingLevels);
    void setDescription(std::stringstream description);
    void setDescription(std::string description);
    void init(const int &argc, char *argv[]);
    const std::vector<std::string> &argv();
    Application &addCommand(const Command &command);
    Command &getCommand(std::string name) /* throw(Exception) */;
    Logger *logger();
    friend std::ostream& operator<<(std::ostream& os, const Application& a);
    std::string getHelp();
    void showHelp();
    void showHelpOnCommand(std::string command);
    bool isInOptions(std::string option_name);

};

}

#define CALLBACK(method) std::bind(&method, this)

#define LETS_DO_IT(CLASS) \
int main(int argc, char *argv[]) { \
    CLASS app; \
    try { \
        app.config(); \
        app.init(argc, argv); \
        app.run(); \
    } catch(Exception ex) { \
            app.activateLoggingLevel(Logger::Level::FATAL); \
            app.logger()->fatal(app.debug() ? ex.getDebugMessage() : ex.getMessage()); \
        exit(EXIT_FAILURE); \
    } \
}

#endif