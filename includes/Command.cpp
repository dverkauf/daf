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

}