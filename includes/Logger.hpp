#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <bitset>
#include <string>
#include <exception>

#include "AbstractLoggingChannel.hpp"
#include "ConsoleLoggingChannel.hpp"

namespace DAF {

class Logger {

    private:

    std::bitset<9> _activeLevels;
    AbstractLoggingChannel *_channel;

    bool _usingDefaultChannel;

    public:

    static const int numberOfLevels = 9;

    enum Level {
        NONE = 0,
        FATAL,
        CRITICAL,
        ERROR,
        WARING,
        NOTICE,
        INFORMATION,
        DEBUG,
        TRACE
    };

    Logger();
    Logger(std::bitset<9> activeLevels);
    Logger(AbstractLoggingChannel *c);
    Logger(AbstractLoggingChannel *c, std::bitset<9> activeLevels);
    ~Logger();

    void activate(int level);
    void inactivate(int level);

    void fatal(std::string text);
    void critical(std::string text);
    void error(std::string text);
    void warning(std::string text);
    void notice(std::string text);
    void info(std::string text);
    void debug(std::string text);
    void trace(std::string text);

    void fatal(std::exception &ex);
    void critical(std::exception &ex);
    void error(std::exception &ex);
    void warning(std::exception &ex);
    void notice(std::exception &ex);
    void info(std::exception &ex);
    void debug(std::exception &ex);
    void trace(std::exception &ex);

    bool isActive(int level);

};

}

#endif