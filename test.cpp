#include <string>
#include <iostream>
#include <vector>

#include "includes/Util.hpp"

using namespace DAF;

int main(int argc, char *argv[]) {

    std::vector<std::string> args;
    for(int c = 0; c < argc; c++) {
        args.push_back(argv[c]);
    }

    std::cout << Util::vector2string(args, " ") << std::endl;

    std::cout << "prog name: " << args[0] << std::endl;

    args.erase(args.begin());

    std::cout << Util::vector2string(args, " ") << std::endl;

    //for(std::string arg: args) {
    for(int c = 0; c < args.size(); c++) {
        std::string arg = args.at(c);
        if(arg == "-t") {
            std::cout << "-t found!";
            args.erase(args.begin() + c);
            //std::cout << Util::vector2string(args, " ") << std::endl;
            std::cout << " value is " << args.at(c) << std::endl;
            args.erase(args.begin() + c);
            //std::cout << Util::vector2string(args, " ") << std::endl;
            c--;
        }
        if(arg == "-f") {
            std::cout << "-f found!" << std::endl;
            args.erase(args.begin() + c);
            c--;
        }
    }
}