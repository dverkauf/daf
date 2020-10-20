#ifndef _CONFIG_H_
#define _CONFIG_H_

//#include <cstdlib>
#include <string>
#include <fstream>

#include "DBasicClass.hpp"
#include "json.hpp"

using namespace std::literals::string_literals;
using json = nlohmann::json;

namespace DAF {

class Config : public DBasicClass {

    protected:

    json _config;

    public:

    Config(const std::string &file);
    Config(std::ifstream &file);
    void init(std::ifstream &file);

};


}

#endif