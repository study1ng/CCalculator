#pragma once

#include <string>
#include <iostream>
#include <cstdarg>
#include <memory>
#include <map>
#include <tuple>
#include <vector>

namespace np_calculator
{
    using std::cerr;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::map;
    using std::pair;
    using std::string;
    using std::unique_ptr;
    using std::vector;
    bool is_quit(string);

    int calcaulator(void);
    namespace new_liner
    {
        void set_attr(string);
        void set_mark(string);
        void new_line(void);
        void set_ccolor(string color);
        void set_bcolor(int color);
        void set_bcolor(string color);
        void set_ccolor(int color);
        void set_font(string font);
        void set_font(int font);
        void set_default();
        void use_customized_font();
        void use_default();
        extern string new_line_attr;
        extern string new_line_mark;
    }

    using new_liner::new_line;
    using new_liner::set_attr;
    using new_liner::set_mark;
    using new_liner::set_font;
    using new_liner::set_ccolor;
    using new_liner::set_bcolor;
    using new_liner::set_default;
    using new_liner::use_customized_font;
    using new_liner::use_default;
    namespace error
    {
        extern bool err_flag;

        void error_at(int place, string fmt, ...);
    }
    using namespace error;
}
