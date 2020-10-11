#include "DBasicClass.hpp"

namespace DAF {

bool DBasicClass::debug() {
    return _logger->isActive(Logger::Level::DEBUG);
};

void DBasicClass::debug(bool setDebug) {
    if(setDebug) {
        _logger->activate(Logger::Level::DEBUG);
    }
};

void DBasicClass::activateLoggingLevel(int level) {
    _logger->activate(level);
};

bool DBasicClass::isLoggingLevelActive(int level) {
    return _logger->isActive(level);
};

Logger *DBasicClass::_logger = new Logger();

}