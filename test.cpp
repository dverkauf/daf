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
        client.get("http://www.heise.de/");
    } catch(DAF::HTTPClientException &e) {
        std::cerr << e << "\n";
    }
    return EXIT_SUCCESS;
}