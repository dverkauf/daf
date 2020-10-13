#include "Config.hpp"

namespace DAF {

Config::Config() {
    init(std::string(std::getenv("PATH")));
};

Config::Config(std::string config_file) : _config_file{config_file} {
    init(config_file);
};

void Config::init(std::string config_file) {

};

}