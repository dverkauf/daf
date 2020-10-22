#ifndef _DBASICCLASS_H_
#define _DBASICCLASS_H_

#include "Logger.hpp"

namespace DAF {

class DBasicClass {

    protected:

    static Logger *_logger;
    bool _debug_on{false};
    bool _verbose_on{false};

    public:

    bool debug(); // is debug active?
    void debug(bool setDebug); // activate or inactivate debugging output
    bool trace(); // is debug active?
    void trace(bool setTrace); // activate or inactivate debugging output
    void activateLoggingLevel(int level);
    bool isLoggingLevelActive(int level);


};

}

#define TRACE(text) _logger->trace(__FILE__ + ":"s + std::to_string(__LINE__) + " "s + prefix + " "s + text);

#endif