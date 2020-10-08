#include "Command.hpp"

namespace DAF {

Command::Command(const std::string &name, const std::string &description) : _name{name}, _description{description} {};

void Command::bind(Application *app) {
    this->_app = app;
};

Command &Command::need(Option &option) {
    this->_options.push_back(option);
    return *this;
};

Command &Command::help(std::string text) {
    this->_help = text;
    return *this;
};

Command &Command::callback(Callback callback) {
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

}