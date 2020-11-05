#include "HTTPClient.hpp"

namespace DAF {

HTTPResponse::HTTPResponse(std::stringstream &ss_headrs, std::stringstream &ss_body) {
    std::string prefix = "HTTPResponse::HTTPResponse";
    TRACE("HEADERS:\n" + ss_headrs.str() + "\n------------------------------------------------");
    TRACE("BODY:\n" + ss_body.str() + "\n------------------------------------------------");
};

HTTPResponse::HTTPResponse(std::string &headers, std::string &body) {
    std::string prefix = "HTTPResponse::HTTPResponse";
    std::regex re_status_line("^HTTP/([0-9\\.]+)\\s+([0-9]{3})\\s+(.+)$");
    std::regex re_header_line("^([^:]+):\\s+(.*)$");
    std::stringstream ss_headers;
    ss_headers << headers;
    bool status_line_not_found_yet{true};
    for(std::string line; std::getline(ss_headers, line, '\n');) {
        TRACE("line: " + line);
        line = Util::trim(line);
        if(line.length() == 0) continue;
        std::smatch matches;
        if(status_line_not_found_yet && std::regex_match(line, matches, re_status_line)) {
            status_line_not_found_yet = false;
            char *end;
            _http_version = std::strtod(matches[1].str().c_str(), &end);
            _response_code = std::strtoul(matches[2].str().c_str(), &end, 10);
            _response_reason = matches[3];
            TRACE("HTTP Version: " + std::to_string(_http_version));
            TRACE("Respose code: " + std::to_string(_response_code));
            TRACE("Response reason: " + _response_reason);
        } else if(std::regex_match(line, matches, re_header_line)) {
            TRACE("HEADER name: " + matches[1].str() + " value: " + matches[2].str());
            _headers.push_back(new HTTPHeader(matches[1], matches[2]));
        } else {
            throw HTTPClientException("bad header (" + line + ")");
        }
    }
    if(status_line_not_found_yet) {
        throw HTTPClientException("status line not found");
    }
    _body = body;
};

HTTPClient::HTTPClient() {
    _logger->activate(Logger::Level::TRACE);
    _curl = curl_easy_init();
};

HTTPClient::HTTPClient(Proxy *proxy) {
    _logger->activate(Logger::Level::TRACE);
    _curl = curl_easy_init();
    setProxy(proxy);
};

HTTPClient::~HTTPClient() {
    if(_curl) {
        curl_easy_cleanup(_curl);
    }
};

size_t get_body(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = (size_t) size * nmemb;
    std::string *s = (std::string *) userp;
    s->append((char *)contents);
    return realsize;
};
size_t get_headers(char *buffer, size_t size, size_t nitems, void *userdata) {
    size_t realsize = (size_t) size * nitems;
    std::string *s = (std::string *) userdata;
    s->append(buffer);
    return realsize;
};

HTTPResponse *HTTPClient::_method(METHOD method, const std::string &url, const char *payload) {
    std::string prefix = "HTTPClient::_method";
    TRACE("url=" + url);
    //curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    _setopt(CURLOPT_URL, url);
    CURLcode code;
    switch(method) {
        case METHOD::CONNECT:
            // CONNECT needs a special implementation (see HTTPClient::connect)
            break;
        case METHOD::CUSTOM:
            /*
            When you change the request method by setting CURLOPT_CUSTOMREQUEST to something,
            you don't actually change how libcurl behaves or acts in regards to the particular 
            request method, it will only change the actual string sent in the request.
            */
            break;
        case METHOD::DELETE:
            _setopt(CURLOPT_CUSTOMREQUEST, _method_string(METHOD::DELETE));
            break;
        case METHOD::GET:
            _setopt(CURLOPT_HTTPGET, 1L);
            break;
        case METHOD::HEAD:
            _setopt(CURLOPT_NOBODY, 1L);
            break;
        case METHOD::OPTIONS:
            _setopt(CURLOPT_CUSTOMREQUEST, _method_string(METHOD::OPTIONS));
            _setopt(CURLOPT_NOBODY, 1L);
            break;
        case METHOD::PATCH:
            _setopt(CURLOPT_CUSTOMREQUEST, _method_string(METHOD::PATCH));
            break;
        case METHOD::POST:
            _setopt(CURLOPT_POST, 1L);
            _setopt(CURLOPT_POSTFIELDS, payload);
            break;
        case METHOD::PUT:
            _setopt(CURLOPT_CUSTOMREQUEST, _method_string(METHOD::PUT));
            break;
        case METHOD::TRACE:
            _setopt(CURLOPT_CUSTOMREQUEST, _method_string(METHOD::TRACE));
            break;
        default:
            throw HTTPClientException("Unknown method");
    }
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set method " + _method_string(method), code));
    }
    std::string body;
    std::string headers;
    _setopt(CURLOPT_WRITEDATA, (void *)&body);
    _setopt(CURLOPT_WRITEFUNCTION, get_body);
    _setopt(CURLOPT_HEADERDATA, (void *)&headers);
    _setopt(CURLOPT_HEADERFUNCTION, get_headers);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, (void *)&body);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, get_body);
    curl_easy_setopt(_curl, CURLOPT_HEADERDATA, (void *)&headers);
    curl_easy_setopt(_curl, CURLOPT_HEADERFUNCTION, get_headers);
    code = curl_easy_perform(_curl);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to perform request", code));
    }
    return new HTTPResponse(headers, body);
};

HTTPResponse *HTTPClient::_method(const char *method, const std::string &url) {
    HTTPResponse *res; 
    return res;
};

socket HTTPClient::connect(const std::string &url) {
    if( ! _proxy_is_set) {
        throw HTTPClientException("Proxy must be set before using method CONNECT");
    }
    curl_easy_setopt(_curl, CURLOPT_URL, url);
    curl_easy_setopt(_curl, CURLOPT_CONNECT_ONLY, 1L);
    CURLcode code = curl_easy_perform(_curl);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to perform request", code));
    }
    socket sockfd;
    code = curl_easy_getinfo(_curl, CURLINFO_ACTIVESOCKET, &sockfd);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to get socket file descriptor", code));
    }
    return sockfd;
};

// CURLcode curl_easy_setopt(CURL *handle, CURLOPT_POST, long post);
// CURLcode curl_easy_setopt(CURL *handle, CURLOPT_PUT, long put);
// curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "DELETE");

HTTPResponse *HTTPClient::get(const std::string &url) {
    // curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    std::string prefix = "HTTPClient::get";
    /*
    TRACE("url=" + url);
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    TRACE("");
    
    std::string body;
    std::string headers;
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, (void *)&body);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, get_body);
    curl_easy_setopt(_curl, CURLOPT_HEADERDATA, (void *)&headers);
    curl_easy_setopt(_curl, CURLOPT_HEADERFUNCTION, get_headers);
    CURLcode code = curl_easy_perform(_curl);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to perform request", code));
    }
    HTTPResponse *res = new HTTPResponse(headers, body); 
    return res;
    */
   return _method(METHOD::GET, url, (const char *)NULL);
};

void HTTPClient::setProxy(Proxy *proxy) {
    std::string prefix = "HTTPClient::setProxy";
    TRACE("host=" + proxy->host + " port=" + std::to_string(proxy->port));
    CURLcode code = curl_easy_setopt(_curl, CURLOPT_PROXY, proxy->host);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set proxy host", code));
    }
    code = curl_easy_setopt(_curl, CURLOPT_PROXYPORT, (long) proxy->port);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set proxy host", code));
    }
    if(proxy->user_name.length() > 0 && proxy->user_pass.length() > 0) {
        code = curl_easy_setopt(_curl, CURLOPT_PROXYUSERNAME, proxy->user_name);
        if(code != CURLE_OK) {
            throw HTTPClientException(_curl_error("Failed to set proxy user", code));
        }
        code = curl_easy_setopt(_curl, CURLOPT_PROXYPASSWORD, proxy->user_name);
        if(code != CURLE_OK) {
            throw HTTPClientException(_curl_error("Failed to set proxy password", code));
        }
        // for security reasons we delete the password after usage
        for(int c = 0; c < proxy->user_pass.length(); c++) {
            proxy->user_pass[c] = 0;
        }
    }
    _proxy_is_set = true;
};


std::string HTTPClient::version() {
    curl_version_info_data *curl_info = curl_version_info(CURLVERSION_NOW);
    std::string v{_VERSION_};
    v += " (curl version:" + std::string{curl_info->version} + ")";
    return v;
};

std::string HTTPClient::_curl_error(std::string error, CURLcode code) {
    std::string reason{error + " (CURL error: "};
    reason += curl_easy_strerror(code);
    reason += ")";
    return reason;
};

std::string HTTPClient::_method_string(unsigned short int method) {
    switch(method) {
        case METHOD::CONNECT:
            return NULL;
        case METHOD::CUSTOM:
            return NULL;            
       case METHOD::DELETE:
            return "DELETE"s;
        case METHOD::GET:
            return "GET"s;
        case METHOD::HEAD:
            return "HEAD"s;
        case METHOD::OPTIONS:
            return "OPTIONS"s;
        case METHOD::PATCH:
            return "PATCH"s;
        case METHOD::POST:
            return "POST"s;
        case METHOD::PUT:
            return "PUT"s;
        case METHOD::TRACE:
            return "TRACE"s;
        default:
            throw HTTPClientException("Unknown method");
    }
};

CURLcode HTTPClient::_setopt(CURLoption opt, long parameter) {
    CURLcode code = curl_easy_setopt(_curl, opt, parameter);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set proxy user", code));
    }
    return code;
};

CURLcode HTTPClient::_setopt(CURLoption opt, std::string parameter) {
    CURLcode code = curl_easy_setopt(_curl, opt, parameter.c_str());
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set proxy user", code));
    }
    return code;
};

CURLcode HTTPClient::_setopt(CURLoption opt, const char *parameter) {
    CURLcode code = curl_easy_setopt(_curl, opt, parameter);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set proxy user", code));
    }
    return code;
};

CURLcode HTTPClient::_setopt(CURLoption opt, void *parameter) {
    CURLcode code = curl_easy_setopt(_curl, opt, parameter);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set proxy user", code));
    }
    return code;
};

CURLcode HTTPClient::_setopt(CURLoption opt, size_t (*callback)(void *, size_t, size_t, void *)) {
    CURLcode code = curl_easy_setopt(_curl, opt, callback);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set proxy user", code));
    }
    return code;
};

CURLcode HTTPClient::_setopt(CURLoption opt, size_t (*callback)(char *, size_t, size_t, void *)) {
    CURLcode code = curl_easy_setopt(_curl, opt, callback);
    if(code != CURLE_OK) {
        throw HTTPClientException(_curl_error("Failed to set proxy user", code));
    }
    return code;
};

}