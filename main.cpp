#include <iostream>
#include <string>
#include <bitset>

#include "includes/Application.hpp"
#include "includes/Logger.hpp"
#include "includes/Command.hpp"
#include "includes/Option.hpp"

using namespace DAF;

class MyApp : public Application {

    public:

    void commandTestCallback() {
        
    };

    void config() override {
        this->setLoggingLevels(std::bitset<Logger::numberOfLevels>(std::string(Logger::numberOfLevels, '1')));
        this->addCommand(Command("test", "Just for testing"));
    };

    void run() override {
        for(const std::string &arg: this->argv()) {
            std::cout << arg << std::endl;
        }
    };

};

/*
int main(int argc, char *args[]) { 
    std::vector<std::string> argv(argc); 
    for(int c = 0; c < argc; c++) { 
        argv[c] = std::string(args[c]); 
    }
    //MyApp app(argc, argv);
    MyApp app; 
    app.run(); 
}
*/
LETS_DO_IT(MyApp);