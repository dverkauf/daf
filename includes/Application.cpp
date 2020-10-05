#include "Application.hpp"

namespace DAF {

void Application::init(const int &argc, char *argv[]) {
    logger = new Logger(this->_loggingLevels);
    for(int c = 0; c < argc; c++) {
        _argv.push_back(std::string(argv[c]));
    }
    for(std::string &arg: _argv) {
        logger->trace(arg);
    }
};

const std::vector<std::string> &Application::argv() {
    return _argv;
};

void Application::setLoggingLevels(std::bitset<Logger::numberOfLevels> loggingLevels) {
    this->_loggingLevels = loggingLevels;
};

Application &Application::addCommand(const Command &command) {
    this->_commands.push_back(command);
    return *this;
};

}