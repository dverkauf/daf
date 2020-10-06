#include "Command.hpp"

namespace DAF {

Command::Command(const std::string &name, const std::string &description) : _name{name}, _description{description} {};

void Command::bind(const Application *app) {
    this->_app = app;
};

Command &Command::need(Option &option) {
    this->_options.push_back(option);
};

Command &Command::help(std::string text) {
    this->_help = text;
    return *this;
};

template<class C>
Command &Command::callback( C *object, void (C::*func)() ) {
    object->*func();
};

}