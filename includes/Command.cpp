#include "Command.hpp"

namespace DAF {

Command::Command(std::string name, std::string description) : _name{name}, _description{description}, _callback{Command::genericCallBack} {};
Command::Command(std::string name, std::string description, std::function<void()> callback) : _name{name}, _description{description}, _callback{callback} {};

Command &Command::need(Option &option) {

};

Command &Command::callback(std::function<void()> callback) {
    _callback = callback;
    return *this;
};

Command &Command::help(std::string text) {
    this->_help = text;
    return *this;
};

void Command::run() {
    this->_callback();
};

void Command::genericCallBack() {};

}