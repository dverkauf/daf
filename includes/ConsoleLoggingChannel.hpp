#ifndef _CONSOLELOGGINGCHANNEL_H_
#define _CONSOLELOGGINGCHANNEL_H_

#include <iostream>
#include <string>
#include <exception>

#include "AbstractLoggingChannel.hpp"
#include "Interactor.hpp"

namespace DAF {

class ConsoleLoggingChannel : public AbstractLoggingChannel {

    public:

    void write(std::string text) override;

    void fatal(std::string text) override;
    void critical(std::string text) override;
    void error(std::string text) override;
    void warning(std::string text) override;
    void notice(std::string text) override;
    void info(std::string text) override;
    void debug(std::string text) override;
    void trace(std::string text) override;

    void fatal(std::exception &ex) override;
    void critical(std::exception &ex) override;
    void error(std::exception &ex) override;
    void warning(std::exception &ex) override;
    void notice(std::exception &ex) override;
    void info(std::exception &ex) override;
    void debug(std::exception &ex) override;
    void trace(std::exception &ex) override;

    ~ConsoleLoggingChannel() {};

    static constexpr const char* CLEAR_LINE_TO_END      = "\033[0K";
    static constexpr const char* CLEAR_LINE_TO_START    = "\033[1K";
    static constexpr const char* CLEAR_LINE             = "\033[2K";

    static constexpr const char* RESET      = "\033[0m";
    static constexpr const char* BOLD       = "\033[1m";
    static constexpr const char* DIM        = "\033[2m";
    static constexpr const char* STANDOUT   = "\033[3m";
    static constexpr const char* UNDERSCORE = "\033[4m";
    static constexpr const char* BLINK      = "\033[5m";
    static constexpr const char* REVERSE    = "\033[7m";
    static constexpr const char* HIDDEN     = "\033[8m";

    static constexpr const char* COLOR_FG_BLACK     = "\033[30m";
    static constexpr const char* COLOR_FG_RED       = "\033[31m";
    static constexpr const char* COLOR_FG_GREEN     = "\033[32m";
    static constexpr const char* COLOR_FG_YELLOW    = "\033[33m";
    static constexpr const char* COLOR_FG_BLUE      = "\033[34m";
    static constexpr const char* COLOR_FG_MAGENTA   = "\033[35m";
    static constexpr const char* COLOR_FG_CYAN      = "\033[36m";
    static constexpr const char* COLOR_FG_WHITE     = "\033[37m";
    static constexpr const char* COLOR_FG_DEFAULT   = "\033[39m";

    static constexpr const char* COLOR_BG_BLACK     = "\033[40m";
    static constexpr const char* COLOR_BG_RED       = "\033[41m";
    static constexpr const char* COLOR_BG_GREEN     = "\033[42m";
    static constexpr const char* COLOR_BG_YELLOW    = "\033[43m";
    static constexpr const char* COLOR_BG_BLUE      = "\033[44m";
    static constexpr const char* COLOR_BG_MAGENTA   = "\033[45m";
    static constexpr const char* COLOR_BG_CYAN      = "\033[46m";
    static constexpr const char* COLOR_BG_WHITE     = "\033[47m";
    static constexpr const char* COLOR_BG_DEFAULT   = "\033[49m";

};

}

#endif