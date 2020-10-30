#include "HTTPClient.hpp"

namespace DAF {

HTTPResponse::HTTPResponse(std::stringstream &ss) {
    std::cout << ss.str() << std::endl;
};

HTTPClient::HTTPClient() {
    _logger->activate(Logger::Level::TRACE);
    curl = curl_easy_init();
};

HTTPClient::~HTTPClient() {
    if(curl) {
        curl_easy_cleanup(curl);
    }
};

HTTPResponse *HTTPClient::get(const std::string &url) {
    std::string prefix = "HTTPClient::get";
    TRACE("url=" + url);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    CURLcode code = curl_easy_perform(curl);
    if(code != CURLE_OK) {
        std::string reason{"Failed to perform request (CURL error: "};
        reason += curl_easy_strerror(code);
        reason += ")";
        throw HTTPClientException(reason);
    }
    std::stringstream ss;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [&ss] (void *contents, size_t size, size_t nmemb, void *userp) -> size_t {
        size_t realsize = (size_t) size * nmemb;
        std::string s((const char *) contents, realsize);
        ss << s;
        return realsize;
    });
    HTTPResponse *res = new HTTPResponse(ss); 
    return res;
};


std::string HTTPClient::version() {
    curl_version_info_data *curl_info = curl_version_info(CURLVERSION_NOW);
    std::string v{_VERSION_};
    v += " (curl version:" + std::string{curl_info->version} + ")";
    return v;
};



}