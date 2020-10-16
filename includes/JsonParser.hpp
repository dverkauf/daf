#ifndef _JSONPARSER_H_
#define _JSONPARSER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

namespace DAF {

class JsonParser {

private:
    std::unordered_map <std::string, std::any> _root;
    std::string _json;

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
    static JsonParser *parse_file(std::ifstream &file);

    JsonParser(std::string json) : _json{json} {};
    ~JsonParser() {};

    auto get(std::string address);

    std::string getRowJsonString();

    struct JsonEntity {
        std::string name;
        int type;
    };

    struct JsonObject : JsonEntity {
        std::vector<JsonEntity> fields;
    };

    struct JsonArray : JsonEntity {
        std::vector<JsonEntity> fields;
    };

    struct JsonString : JsonEntity {
        std::string value;
    };

    struct JsonNumber : JsonEntity {
        double value;
    };

    struct JsonBoolean : JsonEntity {
        bool value;
    };

    struct  JsonNull : JsonEntity {

    };
    
    

};


}

#endif