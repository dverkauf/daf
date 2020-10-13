#include <iostream>
#include <string>
#include <bitset>

#include "includes/Application.hpp"
#include "includes/Logger.hpp"
#include "includes/Command.hpp"
#include "includes/Option.hpp"
#include "includes/Exception.hpp"

using namespace DAF;

using namespace std::literals::string_literals;

class MyApp : public Application {
    #undef __CLASS__
    #define __CLASS__ "MyApp"

    private:

    std::string _config_file_name;

    public:

    void handleTest() {
        Interactor::warn("TEST!!!");
    };

    void config() override {
        #undef __METHOD__
        #define __METHOD__ "config"
        this->_useCommands = true;
        this->_config_file_name = "";
        //this->debug(true);
        this->setLoggingLevels(std::bitset<Logger::numberOfLevels>(std::string(Logger::numberOfLevels, '0')));
        this->addCommand(
            Command("test", "A test command")
                .callback(CALLBACK(MyApp::handleTest))
                .need(
                    Option("r", "rest", "Go to rest")
                        .required()
                        .takeValue()
                )
                .need(
                    Option("t", "test", "Just a test option")
                )
                .need(
                    Option("c", "config", "Specify an alternative config", [this](std::string value) { this->_config_file_name = value; })
                        .takeValue()
                )
        );
    };

    void run() override {
        #undef __METHOD__
        #define __METHOD__ "run"
        std::string prefix = __CLASS__ + "::"s + __METHOD__ + ": "s;
        logger()->trace(prefix);
        for(const std::string &arg: this->argv()) {
            std::cout << arg << std::endl;
        }
        std::cout << "_config_file_name=" << _config_file_name << std::endl;
        
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