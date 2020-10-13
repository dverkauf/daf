#include "Application.hpp"

namespace DAF {

void Application::init(const int &argc, char *argv[]) {
    #undef __METHOD__
    #define __METHOD__ "init"
    std::string prefix = __CLASS__ + "::"s + __METHOD__ + ": "s;
    //activateLoggingLevel(Logger::Level::TRACE);
    _logger->trace(prefix + "Application::init");
    //std::cout << "argc=" << argc << std::endl;
    // convert argv into vector of strings
    for(int c = 0; c < argc; c++) {
        //std::cout << "argv[" << c << "]=" << argv[c] << std::endl;
        _argv.push_back(std::string(argv[c]));
    }
    // get my name
    //std::cout << "_argv: " << Util::vector2string(_argv, " ") << std::endl;
    _name = _argv.front();
    _argv.erase(_argv.begin());
    //std::cout << "_argv: " << Util::vector2string(_argv, " ") << std::endl;
    _logger->trace(prefix + "_name=" + _name);
    // default commands
    if(_useDefaultCommands) {
        _logger->trace(prefix + "using default commands");
        _commands.push_back(Command("help", "Get some help")
            .callback(CALLBACK(Application::showHelp))
        );
    }
    if(_useCommands) {
        _logger->trace(prefix + "using commands");
        // we need at least a command
        if(_argv.size() == 0 || _argv[0][0] == '-') {
            _logger->trace(prefix + "_argv.size()="s + std::to_string(_argv.size()) + " _argv[0]="s + _argv[0]);
            throw EXCEPTION(Exception::NO_COMMAND_SPECIFIED);
        }
        // get the command to run
        _command = _argv.front();
        _argv.erase(_argv.begin());
        _logger->trace(prefix + "found command <" + _command + ">");
    }
    // default options
    if(_useDefaultOptions) {
        _logger->trace(prefix + "using default options");
        _options.push_back(Option("h"s, "help"s, "Show help"s).bind(this).feed(_argv));
        _options.push_back(Option("t"s, "trace"s, "Activate trace information"s, [this](){this->activateLoggingLevel(Logger::Level::TRACE);}).bind(this).feed(_argv));
        _options.push_back(Option("d"s, "debug"s, "Activate debug information"s, [this](){this->activateLoggingLevel(Logger::Level::DEBUG);}).bind(this).feed(_argv));
        _options.push_back(Option("v"s, "verbose"s, "Increase verbosity"s).feed(_argv));
    }
    _logger->trace(prefix + "debug is "s + (debug() ? "on"s : "off"s));
    if(_useCommands) {
        try {
            Command command = getCommand(_command);
            command.feed(_argv);
            command.invoke();
        } catch(const DAF::Exception &ex) {
           // _logger->fatal(ex.getMessage());
            throw ex;
        }
    }
    
};

const std::vector<std::string> &Application::argv() {
    return _argv;
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

Application &Application::addCommand(const Command &command) {
    
    //command.bind(this);
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
    throw EXCEPTION(Exception::REASONS::UNKNOWN_COMMAND, name);
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

void Application::processCommandLineArguments() {
    for(Option &option: _options) {
        option.feed(_argv);
    }
    getCommand(_command).feed(_argv);
};

bool Application::isInOptions(std::string option_name) {
    for(Option &o: _options) {
        if(o.is(option_name)) {
            return true;
        }
    }
    return false;
};

}