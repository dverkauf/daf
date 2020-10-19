#include "Command.hpp"

namespace DAF {

Command::Command(const std::string &name, const std::string &description) : _name{name}, _description{description} {};
Command::Command(const std::string &name, const std::string &description, Callable callback) : _name{name}, _description{description}, _callback{callback} {};

void Command::bind(Application *app) {
    this->_app = app;
};

Command &Command::help(std::string text) {
    this->_help = text;
    return *this;
};

Command &Command::callback(Callable callback) {
    this->_callback = callback;
    return *this;
};

void Command::invoke() {
    this->_callback();
};

std::ostream& operator<<(std::ostream& os, const Command& c) {
    os << "\t" << c._name << "\t\t" << c._description << std::endl;
    if(c._options.size() > 0) {
        os << "\t\tCommand options:" << std::endl;
        for(const Option option: c._options) {
            os << option;
        }
    }
    return os;
};

std::string Command::getHelp() {
    std::stringstream s;
    s << *this;
    return s.str();
};

const std::string Command::name() const {
    return _name;
};

const std::string Command::description() const {
    return _description;
};

void Command::feed(std::vector<std::string> &args) {
    for(Option &option: _options) {
        option.feed(args);
    }
};

Command &Command::need(Option &option) {
    return this->option(option);
};
Command &Command::need(Option *option) {
    return this->option(*option);
};

Command &Command::option(Option &option) {
    option.bind(_app);
    _options.push_back(option);
    return *this;
};

}