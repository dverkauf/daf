#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include "includes/HTTPClient.hpp"

int main(int argc, char *argv[]) {
    DAF::HTTPClient client;
    try {
        //client.get("http://standards-oui.ieee.org/oui.txt");
        DAF::HTTPResponse *response = client.get("http://127.0.0.1:8888/config.json");
        std::string body = response->getBody();
        std::cout << body << std::endl;
    } catch(DAF::HTTPClientException &e) {
        std::cerr << e.what() << "\n";
    }
    return EXIT_SUCCESS;
}