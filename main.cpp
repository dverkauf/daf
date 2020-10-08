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

    public:

    void handleTest() {
        Interactor::warn("TEST!!!");
    };

    void config() override {
        this->setLoggingLevels(std::bitset<Logger::numberOfLevels>(std::string(Logger::numberOfLevels, '1')));
        this->addCommand(Command("test", "A test command")
            .callback(CALLBACK(MyApp::handleTest))
        );
    };

    void run() override {
        for(const std::string &arg: this->argv()) {
            std::cout << arg << std::endl;
        }
        // get my name
        _name = _argv.front();
        _argv.erase(_argv.begin());
        // we need at least a command
        if(_argv.size() == 0) {
            throw Exception(Exception::NO_COMMAND_SPECIFIED);
        }
        // get the command to run
        _command = _argv.front();
        _argv.erase(_argv.begin());
        try {
            Command command = getCommand(_command);
        } catch(const DAF::Exception &ex) {
            _logger->fatal(ex.getMessage());
        }
        // get that command`s arguments
        for(int a = 0; a < _argv.size(); a++) {
            auto arg = _argv[a];
            if(arg[0] == '-') {
                
            }
        }
        for(Command &command: _commands) {
            if(command.is(_command)) {
                command.invoke();
            }
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