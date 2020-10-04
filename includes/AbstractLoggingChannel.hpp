#ifndef _ABSTRACTLOGGINGCHANNEL_H_
#define _ABSTRACTLOGGINGCHANNEL_H_

#include <string>
#include <exception>

namespace DAF {

struct AbstractLoggingChannel {
    
    virtual void write(std::string text) = 0;

    virtual void fatal(std::string text) = 0;
    virtual void critical(std::string text) = 0;
    virtual void error(std::string text) = 0;
    virtual void warning(std::string text) = 0;
    virtual void notice(std::string text) = 0;
    virtual void info(std::string text) = 0;
    virtual void debug(std::string text) = 0;
    virtual void trace(std::string text) = 0;

    virtual void fatal(std::exception &ex) = 0;
    virtual void critical(std::exception &ex) = 0;
    virtual void error(std::exception &ex) = 0;
    virtual void warning(std::exception &ex) = 0;
    virtual void notice(std::exception &ex) = 0;
    virtual void info(std::exception &ex) = 0;
    virtual void debug(std::exception &ex) = 0;
    virtual void trace(std::exception &ex) = 0;

};

}

#endif