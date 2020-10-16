#include "JsonParser.hpp"

namespace DAF {

JsonParser *JsonParser::parse(std::string json) {
    return new JsonParser(json);
};
JsonParser *JsonParser::parse_file(std::string file_name) {
    std::ifstream file(file_name);
    return JsonParser::parse_file(file);
};
JsonParser *JsonParser::parse_file(std::ifstream &file) {
    return new JsonParser(std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>())));
};

auto JsonParser::get(std::string address) {};

std::string JsonParser::getRowJsonString() {
    return this->_json;
};

}