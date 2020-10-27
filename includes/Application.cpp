#include "Application.hpp"

namespace DAF {

void Application::init(const int &argc, char *argv[]) {
    std::string prefix = "Application::init: ";
    //activateLoggingLevel(Logger::Level::TRACE);
    TRACE("Application::init");
    // convert argv into vector of strings
    for(int c = 0; c < argc; c++) {
        _argv.push_back(std::string(argv[c]));
    }
    // get my name
    _name = _argv.front();
    _argv.erase(_argv.begin());
    TRACE("_name=" + _name);
    // get the command to run
    if(_useCommands) {
        TRACE("using commands");
        // we need at least a command
        if(_argv.size() == 0 || _argv[0][0] == '-') {
            TRACE("_argv.size()="s + std::to_string(_argv.size()) + " _argv[0]="s + _argv[0]);
            throw Exception(Exception::NO_COMMAND_SPECIFIED);
        }
        _command = _argv.front();
        _argv.erase(_argv.begin());
        TRACE("found command <" + _command + ">");
        if(_command == "help") { // help!!!
            if(_argv.size() != 0 && _argv[0][0] != '-') { // next word is a command to get help for
                _help_on_command = _argv.front();
                _argv.erase(_argv.begin());
                TRACE("help ask on command <" + _help_on_command + ">");
            }
        }
    }
    if(_config_file.length() == 0) { // do we need to search for a default config file or was it overidden
        // search a default config file
        TRACE("searching for default config file");
        std::string config_file;
        if(std::getenv("HOME") != NULL) {
            std::string file = std::getenv("HOME");
            TRACE("HOME=" + file);
            file += "/." + Util::baseName(_name);
            TRACE("searching for config file " + file + " or " + file + ".json");
            TRACE("file " + file + " is " + (Util::fileIsReadable(file) ? "" : "not ") + "readable and is " + (Util::fileIsValidJson(file) ? "" : "not ") + "a json file");
            TRACE("file " + file + ".json is " + (Util::fileIsReadable(file + ".json") ? "" : "not ") + "readable and is " + (Util::fileIsValidJson(file + ".json"s) ? "" : "not ") + "a json file");
            if(Util::fileIsReadable(file) && Util::fileIsValidJson(file)) {
                config_file = file;
            } else if(Util::fileIsReadable(file + ".json") && Util::fileIsValidJson(file + ".json")) {
                config_file = file + ".json";
            }
        }
        if(config_file.length() == 0) { // we still did find a config file
            std::string file = "." + Util::baseName(_name);
            TRACE("searching for config file " + file + " or " + file + ".json");
            TRACE("file " + file + " is " + (Util::fileIsReadable(file) ? "" : "not ") + "readable and is " + (Util::fileIsValidJson(file) ? "" : "not ") + "a json file");
            TRACE("file " + file + ".json is " + (Util::fileIsReadable(file + ".json") ? "" : "not ") + "readable and is " + (Util::fileIsValidJson(file + ".json"s) ? "" : "not ") + "a json file");
            if(Util::fileIsReadable(file) && Util::fileIsValidJson(file)) {
                config_file = file;
            } else if(Util::fileIsReadable(file + ".json") && Util::fileIsValidJson(file + ".json")) {
                config_file = file + ".json";
            }
        }
        TRACE("default config file " + (config_file.length() == 0 ? "not found" : ("found (" + config_file + ")")));
        _config_file = config_file;
    }
    // default commands
    if(_useDefaultCommands) {
        TRACE("using default commands");
        _commands.push_back(Command("help", "Get some help")
            .callback(CALLBACK(Application::showHelp))
        );
    }
    std::string opts = ":";
    std::vector<option> long_opts;
    // default options
    if(_useDefaultOptions) {
        TRACE("using default options");
        opts += "htdv";
        long_opts.push_back(option{"help", no_argument, &_help_on, 1});
        long_opts.push_back(option{"trace", no_argument, &_trace_on, 1});
        long_opts.push_back(option{"debug", no_argument, &_debug_on, 1});
        long_opts.push_back(option{"verbose", no_argument, &_verbose_on, 1});
    }
    if(_options.size() > 0) {
        for(Option &o: _options) {
            opts += o.short_name();
            if(o.isTakingValue()) {
                opts += ':';
            }
            long_opts.push_back(option{o.long_name().c_str(), o.isTakingValue() ? required_argument : no_argument, 0, o.short_name()});
        }
    }
    if(_useCommands) {
        for(Option &o: getCommand(_command).options()) {
            opts += o.short_name();
            if(o.isTakingValue()) {
                opts += ':';
            }
            long_opts.push_back(option{o.long_name().c_str(), o.isTakingValue() ? required_argument : no_argument, 0, o.short_name()});
        }
    }
            
    option *long_options = long_opts.data();
    int c;
    while(true) {
        int option_index = 0;
        c = getopt_long(argc, argv, opts.c_str(), long_options, &option_index);
        if(c == ALL_OPTIONS_PARSED || c == OPTION_IS_SETTING_A_FLAG) {
            break;
        }
        if(c == UNKNOWN_OPTION_FOUND) {
            throw Exception(Exception::REASONS::UNKNOWN_OPTION, std::to_string(c));
        }
        if(c == MISSING_AN_OPTION_ARGUMENT) {
            throw Exception(Exception::REASONS::NO_VALUE_FOR_PARAMETER, std::to_string(optopt));
        }
        if(_useDefaultOptions) {
            switch(c) {
                case 'h':
                    _help_on = 1;
                    break;
                case 't':
                    _trace_on = 1;
                    break;
                case 'd':
                    _debug_on = 1;
                    break;
                case 'v':
                    _verbose_on = 1;
                    break;
                default:
                    if(_useCommands) {
                        for(Option &o: getCommand(_command).options()) {
                            if(c == o.short_name()) {
                                o.trigger();
                                if(o.isTakingValue()) {
                                    o.value(std::string{optarg});
                                }
                                break;
                            }
                        }
                    }
            }
        }
    }
    if(_useCommands) {
        getCommand(_command).invoke();
    }
};

void Application::setLoggingLevels(std::bitset<Logger::numberOfLevels> loggingLevels) {
    //this->_loggingLevels = loggingLevels;
    _logger->setLevels(loggingLevels);
};

void Application::setDescription(std::stringstream description) {
    _description = description.str();
};

void Application::setDescription(std::string description) {
    _description = description;
};

Application &Application::addCommand(Command &command) {
    _useCommands = true;
    //command.bind(this);
    this->_commands.push_back(command);
    return *this;
};

Command &Application::getCommand(std::string name) {
    std::string prefix = "Application::getCommand";
    TRACE("name="s + name);
    for(Command &c: _commands) {
        if(c.is(name)) {
            return c;
        }
    }
    throw Exception(Exception::REASONS::UNKNOWN_COMMAND, name);
};

Logger *Application::logger() {
    return _logger;
};

std::ostream& operator<<(std::ostream& os, const Application& a) {
    // Usage
    os << Interactor::BOLD << "Basic usage: " << Interactor::RESET << a._name << " ";
    os << (a._help_on_command.length() == 0 ? "<COMMANAD>" : a._help_on_command) << " [OPTIONS]" << std::endl << std::endl;
    // Description, in case there is one
    if(a._description.size() != 0) {
        os << a._description << std::endl << std::endl;
    }
    // Commands
    if(a._help_on_command.length() == 0) { 
        os << Interactor::BOLD << Interactor::COLOR_BG_BLACK << Interactor::COLOR_FG_YELLOW << "\tAvailable commands:" << Interactor::RESET << std::endl;
        std::vector<std::string> headers {"name      ", "description"};
        std::vector<std::vector<std::string>> rows;
        for(const Command &command: a._commands) {
            std::vector<std::string> row {command.name(), command.description()};
            rows.push_back(row);
        }
        Interactor::printInColumns(rows, headers, os, 1);
        os << std::endl;
        os << Interactor::COLOR_BG_BLACK << Interactor::COLOR_FG_YELLOW << "For help on a command try \"" << a._name << " help " << "<COMMAND>\"" << Interactor::RESET << std::endl;
        os << std::endl;
    }
    // help on command
    if(a._help_on_command.length() != 0) {
        // Command description
        // Command options
        os << Interactor::BOLD << "\tCommand options:" << Interactor::RESET << std::endl;
        for(const Command &c: a._commands) {
            if(c.name() == a._help_on_command) {
                c.streamHelpOnOptions(os);
            }
        }
    }
    os << Interactor::BOLD << "\tGeneral options:" << Interactor::RESET << std::endl;
    for(const auto &o: a._options) {
        os << "\t" << o << std::endl;
    }
    os << std::endl;
    
    return os;
}

std::string Application::getHelp() {
    std::stringstream help_stream;
    help_stream << *this;
    return help_stream.str();
};

void Application::showHelp() {
    if(_help_on_command.length() != 0) {
        
    }
    std::cout << *this;
};

void Application::showHelpOnCommand(std::string command) {
    std::cout << "Basic usage: " << _name << " " << command << " [OPTIONS]" << std::endl << std::endl;
    std::cout << "Options:" << std::endl;
};

/*void Application::processCommandLineArguments() {
    for(Option &option: _options) {
        option.feed(_argv);
    }
    getCommand(_command).feed(_argv);
};*/

/*bool Application::isInOptions(std::string option_name) {
    for(Option &o: _options) {
        if(o.is(option_name)) {
            return true;
        }
    }
    return false;
};*/

/*const std::vector<std::string> &Application::argv() {
    return _argv;
};*/

}