#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <cstdlib>
#include <string>

#include "DBasicClass.hpp"

namespace DAF {

class Config : public DBasicClass {

    private:

    std::string _config_file;

    public:

    Config();
    Config(std::string config_file);
    void init(std::string config_file);

};


}

#endif