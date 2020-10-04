#include "Application.hpp"

namespace DAF {

void Application::init(const int &argc, const char *argv[]) {
    logger = new Logger();
    for(int c = 0; c < argc; c++) {
        _argv.push_back(std::string(argv[c]));
    }
    for(std::string &arg: _argv) {
        logger->info(arg);
    }
};

}