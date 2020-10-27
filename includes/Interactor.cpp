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

/*
bool Interactor::confirm(std::string question) {
    
};
*/

bool Interactor::confirm(std::string question, bool defaultAnswer) {
    std::cout << question;
    std::cout << " [" << (defaultAnswer ? "Y" : "y") << ", " << (defaultAnswer ? "n" : "N") << "]" << std::endl;
    while(true) {
        std::string answer = Interactor::readString();
        if(answer == "" || answer == "y") {
            return true;
        }
        if(answer == "n") {
            return false;
        }
        Interactor::bold("Not a valid answer. Please enter y or n.");
    }
    return false;
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
            Interactor::bold("(" + std::to_string(c+1) + ") " + choices[c]);
            std::cout << std::endl;
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

void Interactor::printInColumns(const std::vector<std::vector<std::string>> &rows) {
    Interactor::printInColumns(rows, std::vector<std::string>{}, std::cout, 0);
};

void Interactor::printInColumns(const std::vector<std::vector<std::string>> &rows, int indent) {
    Interactor::printInColumns(rows, std::vector<std::string>{}, std::cout, indent);
};

void Interactor::printInColumns(const std::vector<std::vector<std::string>> &rows, const std::vector<std::string> &headers) {
    Interactor::printInColumns(rows, headers, std::cout, 0);
};

void Interactor::printInColumns(const std::vector<std::vector<std::string>> &rows, const std::vector<std::string> &headers, int indent) {
    Interactor::printInColumns(rows, headers, std::cout, indent);
};

void Interactor::printInColumns(const std::vector<std::vector<std::string>> &rows, const std::vector<std::string> &headers, std::ostream &os) {
    Interactor::printInColumns(rows, headers, os, 0);
};


void Interactor::printInColumns(const std::vector<std::vector<std::string>> &rows, const std::vector<std::string> &headers, std::ostream &os, int indent) {
    // make sure rows is not empty
    if(rows.size() == 0) {
        return;
    }
    bool haveHeaders = headers.size() > 0;
    // make sure all rows habe the same number of columns
    // and check for the longest string
    std::size_t numberOfColumns = rows[0].size();
    std::vector<std::size_t> longests(numberOfColumns);
    for(int r = 0; r < rows.size(); r++) {
        // check number of columns
        if(rows[r].size() != numberOfColumns) {
            return;
        }
        // check the lengths
        for(int c = 0; c < numberOfColumns; c++) {
            std::size_t length = rows[r][c].length();
            if(longests[c] < length) {
                longests[c] = length;
            }
        }
    }
    // if we have headers, do the same
    if(haveHeaders) {
        if(headers.size() != numberOfColumns) {
            return;
        }
        for(int c = 0; c < numberOfColumns; c++) {
            std::size_t length = headers[c].length();
            if(longests[c] < length) {
                longests[c] = length;
            }
        }
    }
    // now we print it
    if(haveHeaders) {
        os << std::left;
        if(indent > 0) {
            os << std::string(indent, '\t');
        }
        for(int h = 0; h < numberOfColumns; h++) {
            os << Interactor::BOLD;
            os << std::setw(longests[h]) << std::setfill(' ') << headers[h] << " ";
            os << Interactor::RESET;
        }
        os << std::endl;
        if(indent > 0) {
            os << std::string(indent, '\t');
        }
        for(int h = 0; h < numberOfColumns; h++) {
            os << std::string(longests[h], '-') << '-';
        }
        os << std::endl;
    }
    for(int r = 0; r < rows.size(); r++) {
        os << std::left;
        if(indent > 0) {
            os << std::string(indent, '\t');
        }
        for(int h = 0; h < numberOfColumns; h++) {
            os << std::setw(longests[h]) << std::setfill(' ') << rows[r][h] << " ";
            os << Interactor::RESET;
        }
        os << std::endl;
    }
};

std::string Interactor::rgb2color(const int rgb[3], bool fg) {
    return (fg ? Interactor::MULTICOLOR_FG : Interactor::MULTICOLOR_BG) + std::to_string(rgb[0]) + ";" + std::to_string(rgb[1]) + ";" + std::to_string(rgb[2]) + "m";
};

void Interactor::put(const std::string &text, const int rgb[3]) {
    std::cout << rgb2color(rgb) << text << Interactor::RESET << std::endl;
};

void Interactor::put(const std::string &text, const int rgb[3], const int rgb_bg[3]) {
    std::cout << rgb2color(rgb) << rgb2color(rgb_bg, false) << text << Interactor::RESET << std::endl;
};

void Interactor::bold(std::string text) {
    std::cout << Interactor::BOLD << text << Interactor::RESET;
};

void Interactor::bold(std::string text, std::ostream &os) {
    os << Interactor::BOLD << text << Interactor::RESET;
};