#include "Logger.hpp"

namespace DAF {

void Logger::fatal(std::string text) { if(isActive(Level::FATAL)) channel->fatal(text); };
void Logger::critical(std::string text) { if(isActive(Level::CRITICAL)) channel->critical(text); };
void Logger::error(std::string text) { if(isActive(Level::ERROR)) channel->error(text); };
void Logger::warning(std::string text) { if(isActive(Level::WARING)) channel->warning(text); };
void Logger::notice(std::string text) { if(isActive(Level::NOTICE)) channel->notice(text); };
void Logger::info(std::string text) { if(isActive(Level::INFORMATION)) channel->info(text); };
void Logger::debug(std::string text) { if(isActive(Level::DEBUG)) channel->debug(text); };
void Logger::trace(std::string text) { if(isActive(Level::TRACE)) channel->trace(text); };

void Logger::fatal(std::exception &ex) { if(isActive(Level::FATAL)) channel->fatal(ex); };
void Logger::critical(std::exception &ex) { if(isActive(Level::CRITICAL)) channel->critical(ex); };
void Logger::error(std::exception &ex) { if(isActive(Level::ERROR)) channel->error(ex); };
void Logger::warning(std::exception &ex) { if(isActive(Level::WARING)) channel->warning(ex); };
void Logger::notice(std::exception &ex) { if(isActive(Level::NOTICE)) channel->notice(ex); };
void Logger::info(std::exception &ex) { if(isActive(Level::INFORMATION)) channel->info(ex); };
void Logger::debug(std::exception &ex) { if(isActive(Level::DEBUG)) channel->debug(ex); };
void Logger::trace(std::exception &ex) { if(isActive(Level::TRACE)) channel->trace(ex); };

Logger::Logger() {
    channel = new ConsoleLoggingChannel();
    usingDefaultChannel = true;
};

Logger::Logger(AbstractLoggingChannel *c) : channel{c} {
    usingDefaultChannel = false;
};

Logger::~Logger() {
    if(usingDefaultChannel) {
        delete(channel);
    }
};

void Logger::activate(int level) {
    if(Logger::Level::NONE <= level <= Logger::Level::TRACE) {
        activeLevels.set(level, 1);
    }
};

void Logger::inactivate(int level) {
    if(Logger::Level::NONE <= level <= Logger::Level::TRACE) {
        activeLevels.set(level, 0);
    }
};

bool Logger::isActive(int level) {
    if(Logger::Level::NONE <= level <= Logger::Level::TRACE) {
        return activeLevels[level];
    }
    return false;
};

} // namespace DAF