#ifndef _EXCELXML_H_
#define _EXCELXML_H_

#include <iostream>
#include <string>
#include <vector>

#define EOL "\n"
#define STYLE_ALIGNMENT_HORIZONTAL_AUTOMATIC "Automatic"
#define STYLE_ALIGNMENT_HORIZONTAL_LEFT "Left"
#define STYLE_ALIGNMENT_HORIZONTAL_CENTER "Center"
#define STYLE_ALIGNMENT_HORIZONTAL_RIGHT "Right"
#define STYLE_ALIGNMENT_HORIZONTAL_FILL "Fill"
#define STYLE_ALIGNMENT_HORIZONTAL_JUSTIFY "Justify"
#define STYLE_ALIGNMENT_HORIZONTAL_CENTER_ACROSS_SELECTION "CenterAcrossSelection"
#define STYLE_ALIGNMENT_HORIZONTAL_DISTRIBUTED "Distributed"
#define STYLE_ALIGNMENT_HORIZONTAL_JUSTIFY_DISTRIBUTED "JustifyDistributed"

#define STYLE_ALIGNMENT_READING_ORDER_RIGHT_TO_LEFT "RightToLeft"
#define STYLE_ALIGNMENT_READING_ORDER_LEFT_TO_RIGHT "LeftToRight"
#define STYLE_ALIGNMENT_READING_ORDER_CONTEXT "Context"

#define STYLE_ALIGNMENT_VERTICAL_AUTOMATIC "Automatic"
#define STYLE_ALIGNMENT_VERTICAL_TOP "Top"
#define STYLE_ALIGNMENT_VERTICAL_BOTTOM "Bottom"
#define STYLE_ALIGNMENT_VERTICAL_CENTER "Center"
#define STYLE_ALIGNMENT_VERTICAL_JUSTIFY "Justify"
#define STYLE_ALIGNMENT_VERTICAL_DISTRIBUTED "Distributed"
#define STYLE_ALIGNMENT_VERTICAL_JUSTIFY_DISTRIBUTED "JustifyDistributed"

#define STYLE_BORDER_POSITION_LEFT "Left"
#define STYLE_BORDER_POSITION_TOP "Top"
#define STYLE_BORDER_POSITION_RIGHT "Right"
#define STYLE_BORDER_POSITION_BOTTOM "Bottom"
#define STYLE_BORDER_POSITION_DIAGONAL_LEFT "DiagonalLeft"
#define STYLE_BORDER_POSITION_DIAGONAL_RIGHT "DiagonalRight"

#define STYLE_BORDER_COLOR_DEFAULT "Automatic"

#define STYLE_BORDER_LINE_STYLE_NONE "None"
#define STYLE_BORDER_LINE_STYLE_CONTINUOUS "Continuous"
#define STYLE_BORDER_LINE_STYLE_DASH "Dash"
#define STYLE_BORDER_LINE_STYLE_DOT "Dot"
#define STYLE_BORDER_LINE_STYLE_DASH_DOT "DashDot"
#define STYLE_BORDER_LINE_STYLE_DASH_DOT_DOT "DashDotDot"
#define STYLE_BORDER_LINE_STYLE_SLANT_DASH_DOT "SlantDashDot"
#define STYLE_BORDER_LINE_STYLE_DOUBLE "Double"

#define STYLE_BORDER_WEIGHT_HAIRLINE 0
#define STYLE_BORDER_WEIGHT_THIN 1
#define STYLE_BORDER_WEIGHT_MEDIUM 2
#define STYLE_BORDER_WEIGHT_THICK 3
// ss:LineStyle , , , , , , , and 

namespace DAF {

struct Alignment {
    std::string horizontal{STYLE_ALIGNMENT_HORIZONTAL_AUTOMATIC};
    unsigned long indent{0};
    std::string reading_order{STYLE_ALIGNMENT_READING_ORDER_CONTEXT};
    double rotate{0};
    bool shrink_to_fit{false};
    std::string vertical{STYLE_ALIGNMENT_VERTICAL_AUTOMATIC};
    bool vertical_text{false};
    bool wrap_text{false};
    bool isEmpty() {
        return horizontal != STYLE_ALIGNMENT_HORIZONTAL_AUTOMATIC
        || indent != 0
        || reading_order != STYLE_ALIGNMENT_READING_ORDER_CONTEXT
        || rotate != 0
        || shrink_to_fit != false
        || vertical != STYLE_ALIGNMENT_VERTICAL_AUTOMATIC
        || vertical_text != false
        || wrap_text != false;
    };
};

struct Border {
    std::string position{STYLE_BORDER_POSITION_LEFT};
    /*
    Specifies the color of this border.
    This value can be either a 6-hexadecimal digit number in "#rrggbb" format or it can be any
    of the Microsoft® Internet Explorer named colors (including the named Microsoft Windows® colors).
    This string can also be the special value of "Automatic." This string is case insensitive.
    */
    std::string color{STYLE_BORDER_COLOR_DEFAULT};
    std::string linestyle{STYLE_BORDER_LINE_STYLE_NONE};
    double weight{STYLE_BORDER_WEIGHT_HAIRLINE};
};

struct Borders {
    std::vector<Border> borders;
    bool isEmpty() { return borders.size() == 0; };
};

struct Font {

};

struct Style {
    std::string id;
    Alignment alignment;
    Font font;
    // ss:Alignment, ss:Borders, ss:Font, ss:Interior, ss:NumberFormat, ss:Protection
    friend std::ostream &operator<<(std::ostream &os, Style &s) {
        os << "<ss:Style>" << EOL;
        if(! s.alignment.isEmpty()) {
            os << "<ss:Alignment ";
            if(s.alignment.horizontal != STYLE_ALIGNMENT_HORIZONTAL_AUTOMATIC) {
                os << "ss:Horizontal=\"" << s.alignment.horizontal << "\" ";
            }
            if(s.alignment.indent != 0) {
                os << "ss:Indent=\"" << s.alignment.indent << "\" ";
            }
            if(s.alignment.reading_order != STYLE_ALIGNMENT_READING_ORDER_CONTEXT) {
                os << "ss:ReadingOrder=\"" << s.alignment.reading_order << "\" ";
            }
            if(s.alignment.rotate != 0) {
                os << "ss:Rotate=\"" << s.alignment.rotate << "\" ";
            }
            if(s.alignment.shrink_to_fit) {
                os << "ss:ShrinkToFit=\"1\" ";
            }
            if(s.alignment.vertical != STYLE_ALIGNMENT_VERTICAL_AUTOMATIC) {
                os << "ss:Vertical=\"" << s.alignment.vertical << "\" ";
            }
            if(s.alignment.vertical_text) {
                os << "ss:VerticalText=\"1\" ";
            }
            if(s.alignment.wrap_text) {
                os << "ss:WrapText=\"1\" ";
            }
            os << "/>" << EOL;
        }
        os << "</ss:Style>" << EOL;
    };
};

struct Styles {
    std::vector<Style> styles;
    std::string generateID() { return std::string{"style" + (styles.size() + 1)}; }
};

struct Cell {
    typedef enum Type {
        STRING = 0,
        NUMBER
    } TYPE;
    Type type;
    std::string data;
};

struct Column {
    int index{0};
    std::string caption{""};
    std::string styleid{""};
    double width{0.0};
    friend std::ostream &operator<<(std::ostream &os, Column &c) {
        os << "<Column ";
        if(c.index > 0) {
            os << "ss:Index=\"" << c.index << "\" ";
        }
        if(c.caption.size() > 0) {
            os << "cCaption=\"" << c.caption << "\" ";
        }
        if(c.styleid.size() > 0) {
            os << "ss:StyleID=\"" << c.styleid << "\" ";
        }
        if(c.width > 0) {
            os << "ss:Width=\"" << c.width << "\"";
        }
        os << "/>" << EOL;
        return os;
    };
};

struct Row {
    std::vector<Cell> cells;
};

struct Worksheet {
    std::string name;
    std::vector<Column> columns;
    std::vector<Row> rows;
    friend std::ostream &operator<<(std::ostream &os, Worksheet &ws) {
        std::replace(ws.name.begin(), ws.name.end(), ' ', '+');
        os << "<Worksheet ss:Name=\"" + ws.name + "\">" + EOL;

        os << "</Worksheet>" << EOL;
        return os;
    };
};

struct Workbook {
    std::vector<Worksheet> worksheets;
    friend std::ostream &operator<<(std::ostream &os, Workbook &wb) {
        os << R"(<?xml version="1.0" encoding="UTF-8"?>)" << EOL;
        os << R"(<?mso-application progid="Excel.Sheet"?>")" << EOL;
        os << R"(<Workbook xmlns="urn:schemas-microsoft-com:office:spreadsheet" xmlns:x="urn:schemas-microsoft-com:office:excel" xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet" xmlns:html="https://www.w3.org/TR/html401/">)" << EOL;
        for(Worksheet &ws: wb.worksheets) {
            os << ws;
        }
        os << R"(</Workbook>)" << EOL;
        return os;
    };
};

}

#endif