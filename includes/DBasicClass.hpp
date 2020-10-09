#ifndef _DBASICCLASS_H_
#define _DBASICCLASS_H_

#include "Logger.hpp"

namespace DAF {

class DBasicClass {

    protected:

    Logger *_logger;
    bool _debug_on{false};
    bool _verbose_on{false};


};

}

#endif