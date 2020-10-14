#ifndef _JSONPARSER_H_
#define _JSONPARSER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <any>

namespace DAF {

class JsonParser {

private:
    std::unordered_map <std::string, std::any> _root;

protected:

    enum types {
        OBJECT = 0,
        ARRAY,
        STRING,
        NUMBER,
        BOOLEAN,
        NULL_VALUE
    };

public:
    static JsonParser *parse(std::string json);
    static JsonParser *parse_file(std::string file_name);
    static JsonParser *parse_file(std::ifstream &
    
    file);

    auto get(std::string address);

};


}

#endif