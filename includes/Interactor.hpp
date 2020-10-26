#ifndef INTERACTOR_H
#define INTERACTOR_H

#include <string>
#include <vector>
#include <array>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <exception>

class Interactor {

    private:

        std::size_t findLongestString(std::vector<std::string> strings);

        class TableColumn {
            
                public:

                std::string header;
                std::vector<std::string> values;
                std::size_t width;

                TableColumn(std::string header, std::vector<std::string> values) {
                    this->header = header;
                    this->values = values;
                    this->width = 0;
                    for(auto &value: values) {
                        std::size_t length = value.length();
                        this->width = (this->width > length) ? this->width : length;
                    }
                };

                std::size_t numrows() {
                    return values.size();
                };

                std::string valueAt(std::size_t row) {
                    return values.at(row);
                }

        };

    public:

        static constexpr const char KEY_ENTER = 10;

        static constexpr const char* CLEAR_LINE_TO_END      = "\033[0K";
        static constexpr const char* CLEAR_LINE_TO_START    = "\033[1K";
        static constexpr const char* CLEAR_LINE             = "\033[2K";

        static constexpr const char* RESET      = "\033[0m";
        static constexpr const char* BOLD       = "\033[1m";
        static constexpr const char* DIM        = "\033[2m";
        static constexpr const char* STANDOUT   = "\033[3m";
        static constexpr const char* UNDERSCORE = "\033[4m";
        static constexpr const char* BLINK      = "\033[5m";
        static constexpr const char* REVERSE    = "\033[7m";
        static constexpr const char* HIDDEN     = "\033[8m";

        static constexpr const char* COLOR_FG_BLACK     = "\033[30m";
        static constexpr const char* COLOR_FG_RED       = "\033[31m";
        static constexpr const char* COLOR_FG_GREEN     = "\033[32m";
        static constexpr const char* COLOR_FG_YELLOW    = "\033[33m";
        static constexpr const char* COLOR_FG_BLUE      = "\033[34m";
        static constexpr const char* COLOR_FG_MAGENTA   = "\033[35m";
        static constexpr const char* COLOR_FG_CYAN      = "\033[36m";
        static constexpr const char* COLOR_FG_WHITE     = "\033[37m";
        static constexpr const char* COLOR_FG_DEFAULT   = "\033[39m";

        static constexpr const char* COLOR_BG_BLACK     = "\033[40m";
        static constexpr const char* COLOR_BG_RED       = "\033[41m";
        static constexpr const char* COLOR_BG_GREEN     = "\033[42m";
        static constexpr const char* COLOR_BG_YELLOW    = "\033[43m";
        static constexpr const char* COLOR_BG_BLUE      = "\033[44m";
        static constexpr const char* COLOR_BG_MAGENTA   = "\033[45m";
        static constexpr const char* COLOR_BG_CYAN      = "\033[46m";
        static constexpr const char* COLOR_BG_WHITE     = "\033[47m";
        static constexpr const char* COLOR_BG_DEFAULT   = "\033[49m";

        static constexpr const char* MULTICOLOR_FG      = "\x1b[38;2;";
        static constexpr const char* MULTICOLOR_BG      = "\x1b[48;2;";

        static std::string readString();

        static void wait(std::string);
        static void wait(std::string, bool);
        static bool confirm(std::string question);
        static std::string prompt(std::string question);
        static std::string prompt(std::string question, std::string default_value);
        static int choose(std::string question, std::vector<std::string> choices);
        static int choose(std::string question, std::vector<std::string> choices, int default_at);
        static void table(std::vector<std::vector<std::string>> values);
        static void table(std::vector<std::vector<std::string>> values, std::vector<std::string> headers);

        static std::string rgb2color(const int rgb[3], bool fg = true);

        static void put(std::string);
        static void put(std::string, bool);
        static void put(std::string, const char* color);
        static void put(std::string, const char* color, bool);
        static void put(std::string, const char* color, const char* bg);
        static void put(std::string, const char* color, const char* bg, bool);
        static void put(std::string text, std::vector<const char *> styles);
        static void put(std::string text, std::vector<const char *> styles, bool);
        static void put(const std::string &text, const int rgb[3]);
        static void put(const std::string &text, const int rgb[3], const int rgb_bg[3]);
        static void info(std::string);
        static void info(std::string, bool);
        static void ok(std::string);
        static void warn(std::string);

        static void bold(std::string text, std::ostream &os);

        static void printInColumns(const std::vector<std::vector<std::string>> &rows);
        static void printInColumns(const std::vector<std::vector<std::string>> &rows, int indent);
        static void printInColumns(const std::vector<std::vector<std::string>> &rows, const std::vector<std::string> &headers);
        static void printInColumns(const std::vector<std::vector<std::string>> &rows, const std::vector<std::string> &headers, int indent = 0);
        static void printInColumns(const std::vector<std::vector<std::string>> &rows, const std::vector<std::string> &headers, std::ostream &os);
        static void printInColumns(const std::vector<std::vector<std::string>> &rows, const std::vector<std::string> &headers, std::ostream &os, int indent = 0);

        class Table {

            private:
                std::vector<std::string> headers;
                std::vector<std::vector<std::string>> rows;
                std::size_t numcols;
                std::size_t numrows;
                std::vector<std::size_t> col_widths;
                std::size_t total_width;
                void init(std::vector<std::vector<std::string>> rows, std::vector<std::string> headers);

            public:
                Table(std::vector<std::vector<std::string>> rows);
                Table(std::vector<std::vector<std::string>> rows, std::vector<std::string> headers);
                friend std::ostream &operator<<(std::ostream &os, const Interactor::Table &t);
                bool hasHeaders();

        };
};

class InteractorException : std::exception {

    private:

        std::string reason;
    
    public:
    
        static constexpr const char* REASON_HEADERS_NUM_MISMATCH   = "The number of headers mismatch the number of columns";
        static constexpr const char* REASON_NO_ROWS_FOUND   = "No rows were specified";
        static constexpr const char* REASON_ROWS_WITH_DEFFERENT_NUMCOLS   = "All rows must have the same number of columns";
        InteractorException(std::string reason) {
            this->reason = reason;
        };
        const char *what() const throw () {
            return this->reason.c_str();
        };
};

#endif /* INTERACTOR_H */