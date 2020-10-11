#include <iostream>
#include <string>
#include <bitset>

#include "includes/Application.hpp"
#include "includes/Logger.hpp"
#include "includes/Command.hpp"
#include "includes/Option.hpp"
#include "includes/Exception.hpp"

using namespace DAF;

class MyApp : public Application {
    #undef __CLASS__
    #define __CLASS__ "MyApp"

    public:

    void handleTest() {
        Interactor::warn("TEST!!!");
    };

    void config() override {
        #undef __METHOD__
        #define __METHOD__ "config"
        this->_useCommands = false;
        //this->debug(true);
        this->setLoggingLevels(std::bitset<Logger::numberOfLevels>(std::string(Logger::numberOfLevels, '0')));
        this->addCommand(
            Command("test", "A test command")
                .callback(CALLBACK(MyApp::handleTest))
                .need(
                    Option("r", "rest")
                        .required()
                )
                .need(Option("t", "test"))
                
        );
    };

    void run() override {
        #undef __METHOD__
        #define __METHOD__ "run"        
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