#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <vector>
#include <string>
#include <functional>
#include <sstream>
#include <ostream>
#include <cstdlib>
#include <getopt.h>

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
    
    protected:

    std::string _name;
    std::string _description;
    std::string _command;
    std::string _help_on_command;
    std::vector<std::string> _argv;
    std::bitset<Logger::numberOfLevels> _loggingLevels;
    std::vector<Command> _commands;
    std::vector<Option> _options;
    bool _useCommands{true};
    bool _useDefaultCommands{true};
    bool _useDefaultOptions{true};
    std::string _config_file;

    int _trace_on = 0;
    int _debug_on = 0;
    int _verbose_on = 0;
    int _help_on = 0;


    public:
    
    void init(const int &argc, char *argv[]);
    //#####----- VRTUAL - must be overriden -----######
    // this function must be overridden by the application in order to set the configuration before init is executed
    virtual void config() = 0;
    // this function can be used to run any routine that needs to run each time. It will run after running the command
    virtual void run() = 0;
    
    void setLoggingLevels(std::bitset<Logger::numberOfLevels> loggingLevels);
    void setDescription(std::stringstream description);
    void setDescription(std::string description);
    
    Application &addCommand(Command &command);
    Command &getCommand(std::string name) /* throw(Exception) */;
    std::vector<Command> &commands() { return _commands; };
    void addOption(Option option) { _options.push_back(option); };
    Logger *logger();
    std::string getHelp();
    void showHelp();
    void showHelpOnCommand(std::string command);
    friend std::ostream& operator<<(std::ostream& os, const Application& a);

    //void processCommandLineArguments();
    //const std::vector<std::string> &argv();
    //bool isInOptions(std::string option_name);

};

}

#define ALL_OPTIONS_PARSED -1
#define UNKNOWN_OPTION_FOUND '?'
#define MISSING_AN_OPTION_ARGUMENT ':'
#define OPTION_IS_SETTING_A_FLAG 0

#define CALLBACK(method) std::bind(&method, this)

#define LETS_DO_IT(CLASS) \
int main(int argc, char *argv[]) { \
    CLASS app; \
    try { \
        app.config(); \
        app.init(argc, argv); \
        app.run(); \
    } catch(DAF::Exception ex) { \
        app.activateLoggingLevel(DAF::Logger::Level::FATAL); \
        app.logger()->fatal(app.debug() ? ex.getDebugMessage() : ex.getMessage()); \
        exit(EXIT_FAILURE); \
    } catch(...) { \
        app.logger()->fatal("Unknown exception!"); \
    } \
}

#define LETS_TRACE_IT(CLASS) \
int main(int argc, char *argv[]) { \
    CLASS app; \
    app.activateLoggingLevel(DAF::Logger::Level::TRACE); \
    try { \
        app.config(); \
        app.init(argc, argv); \
        app.run(); \
    } catch(DAF::BasicException ex) { \
        app.activateLoggingLevel(DAF::Logger::Level::FATAL); \
        app.logger()->fatal(ex.what()); \
        exit(EXIT_FAILURE); \
    } catch(...) { \
        app.logger()->fatal("Unknown exception!"); \
    } \
}

#endif