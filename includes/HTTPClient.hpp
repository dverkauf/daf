#ifndef _HTTPCLIENT_H_
#define _HTTPCLIENT_H_

#include <string>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <regex>
#include "curl/curl.h"

#include "DBasicClass.hpp"
#include "Util.hpp"

#define _VERSION_ "1.0"

#define EOL '\n'

namespace DAF {

typedef int socket;

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

struct HTTPHeader {
    std::string name;
    std::string value;
    HTTPHeader(std::string n, std::string v) : name{n}, value{v} {};
};

struct HTTPParameter {
    std::string key;
    std::string value;
};

class HTTPRequest : public DBasicClass {
    public:
};
class HTTPResponse : public DBasicClass {
    private:
    double _http_version;
    unsigned short int _response_code;
    std::string _response_reason;
    std::vector<HTTPHeader*> _headers;
    std::string _body;
    public:
    HTTPResponse(std::stringstream &ss_headrs, std::stringstream &ss_body);
    HTTPResponse(std::string &headrs, std::string &body);
    std::string &getBody() { return _body; };
};

struct Proxy {
    std::string host{""};
    unsigned short int port{0};
    std::string user_name{""};
    std::string user_pass{""};
    Proxy(std::string host, unsigned short int port): host{host}, port{port} {};
    Proxy(std::string host, unsigned short int port, std::string name, std::string pass): host{host}, port{port}, user_name{name}, user_pass{pass} {};
    // make sure to delete the password from memory
    ~Proxy() { for(int c = 0; c < user_pass.length(); c++) { user_pass[c] = 0; } };
};

class HTTPClient : public DBasicClass {

    private:

    enum METHOD {
        CUSTOM = 0,
        GET,        // The GET method requests a representation of the specified resource. Requests using GET should only retrieve data.
        HEAD,       // The HEAD method asks for a response identical to that of a GET request, but without the response body.
        POST,       // The POST method is used to submit an entity to the specified resource, often causing a change in state or side effects on the server.
        PUT,        // The PUT method replaces all current representations of the target resource with the request payload.
        DELETE,     // The DELETE method deletes the specified resource.
        CONNECT,    // The CONNECT method establishes a tunnel to the server identified by the target resource.
        OPTIONS,    // The OPTIONS method is used to describe the communication options for the target resource.
        TRACE,      // The TRACE method performs a message loop-back test along the path to the target resource.
        PATCH       // The PATCH method is used to apply partial modifications to a resource.
    };

    bool _proxy_is_set{false};
    const Proxy *_proxy{NULL};
    CURL *_curl{NULL};

    bool _verbose();

    HTTPResponse *_method(METHOD method, const std::string &url, const char *payload);
    HTTPResponse *_method(const char *method, const std::string &url);
    std::string _curl_error(std::string error, CURLcode code);
    std::string _method_string(unsigned short int m);
    CURLcode _setopt(CURLoption opt, long parameter);
    CURLcode _setopt(CURLoption opt, std::string parameter);
    CURLcode _setopt(CURLoption opt, const char *parameter);
    CURLcode _setopt(CURLoption opt, void *parameter);
    CURLcode _setopt(CURLoption opt, size_t (*callback)(void *, size_t, size_t, void *));
    CURLcode _setopt(CURLoption opt, size_t (*callback)(char *, size_t, size_t, void *));

    protected:

    public:

    HTTPClient();
    HTTPClient(Proxy *proxy);
    ~HTTPClient();
    // You're looking for the CURLOPT_CONNECT_ONLY curl_easy_setopt() option and the CURLINFO_LASTSOCKET curl_easy_getinfo() option.
    socket connect(const std::string &url);
    HTTPResponse *get(const std::string &url);

    void setProxy(Proxy *proxy);
    
    static std::string version();
    

};

}

#endif