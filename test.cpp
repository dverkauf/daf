#include <string>
#include <iostream>
#include <fstream>
#include <vector>
//#include <source_location>

#include "includes/Util.hpp"
#include "includes/JsonParser.hpp"

using namespace DAF;

int main(int argc, char *argv[]) {
    JsonParser *parser = JsonParser::parse_file("./config.json");
    std::cout << parser->getRowJsonString() << std::endl;
}