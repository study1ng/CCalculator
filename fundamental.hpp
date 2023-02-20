#pragma once

#include <string>
#include <iostream>
#include <cstdarg>
#include <memory>
#include <map>
#include <tuple>
#include <vector>
#include <iomanip>
#include <fstream>

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
    using std::ifstream;
    using std::ofstream;
    using std::setw;
    extern int line_number;
    int calcaulator(void);
    void go_next_word(string::const_iterator &);

    bool is_end(string::const_iterator &);
    namespace newliner
    {
        void set_attr(string);
        void set_mark(string);
        void newline(void);
        void set_newline_char_color(string color);
        void set_newline_background_color(int color);
        void set_newline_background_color(string color);
        void set_newline_char_color(int color);
        void set_newline_font(string font);
        void set_newline_font(int font);

        void set_default_char_color(int color);
        void set_default_char_color(string color);
        void set_default_background_color(int color);
        void set_default_background_color(string color);
        void set_default_font(string font);
        void set_default_font(int font);

        void set_default();
        void use_newline_customized_font();
        void use_default_font();
        extern string newline_attr;
        extern string newline_mark;
        extern vector<int> newline_font;
        extern vector<int> default_font;
        extern int newline_char_color;
        extern int newline_background_color;
        extern int default_char_color;
        extern int default_background_color;
    }

    using newliner::newline;
    using newliner::set_attr;
    using newliner::set_default;
    using newliner::set_mark;
    using newliner::set_newline_background_color;
    using newliner::set_newline_char_color;
    using newliner::set_newline_font;
    using newliner::set_default_font;
    using newliner::use_default_font;
    using newliner::set_default_background_color;
    using newliner::set_default_char_color;
    using newliner::use_newline_customized_font;
    namespace error
    {
        extern bool err_flag;

        void error_at(int place, string fmt, ...);
    }
    using namespace error;
}
