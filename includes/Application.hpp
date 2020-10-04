#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <vector>
#include <string>

#include "DBasicClass.hpp"
#include "Logger.hpp"
#include "ConsoleLoggingChannel.hpp"

namespace DAF {

class Application: public DBasicClass {

    private:

    std::vector<std::string> _argv;


    public:

    virtual void run() = 0;

    void init(const int &argc, const char *argv[]);

};

}

#define LETS_DO_IT(CLASS) \
int main(int argc, char **argv) { \
    CLASS app; \
    app.init(argc, argv); \
    app.run(); \
}

#endif