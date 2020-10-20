#include "ConsoleLoggingChannel.hpp"

namespace DAF {

void ConsoleLoggingChannel::write(std::string text) {
    std::cout << text << std::endl;
};

void ConsoleLoggingChannel::fatal(std::string text) {
    std::cout 
        << ConsoleLoggingChannel::COLOR_FG_RED 
        << ConsoleLoggingChannel::COLOR_BG_YELLOW 
        << "FATAL: " << text << ConsoleLoggingChannel::RESET << std::endl;
};

void ConsoleLoggingChannel::critical(std::string text) {
    std::cout 
        << ConsoleLoggingChannel::COLOR_FG_RED 
        << ConsoleLoggingChannel::COLOR_BG_WHITE 
        << "CRITICAL: " << text << ConsoleLoggingChannel::RESET << std::endl;
};

void ConsoleLoggingChannel::error(std::string text) {
    std::cout 
        << ConsoleLoggingChannel::COLOR_FG_CYAN 
        << "ERROR: " << text << ConsoleLoggingChannel::RESET << std::endl;
};

void ConsoleLoggingChannel::warning(std::string text) {
    std::cout 
        << ConsoleLoggingChannel::COLOR_FG_YELLOW 
        << "WARNING: " << text << ConsoleLoggingChannel::RESET << std::endl;
};

void ConsoleLoggingChannel::notice(std::string text) {
    std::cout 
        << ConsoleLoggingChannel::COLOR_FG_BLUE 
        << "NOTICE: " << text << ConsoleLoggingChannel::RESET << std::endl;
};

void ConsoleLoggingChannel::info(std::string text) {
    std::cout << ConsoleLoggingChannel::BOLD << "INFO: " << text << ConsoleLoggingChannel::RESET << std::endl;
};

void ConsoleLoggingChannel::debug(std::string text) {
    std::cout
        << ConsoleLoggingChannel::BOLD << ConsoleLoggingChannel::COLOR_FG_YELLOW
        << "DEBUG: " << text << ConsoleLoggingChannel::RESET << std::endl;
};

void ConsoleLoggingChannel::trace(std::string text) {
    std::cout
        << ConsoleLoggingChannel::BOLD << ConsoleLoggingChannel::COLOR_FG_RED << ConsoleLoggingChannel::COLOR_BG_YELLOW
        << "TRACE: " << text << ConsoleLoggingChannel::RESET << std::endl;
};

void ConsoleLoggingChannel::fatal(std::exception &ex) {
    this->fatal(std::string(ex.what()));
};

void ConsoleLoggingChannel::critical(std::exception &ex) {
    this->critical(std::string(ex.what()));
};

void ConsoleLoggingChannel::error(std::exception &ex) {
    this->error(std::string(ex.what()));
};

void ConsoleLoggingChannel::warning(std::exception &ex) {
    this->warning(std::string(ex.what()));
};

void ConsoleLoggingChannel::notice(std::exception &ex) {
    this->notice(std::string(ex.what()));
};

void ConsoleLoggingChannel::info(std::exception &ex) {
    this->info(std::string(ex.what()));
};

void ConsoleLoggingChannel::debug(std::exception &ex) {
    this->debug(std::string(ex.what()));
};

void ConsoleLoggingChannel::trace(std::exception &ex) {
    this->trace(std::string(ex.what()));
};

} // namespace DAF