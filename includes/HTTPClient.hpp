#ifndef _HTTPCLIENT_H_
#define _HTTPCLIENT_H_

#include "curl/curl.h"
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>

#include "DBasicClass.hpp"

#define _VERSION_ "1.0"

#define EOL '\n'

namespace DAF {

class HTTPClientException : public std::exception {
    private:
    std::string _reason;
    public:
    HTTPClientException(std::string reason): _reason{reason}  {};
    const char *what() { return _reason.c_str(); }
    friend std::ostream &operator<<(std::ostream &os, HTTPClientException &e) {
        os << e._reason;
        return os;
    };
};
class HTTPRequest {
    public:
};
class HTTPResponse {
    public:
    HTTPResponse(std::stringstream &ss);
};

class HTTPClient : public DBasicClass {

    private:
    CURL *curl;

    protected:

    public:
    HTTPClient();
    ~HTTPClient();
    HTTPResponse *get(const std::string &url);
    
    static std::string version();
    

};

}

#endif