#include "JsonParser.hpp"

namespace DAF {

JsonParser *JsonParser::parse(std::string json) {};
JsonParser *JsonParser::parse_file(std::string file_name) {
    std::ifstream file(file_name);
    return JsonParser::parse_file(file);
};
JsonParser *JsonParser::parse_file(std::ifstream &file) {
    
};

auto JsonParser::get(std::string address) {};

}