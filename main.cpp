#include <iostream>
#include <string>
#include <bitset>

#include "includes/Application.hpp"
#include "includes/Logger.hpp"
#include "includes/Command.hpp"
#include "includes/Option.hpp"
#include "includes/Exception.hpp"
#include "includes/Config.hpp"

using namespace DAF;

using namespace std::literals::string_literals;

class MyApp : public Application {

    private:

    //std::string _config_file_name;

    struct Facility {
        std::string name;
        std::vector<std::string> spots;
    };

    class MyConfig : public Config {
        public:
        MyConfig(std::string config_file_name) : Config(config_file_name) {};

        std::vector<Facility> getFacilities() {
            std::string prefix = "MyConfig::getFacilities";
            TRACE(prefix);
            std::vector<Facility> facilities;
            try {
                for(auto f : _config["facilities"]) {
                    Facility facility;
                    facility.name = f["name"];
                    for(auto s: f["spots"]) {
                        facility.spots.push_back(s);
                    }
                    facilities.push_back(facility);
                }
            } catch(nlohmann::detail::exception json_exception) {
                TRACE("Exception: "s + json_exception.what());
                throw Exception(Exception::CONFIG_JSON_EXCEPTION, json_exception.what());
            }
            return facilities;
        };

    };

    MyConfig *_config;

    public:

    void handleTest() {
        std::string prefix = "MyApp::handleTest";
        Interactor::warn("TEST!!!");
        TRACE(" using config file " + _config_file);
        _config = new MyConfig(_config_file);
        for(const auto &facility: _config->getFacilities()) {
            std::cout << facility.name << std::endl;
            for(const auto &spot: facility.spots) {
                std::cout << "\t" << spot << std::endl;
            }
        }

    };

    void config() override {
        std::string prefix = "MyApp::config";
        _useCommands = true;
        //this->_config_file = "./config.json";
        //this->debug(true);
        setLoggingLevels(std::bitset<Logger::numberOfLevels>(std::string(Logger::numberOfLevels, '1')));
        Command cmdTest("test", "A test command");
        cmdTest.callback(CALLBACK(MyApp::handleTest));
        Option optRest("r", "rest", "Go to rest");
        optRest.required().takeValue();
        Option optTest("t", "test", "Just a test option");
        Option optConfig("c", "config", "Specify an alternative config");
        optConfig.callback([this](std::string value) { this->_config_file = value; });
        optConfig.takeValue();
        cmdTest.need(optTest).need(optRest).need(optConfig);
        addCommand(cmdTest);
        TRACE("_config_file="s + _config_file);
        
    };

    void run() override {
        std::string prefix = "MyApp::run: ";
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