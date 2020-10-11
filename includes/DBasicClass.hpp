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

    bool debug();
    void debug(bool setDebug);
    void activateLoggingLevel(int level);
    bool isLoggingLevelActive(int level);


};

}

#endif