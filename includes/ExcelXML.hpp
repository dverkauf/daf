#ifndef _EXCELXML_H_
#define _EXCELXML_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

#define STYLE_FONT_NAME_ARIAL "Arial"
#define STYLE_FONT_SIZE_DEFAULT 10
#define STYLE_FONT_UNDERLINE_NONE "None"
#define STYLE_FONT_UNDERLINE_SINGLE "Single"
#define STYLE_FONT_UNDERLINE_DOUBLE "Double"
#define STYLE_FONT_UNDERLINE_SINGLE_ACCOUNTING "SingleAccounting"
#define STYLE_FONT_UNDERLINE_DOUBLE_ACCOUNTING "DoubleAccounting"
#define STYLE_FONT_VERTICAL_ALIGN_NONE "None"
#define STYLE_FONT_VERTICAL_ALIGN_SUBSCRIPT "Subscript"
#define STYLE_FONT_VERTICAL_ALIGN_SUPERSCRIPT "Superscript"
#define STYLE_FONT_FAMILY_AUTOMATIC "Automatic"
#define STYLE_FONT_FAMILY_DECORATIVE "Decorative"
#define STYLE_FONT_FAMILY_MODERN "Modern"
#define STYLE_FONT_FAMILY_ROMAN "Roman"
#define STYLE_FONT_FAMILY_SCRIPT "Script"
#define STYLE_FONT_FAMILY_SWISS "Swiss"

#define STYLE_INTERIOR_PATTERN_NONE "None"
#define STYLE_INTERIOR_PATTERN_SOLID "Solid"
#define STYLE_INTERIOR_PATTERN_GRAY75 "Gray75"
#define STYLE_INTERIOR_PATTERN_GRAY50 "Gray50"
#define STYLE_INTERIOR_PATTERN_GRAY25 "Gray25"
#define STYLE_INTERIOR_PATTERN_GRAY125 "Gray125"
#define STYLE_INTERIOR_PATTERN_GRAY0625 "Gray0625"
#define STYLE_INTERIOR_PATTERN_HORZ_STRIPE "HorzStripe"
#define STYLE_INTERIOR_PATTERN_VERT_STRIPE "VertStripe"
#define STYLE_INTERIOR_PATTERN_REVERSE_DIAG_STRIPE "ReverseDiagStripe"
#define STYLE_INTERIOR_PATTERN_DIAG_STRIPE "DiagStripe"
#define STYLE_INTERIOR_PATTERN_DIAG_CROSS "DiagCross"
#define STYLE_INTERIOR_PATTERN_THICK_DIAG_CROSS "ThickDiagCross"
#define STYLE_INTERIOR_PATTERN_THIN_HORZ_STRIPE "ThinHorzStripe"
#define STYLE_INTERIOR_PATTERN_THIN_VERT_STRIPE "ThinVertStripe"
#define STYLE_INTERIOR_PATTERN_THIN_REVERSE_DIAG_STRIPE "ThinReverseDiagStripe"
#define STYLE_INTERIOR_PATTERN_THIN_DIAG_STRIPE "ThinDiagStripe"
#define STYLE_INTERIOR_PATTERN_THIN_HORZ_CROSS "ThinHorzCross"
#define STYLE_INTERIOR_PATTERN_THIN_DIAG_CROSS "ThinDiagCross"

#define STYLE_NUMBER_FORMAT_GENERAL "General"
#define STYLE_NUMBER_FORMAT_GENERAL_NUMBER "General Number"
#define STYLE_NUMBER_FORMAT_GENERAL_DATE "General Date"
#define STYLE_NUMBER_FORMAT_LONG_DATE "Long Date"
#define STYLE_NUMBER_FORMAT_MEDIUM_DATE "Medium Date"
#define STYLE_NUMBER_FORMAT_SHORT_DATE "Short Date"
#define STYLE_NUMBER_FORMAT_LONG_TIME "Long Time"
#define STYLE_NUMBER_FORMAT_MEDIUM_TIME "Medium Time"
#define STYLE_NUMBER_FORMAT_SHORT_TIME "Short Time"
#define STYLE_NUMBER_FORMAT_CURRENCY "Currency"
#define STYLE_NUMBER_FORMAT_EURO_CURRENCY "Euro Currency"
#define STYLE_NUMBER_FORMAT_FIXED "Fixed"
#define STYLE_NUMBER_FORMAT_STANDARD "Standard"
#define STYLE_NUMBER_FORMAT_PERCENT "Percent"
#define STYLE_NUMBER_FORMAT_SCIENTIFIC "Scientific"
#define STYLE_NUMBER_FORMAT_YES_NO "Yes/No"
#define STYLE_NUMBER_FORMAT_TRUE_FALSE "True/False"
#define STYLE_NUMBER_FORMAT_ON_OFF "On/Off"

#define STYLE_COLOR_AUTOMATIC "Automatic"

#define TABLE_DEFAULT_COLUMN_WIDTH 48
#define TABLE_DEFAULT_ROW_HEIGHT 12.75

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
    bool isNotEmpty() {
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
    bool isNotEmpty() { return borders.size() > 0; };
};

struct Font {
// ss:Bold, ss:Color, ss:FontName, ss:Italic, ss:Outline, ss:Shadow, ss:Size, ss:StrikeThrough, ss:Underline, ss:VerticalAlign, x:CharSet, x:Family
    bool bold{false};
    std::string color{STYLE_COLOR_AUTOMATIC};
    std::string name{STYLE_FONT_NAME_ARIAL};
    bool italic{false};
    bool outline{false};
    bool shadow{false};
    double size{STYLE_FONT_SIZE_DEFAULT};
    bool strike_through{false};
    std::string underline{STYLE_FONT_UNDERLINE_NONE};
    std::string vertical_align{STYLE_FONT_VERTICAL_ALIGN_NONE};
    unsigned long charset{0};
    std::string family{STYLE_FONT_FAMILY_AUTOMATIC};
    bool isNotEmpty() {
        return !bold ||
            color != STYLE_COLOR_AUTOMATIC ||
            name != STYLE_FONT_NAME_ARIAL ||
            !italic || !outline || !shadow ||
            size != STYLE_FONT_SIZE_DEFAULT ||
            !strike_through ||
            underline != STYLE_FONT_UNDERLINE_NONE ||
            vertical_align != STYLE_FONT_VERTICAL_ALIGN_NONE ||
            charset != 0 ||
            family != STYLE_FONT_FAMILY_AUTOMATIC;
    };
};

struct Interior {
    std::string color{STYLE_COLOR_AUTOMATIC};
    std::string pattern{STYLE_INTERIOR_PATTERN_NONE};
    std::string pattern_color{STYLE_COLOR_AUTOMATIC};
    bool isNotEmpty() {
        return color != STYLE_COLOR_AUTOMATIC ||
        pattern != STYLE_INTERIOR_PATTERN_NONE ||
        pattern_color != STYLE_COLOR_AUTOMATIC;
    };
};

struct NumberFormat {
    std::string format{STYLE_NUMBER_FORMAT_GENERAL};
    bool isNotEmpty() { return format != STYLE_NUMBER_FORMAT_GENERAL; };
};

struct Protection {
    bool is_protected{true};
    bool hide_formula{false};
    bool isNotEmpty() { return !is_protected || hide_formula; };
};

struct Style {
    std::string id; // REQUIRED!!!
    std::string name; // UNIQUE!!!
    std::string parent;
    Alignment alignment;
    Font font;
    Interior interior;
    NumberFormat number_format;
    Protection protection;
    // ss:Alignment, ss:Borders, ss:Font, ss:Interior, ss:NumberFormat, ss:Protection
    friend std::ostream &operator<<(std::ostream &os, Style &s) {
        os << "<ss:Style>" << EOL;
        if(s.alignment.isNotEmpty()) {
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
        if(s.font.isNotEmpty()) {
            os << "<ss:Font ";
            if(s.font.bold) {
                os << "ss:Bold=\"1\" ";
            }
            if(s.font.color != STYLE_COLOR_AUTOMATIC) {
                os << "ss:Color=\"" << s.font.color << "\" ";
            }
            if(s.font.name != STYLE_FONT_NAME_ARIAL) {
                os << "ss:FontName=\"" << s.font.name << "\" ";
            }
            if(s.font.italic) {
                os << "ss:Italic=\"1\" ";
            }
            if(s.font.outline) {
                os << "ss:Outline=\"1\" ";
            }
            if(s.font.shadow) {
                os << "ss:Shadow=\"1\" ";
            }
            if(s.font.size != STYLE_FONT_SIZE_DEFAULT) {
                os << "ss:Size=\"" << s.font.size << "\" ";
            }
            if(s.font.strike_through) {
                os << "ss:StrikeThrough=\"1\" ";
            }
            if(s.font.underline != STYLE_FONT_UNDERLINE_NONE) {
                os << "ss:Underline=\"" << s.font.underline << "\" ";
            }
            if(s.font.vertical_align != STYLE_FONT_VERTICAL_ALIGN_NONE) {
                os << "ss:VerticalAlign=\"" << s.font.vertical_align << "\" ";
            }
            if(s.font.charset != 0) {
                os << "x:CharSet=\"" << s.font.charset << "\" ";
            }
            if(s.font.family != STYLE_FONT_FAMILY_AUTOMATIC) {
                os << "x:Family=\"" << s.font.family << "\" ";
            }
            os << "/>" << EOL;
        }
        if(s.interior.isNotEmpty()) {
            os << "<ss:Interior ";
            if(s.interior.color != STYLE_COLOR_AUTOMATIC) {
                os << "ss:Color=\"" << s.interior.color << "\" ";
            }
            if(s.interior.pattern != STYLE_INTERIOR_PATTERN_NONE) {
                os << "ss:Pattern=\"" << s.interior.pattern << "\" ";
            }
            if(s.interior.pattern_color != STYLE_COLOR_AUTOMATIC) {
                os << "ss:PatternColor=\"" << s.interior.pattern_color << "\" ";
            }
            os << "/>" << EOL;
        }
        if(s.number_format.isNotEmpty()) {
            os << "<ss:NumberFormat ss:Format=\"" << s.number_format.format << "\"/>";
        }
        if(s.protection.isNotEmpty()) {
            os << "<ss:Protection ";
            if(!s.protection.is_protected) {
                os << "ss:Protected=\"0\" ";
            }
            if(s.protection.hide_formula) {
                os << "x:HideFormula=\"1\" ";
            }
            os << "/>" << EOL;
        }
        os << "</ss:Style>" << EOL;
    };
};

struct Styles {
    std::vector<Style> styles;
    std::string generateID() { return std::string{"style" + (styles.size() + 1)}; }
    friend std::ostream &operator<<(std::ostream &os, Styles &s) {
        if(s.styles.size() > 0) {
            os << "<ss:Styles>" << EOL;
            for(auto style: s.styles) {
                os << style;
            }
            os << "</ss:Styles>" << EOL;
        }
        return os;
    };
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

struct CWorksheetOptions { // <c:WorksheetOptions>
    bool display_custom_headers{false}; // <c:DisplayCustomHeaders>
    friend std::ostream &operator<<(std::ostream &os, CWorksheetOptions &wso) {
        if(wso.display_custom_headers) {
            os << "<c:WorksheetOptions><c:DisplayCustomHeaders/></c:WorksheetOptions>" << EOL;
        }
        return os;
    };
};

struct Names {
    struct NamedRange {
        std::string name;
        std::string refers_to;
        bool hidden{false};
    };
    std::vector<NamedRange> named_ranges;
    friend std::ostream &operator<<(std::ostream &os, Names &n) {
        if(n.named_ranges.size() > 0) {
            os << "<ss:Names>" << EOL;
            for(auto nr: n.named_ranges) {
                if(nr.name.length() > 0 && nr.refers_to.length() > 0) { // both attributes are requiered
                    os << "<ss:NamedRange ss:Name=\"" << nr.name << "\" ss:RefersTo=\"" << nr.refers_to << "\"";
                    if(nr.hidden) {
                        os << " ss:Hidden=\"1\"";
                    }
                    os << "/>" << EOL;
                }
            }
            os << "</ss:Names>" << EOL;
        }
        return os;
    };
};

struct Table { // <ss:Table>
    // optional elements
    std::vector<Column> columns;
    std::vector<Row> rows;
    // optional attributes
    double default_column_width{TABLE_DEFAULT_COLUMN_WIDTH}; // ss:DefaultColumnWidth   
    double default_row_height{TABLE_DEFAULT_ROW_HEIGHT}; // ss:DefaultRowHeight
    unsigned long expanded_column_count{0}; // ss:ExpandedColumnCount
    unsigned long expanded_row_count{0}; // ss:ExpandedRowCount
    unsigned long left_cell{1}; // ss:LeftCell
    std::string styleid{""}; // ss:StyleID
    unsigned long top_cell{1}; // ss:TopCell
    bool full_columns{false}; // x:FullColumns
    bool full_rows{false}; // x:FullRows
    
};

struct AutoFilter {

};

struct XWorksheetOptions {

};

struct Worksheet {
    std::string name;
    bool is_protected{false};
    bool right_to_left{false};
    friend std::ostream &operator<<(std::ostream &os, Worksheet &ws) {
        std::replace(ws.name.begin(), ws.name.end(), ' ', '+');
        os << "<Worksheet ss:Name=\"" + ws.name + "\"";
        if(ws.is_protected) {
            os << " ss:Protected=\"1\"";
        }
        if(ws.right_to_left) {
            os << " ss:RightToLeft=\"1\"";
        }
        os << ">" << EOL;

        os << "</Worksheet>" << EOL;
        return os;
    };
};

struct ComponentOptions {
    struct Toolbar {
        bool hidden{false};
        bool hide_office_logo{false};
    } toolbar;
    friend std::ostream &operator<<(std::ostream &os, ComponentOptions &co) {
        if(co.toolbar.hidden || co.toolbar.hide_office_logo) {
            os << "<c:ComponentOptions><c:Toolbar";
            if(co.toolbar.hidden) {
                os << " ss:Hidden=\"1\"";
            }
            os << ">" << EOL;
            if(co.toolbar.hide_office_logo) {
                os << "<c:HideOfficeLogo />" << EOL;
            }
            os << "</c:Toolbar>" << EOL;
            os << "</c:ComponentOptions>" << EOL;
        }
        return os;
    };
};

struct SmartTagType {
    std::string name;
    std::string namescapeuri;
    friend std::ostream &operator<<(std::ostream &os, SmartTagType &stt) {
        if(stt.name.length() != 0 && stt.namescapeuri.length() != 0) { // both attributes are requiered
            os << "<o:SmartTagType o:name=\"" << stt.name << "\" o:namespaceuri=\"" << stt.namescapeuri << "\"/>" << EOL;
        }
        return os;
    }
};

struct Workbook {
    Styles styles;
    ComponentOptions component_options;
    SmartTagType smart_tag_type;
    Names names;
    std::vector<Worksheet> worksheets;
    friend std::ostream &operator<<(std::ostream &os, Workbook &wb) {
        os << R"(<?xml version="1.0" encoding="UTF-8"?>)" << EOL;
        os << R"(<?mso-application progid="Excel.Sheet"?>")" << EOL;
        os << R"(<Workbook xmlns="urn:schemas-microsoft-com:office:spreadsheet" xmlns:x="urn:schemas-microsoft-com:office:excel" xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet" xmlns:html="https://www.w3.org/TR/html401/">)" << EOL;
        os << wb.styles;
        os << wb.names;
        os << wb.component_options;
        os << wb.smart_tag_type;
        for(Worksheet &ws: wb.worksheets) {
            os << ws;
        }
        os << R"(</Workbook>)" << EOL;
        return os;
    };
};

}

#endif