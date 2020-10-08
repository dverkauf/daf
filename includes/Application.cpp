#include "Application.hpp"

namespace DAF {

void Application::init(const int &argc, char *argv[]) {
    _logger = new Logger(this->_loggingLevels);
    for(int c = 0; c < argc; c++) {
        _argv.push_back(std::string(argv[c]));
    }
    for(std::string &arg: _argv) {
        _logger->trace(arg);
    }
    _commands.push_back(Command("help", "Get some help")
        .callback(CALLBACK(Application::showHelp))
    );
};

const std::vector<std::string> &Application::argv() {
    return _argv;
};

void Application::setLoggingLevels(std::bitset<Logger::numberOfLevels> loggingLevels) {
    this->_loggingLevels = loggingLevels;
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

}