#include "Config.hpp"

namespace DAF {

Config::Config(const std::string &file) {
    std::string prefix = "Config::Config";
    _logger->trace(prefix + ": file=" + file);
    std::ifstream ifs(file);
    init(ifs);
};

Config::Config(std::ifstream &file) {
    std::string prefix = "Config::Config";
    _logger->trace(prefix);
    init(file);
};

void Config::init(std::ifstream &file) {
    std::string prefix = "Config::init";
    _logger->trace(prefix);
    _config = json::parse(file);
};

}