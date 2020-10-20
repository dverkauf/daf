#include "Application.hpp"

namespace DAF {

void Application::init(const int &argc, char *argv[]) {
    std::string prefix = "Application::init: ";
    //activateLoggingLevel(Logger::Level::TRACE);
    TRACE("Application::init");
    // convert argv into vector of strings
    for(int c = 0; c < argc; c++) {
        _argv.push_back(std::string(argv[c]));
    }
    // get my name
    _name = _argv.front();
    _argv.erase(_argv.begin());
    TRACE("_name=" + _name);
    if(_config_file.length() == 0) { // do we need to search for a default config file or was it overidden
        // search a default config file
        std::string config_file;
        if(std::getenv("HOME") != NULL) {
            std::string file = std::getenv("HOME");
            TRACE("HOME=" + file);
            file += "/." + Util::baseName(_name);
            TRACE("searching for config file " + file + " or " + file + ".json");
            TRACE("file " + file + " is " + (Util::fileIsReadable(file) ? "" : "not ") + "readable and is " + (Util::fileIsValidJson(file) ? "" : "not ") + "a json file");
            TRACE("file " + file + ".json is " + (Util::fileIsReadable(file + ".json") ? "" : "not ") + "readable and is " + (Util::fileIsValidJson(file + ".json"s) ? "" : "not ") + "a json file");
            if(Util::fileIsReadable(file) && Util::fileIsValidJson(file)) {
                config_file = file;
            } else if(Util::fileIsReadable(file + ".json") && Util::fileIsValidJson(file + ".json")) {
                config_file = file + ".json";
            }
        }
        if(config_file.length() == 0) { // we still did find a config file
            std::string file = "." + Util::baseName(_name);
            TRACE("searching for config file " + file + " or " + file + ".json");
            TRACE("file " + file + " is " + (Util::fileIsReadable(file) ? "" : "not ") + "readable and is " + (Util::fileIsValidJson(file) ? "" : "not ") + "a json file");
            TRACE("file " + file + ".json is " + (Util::fileIsReadable(file + ".json") ? "" : "not ") + "readable and is " + (Util::fileIsValidJson(file + ".json"s) ? "" : "not ") + "a json file");
            if(Util::fileIsReadable(file) && Util::fileIsValidJson(file)) {
                config_file = file;
            } else if(Util::fileIsReadable(file + ".json") && Util::fileIsValidJson(file + ".json")) {
                config_file = file + ".json";
            }
        }
        TRACE("default config file " + (config_file.length() == 0 ? "not found" : ("found (" + config_file + ")")));
        _config_file = config_file;
    }
    // default commands
    if(_useDefaultCommands) {
        TRACE("using default commands");
        _commands.push_back(Command("help", "Get some help")
            .callback(CALLBACK(Application::showHelp))
        );
    }
    if(_useCommands) {
        TRACE("using commands");
        // we need at least a command
        if(_argv.size() == 0 || _argv[0][0] == '-') {
            TRACE("_argv.size()="s + std::to_string(_argv.size()) + " _argv[0]="s + _argv[0]);
            throw new Exception(Exception::NO_COMMAND_SPECIFIED);
        }
        // get the command to run
        _command = _argv.front();
        _argv.erase(_argv.begin());
        TRACE("found command <" + _command + ">");
    }
    // default options
    if(_useDefaultOptions) {
        TRACE("using default options");
        _options.push_back(Option("h"s, "help"s, "Show help"s).bind(this).feed(_argv));
        _options.push_back(Option("t"s, "trace"s, "Activate trace information"s, [this](){this->activateLoggingLevel(Logger::Level::TRACE);}).bind(this).feed(_argv));
        _options.push_back(Option("d"s, "debug"s, "Activate debug information"s, [this](){this->activateLoggingLevel(Logger::Level::DEBUG);}).bind(this).feed(_argv));
        _options.push_back(Option("v"s, "verbose"s, "Increase verbosity"s).feed(_argv));
    }
    TRACE("debug is "s + (debug() ? "on"s : "off"s));
    if(_useCommands) {
        try {
            Command command = getCommand(_command);
            command.feed(_argv);
            command.invoke();
        } catch(const DAF::Exception &ex) {
            throw ex;
        }
    }
    
};

void Application::setLoggingLevels(std::bitset<Logger::numberOfLevels> loggingLevels) {
    //this->_loggingLevels = loggingLevels;
    _logger->setLevels(loggingLevels);
};

void Application::setDescription(std::stringstream description) {
    _description = description.str();
};

void Application::setDescription(std::string description) {
    _description = description;
};

Application &Application::addCommand(Command &command) {
    command.bind(this);
    this->_commands.push_back(command);
    return *this;
};

Command &Application::getCommand(std::string name) {
    #undef __METHOD__
    #define __METHOD__ "getCommand"
    _logger->trace(__CLASS__ + "::"s + __METHOD__ + " name="s + name);
    for(Command &c: _commands) {
        if(c.is(name)) {
            return c;
        }
    }
    throw Exception(Exception::REASONS::UNKNOWN_COMMAND, name);
};

Logger *Application::logger() {
    return _logger;
};

std::ostream& operator<<(std::ostream& os, const Application& a) {
    // Description, in case there is one
    if(a._description.size() != 0) {
        os << a._description << std::endl << std::endl;
    }
    // Usage
    os << "Basic usage: " << a._name << " <COMMAND> [OPTIONS]" << std::endl << std::endl;
    std::vector<std::string> headers {"name      ", "description"};
    std::vector<std::vector<std::string>> rows;
    for(const Command &command: a._commands) {
        std::vector<std::string> row {command.name(), command.description()};
        rows.push_back(row);
    }
    Interactor::printInColumns(rows, headers, os, 1);
    os << std::endl;
    os << "For help on a command try \"" << a._name << " help " << "<COMMAND>\"" << std::endl;
    return os;
}

std::string Application::getHelp() {
    std::stringstream help_stream;
    help_stream << *this;
    return help_stream.str();
};

void Application::showHelp() {
    std::cout << *this;
};

void Application::showHelpOnCommand(std::string command) {
    std::cout << "Basic usage: " << _name << " " << command << " [OPTIONS]" << std::endl << std::endl;
    std::cout << "Options:" << std::endl;
};

/*void Application::processCommandLineArguments() {
    for(Option &option: _options) {
        option.feed(_argv);
    }
    getCommand(_command).feed(_argv);
};*/

/*bool Application::isInOptions(std::string option_name) {
    for(Option &o: _options) {
        if(o.is(option_name)) {
            return true;
        }
    }
    return false;
};*/

/*const std::vector<std::string> &Application::argv() {
    return _argv;
};*/

}