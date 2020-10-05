#include "Logger.hpp"

namespace DAF {

void Logger::fatal(std::string text) { if(isActive(Level::FATAL)) _channel->fatal(text); };
void Logger::critical(std::string text) { if(isActive(Level::CRITICAL)) _channel->critical(text); };
void Logger::error(std::string text) { if(isActive(Level::ERROR)) _channel->error(text); };
void Logger::warning(std::string text) { if(isActive(Level::WARING)) _channel->warning(text); };
void Logger::notice(std::string text) { if(isActive(Level::NOTICE)) _channel->notice(text); };
void Logger::info(std::string text) { if(isActive(Level::INFORMATION)) _channel->info(text); };
void Logger::debug(std::string text) { if(isActive(Level::DEBUG)) _channel->debug(text); };
void Logger::trace(std::string text) { if(isActive(Level::TRACE)) _channel->trace(text); };

void Logger::fatal(std::exception &ex) { if(isActive(Level::FATAL)) _channel->fatal(ex); };
void Logger::critical(std::exception &ex) { if(isActive(Level::CRITICAL)) _channel->critical(ex); };
void Logger::error(std::exception &ex) { if(isActive(Level::ERROR)) _channel->error(ex); };
void Logger::warning(std::exception &ex) { if(isActive(Level::WARING)) _channel->warning(ex); };
void Logger::notice(std::exception &ex) { if(isActive(Level::NOTICE)) _channel->notice(ex); };
void Logger::info(std::exception &ex) { if(isActive(Level::INFORMATION)) _channel->info(ex); };
void Logger::debug(std::exception &ex) { if(isActive(Level::DEBUG)) _channel->debug(ex); };
void Logger::trace(std::exception &ex) { if(isActive(Level::TRACE)) _channel->trace(ex); };

Logger::Logger() {
    _channel = new ConsoleLoggingChannel();
    _usingDefaultChannel = true;
};

Logger::Logger(std::bitset<9> activeLevels) : _activeLevels{activeLevels} {
    _channel = new ConsoleLoggingChannel();
    _usingDefaultChannel = true;
};

Logger::Logger(AbstractLoggingChannel *c) : _channel{c} {
    _usingDefaultChannel = false;
};

Logger::Logger(AbstractLoggingChannel *c, std::bitset<9> activeLevels) : _channel{c}, _activeLevels{activeLevels} {
    _usingDefaultChannel = false;
};

Logger::~Logger() {
    if(_usingDefaultChannel) {
        delete(_channel);
    }
};

void Logger::activate(int level) {
    if(Logger::Level::NONE <= level <= Logger::Level::TRACE) {
        _activeLevels.set(level, 1);
    }
};

void Logger::inactivate(int level) {
    if(Logger::Level::NONE <= level <= Logger::Level::TRACE) {
        _activeLevels.set(level, 0);
    }
};

bool Logger::isActive(int level) {
    if(Logger::Level::NONE <= level <= Logger::Level::TRACE) {
        return _activeLevels[level];
    }
    return false;
};

} // namespace DAF