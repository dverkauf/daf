#include "Interactor.hpp"

std::string Interactor::readString() {
    std::string input;
    char c;
    bool enter_pressed = false;
    do {
        c = std::getchar();
        if(c == Interactor::KEY_ENTER) {
            enter_pressed = true;
        } else {
            input += c;
        }
    } while(! enter_pressed);
    return input;
};

void Interactor::put(std::string text) {
    Interactor::put(text, true);
};

void Interactor::put(std::string text, bool endl) {
    Interactor::put(text, Interactor::COLOR_FG_WHITE, Interactor::COLOR_BG_BLACK, endl);
};

void Interactor::put(std::string text, std::vector<const char *> styles) {
    Interactor::put(text, styles, true);
};

void Interactor::put(std::string text, std::vector<const char *> styles, bool endl) {
    for(const char *style: styles) {
        std::cout << style;
    }
    std::cout << text << Interactor::RESET;
    if(endl) std::cout << std::endl;
};

void Interactor::put(std::string text, const char* color) {
    Interactor::put(text, color, true);
};

void Interactor::put(std::string text, const char* color, bool endl = true) {
    Interactor::put(text, color, Interactor::COLOR_BG_BLACK, endl);
};

void Interactor::put(std::string text, const char* color, const char* bg) {
    Interactor::put(text, color, bg, true);
};

void Interactor::put(std::string text, const char* color, const char* bg, bool endl) {
    std::cout << color << bg << text << Interactor::RESET;
    if(endl) std::cout << std::endl;
};

void Interactor::wait(std::string text) {
    Interactor::wait(text, true);
};

void Interactor::wait(std::string text, bool endl) {
    Interactor::put(text, endl);
    Interactor::readString();
};

bool Interactor::confirm(std::string question) {
    std::cout << question << std::endl;
    return true;
};

int Interactor::choose(std::string question, std::vector<std::string> choices) {
    return Interactor::choose(question, choices, 0);
};

int Interactor::choose(std::string question, std::vector<std::string> choices, int default_at) {
    Interactor::put(question + ":", Interactor::COLOR_FG_YELLOW, Interactor::COLOR_BG_BLACK);
    std::string cs;
    for(int c = 0; c < choices.size(); c++) {
        if(cs.length() != 0) cs += "/";
        if(default_at == c) {
            Interactor::put("(" + std::to_string(c+1) + ") " + choices[c], std::vector<const char *>{Interactor::BOLD});
            cs += std::to_string(c+1);
            continue;
        }
        Interactor::put("(" + std::to_string(c+1) + ") " + choices[c]);
    }
    Interactor::put("Enter your choice or ENTER for default [" + std::to_string(default_at+1) +  "]: ", false);
    std::string choice = Interactor::readString();
    int ci;
    if(choice.length() == 0)
        return default_at;
    ci = std::stoi(choice);
    if(ci < 1 || ci > choices.size())
        return default_at;
    return ci - 1;
};

std::string Interactor::prompt(std::string question) {
    return Interactor::prompt(question, "");
}

std::string Interactor::prompt(std::string question, std::string default_value) {
    Interactor::put(question, Interactor::COLOR_FG_YELLOW, Interactor::COLOR_BG_BLACK, false);
    if(default_value.length() > 0) {
        Interactor::put(" [" + default_value + "]", Interactor::COLOR_FG_YELLOW, Interactor::COLOR_BG_BLACK, false);
    }
    Interactor::put(": ", Interactor::COLOR_FG_YELLOW, Interactor::COLOR_BG_BLACK, false);
    std::string value = Interactor::readString();
    if(value.length() == 0) {
        return default_value;
    }
    return value;
};

void Interactor::warn(std::string warning) {
    std::cout << Interactor::COLOR_FG_RED << warning << Interactor::RESET << std::endl;
};

void Interactor::info(std::string text) {
    Interactor::info(text, true);
};

void Interactor::info(std::string text, bool endl) {
    Interactor::put(text, Interactor::COLOR_FG_BLUE, endl);
};

void Interactor::table(std::vector<std::vector<std::string>> values) {
    std::vector<std::string> headers;
    Interactor::table(values, headers);
};

void Interactor::table(std::vector<std::vector<std::string>> values, std::vector<std::string> headers) {
    Table t(values, headers);
    std::cout << t;
};

void Interactor::Table::init(std::vector<std::vector<std::string>> rows, std::vector<std::string> headers) {
    #ifdef __LOGGER__
    Poco::Logger &logger= Poco::Logger::get(__LOGGER__);
    logger.trace("Interactor::Table::init");
    #endif
    this->rows = rows;
    this->headers = headers;
    this->numrows = rows.size();
    #ifdef __LOGGER__
    logger.trace("Interactor::Table::init this->numrows=" + std::to_string(this->numrows));
    #endif
    if(this->numrows == 0) {
        throw new InteractorException(InteractorException::REASON_NO_ROWS_FOUND);
    }
    this->numcols = rows.at(0).size();
    #ifdef __LOGGER__
    logger.trace("Interactor::Table::init this->numcols=" + std::to_string(this->numcols));
    #endif
    for(std::vector<std::string> &row: this->rows)  {
        if(this->numcols != row.size()) {
            throw new InteractorException(InteractorException::REASON_ROWS_WITH_DEFFERENT_NUMCOLS);
        }
    }
    if(headers.size() != 0 and this->numcols != headers.size()) {
        throw new InteractorException(InteractorException::REASON_HEADERS_NUM_MISMATCH);
    }
    #ifdef __LOGGER__
    logger.trace("Interactor::Table::init measuring header widths headers.size()=" + std::to_string(headers.size()));
    #endif          
    this->col_widths.resize(this->numcols);
    if(headers.size() > 0) {
        for(std::size_t h = 0; h < this->numcols; h++) {
            this->col_widths[h] = headers[h].size();
            #ifdef __LOGGER__
            logger.trace("Interactor::Table::init headers[" + std::to_string(h) + "]=" + headers[h]);
            #endif
        }
    }
    for(std::size_t r = 0; r < this->numrows; r++) {
        for(std::size_t c = 0; c < this->numcols; c++) {
            std::size_t length = rows[r][c].length();
            if(length > this->col_widths[c]) {
                this->col_widths[c] = length; 
            }
        }
    }
    this->total_width = 0;
    for(std::size_t &width: this->col_widths) {
        this->total_width += width + 3;
    }
    this->total_width--;
}

Interactor::Table::Table(std::vector<std::vector<std::string>> rows, std::vector<std::string> headers) {
    init(rows, headers);
};

Interactor::Table::Table(std::vector<std::vector<std::string>> rows) {
    std::vector<std::string> headers;
    init(rows, headers);
};

bool Interactor::Table::hasHeaders() {
    return (this->headers.size() > 0);
};

std::ostream &operator<<(std::ostream &os, const Interactor::Table &t) {
    os << "+" << std::string(t.total_width, '-') << "+" << std::endl;
    if(t.headers.size() > 0) { // has headers
        os << "|";
        for(int h = 0; h < t.headers.size(); h++) {
            os << ' ' << Interactor::BOLD;
            os << std::setw(t.col_widths[h]) << std::setfill(' ') << t.headers[h];
            os << Interactor::RESET << " |";
        }
        os << std::endl;
        os << "+" << std::string(t.total_width, '-') << "+" << std::endl;
    }
    // output rows
    for(int r = 0; r < t.numrows; r++) {
        os << "|";
        for(int c = 0; c < t.numcols; c++) {
            os << ' ';
            os << std::setw(t.col_widths[c]) << std::setfill(' ') << t.rows[r][c];
            os << " |";
        }
        os << std::endl;
    }
    os << "+" << std::string(t.total_width, '-') << "+" << std::endl;
    return os;
};

std::size_t  Interactor::findLongestString(std::vector<std::string> strings) {
    std::size_t longest = 0;
    for(std::size_t s = 0; s < strings.size(); s++) {
        std::size_t length = strings.at(s).length();
        longest = (length > longest) ? length : longest;
    }
    return longest;
};