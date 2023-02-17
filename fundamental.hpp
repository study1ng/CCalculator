#pragma once

#include <string>
#include <iostream>
#include <cstdarg>
#include <memory>
#include <map>
#include <tuple>

namespace np_calculator
{
    using std::cerr;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;
    using std::unique_ptr;
    using std::pair;
    using std::map;
    bool is_quit(string);

    int calcaulator(void);
    namespace new_liner
    {
        void set_attr(string);
        void set_mark(string);
        void new_line(void);
        extern string new_line_attr;
        extern string new_line_mark;
    }

    using new_liner::new_line;
    using new_liner::set_attr;
    using new_liner::set_mark;

    namespace error
    {
        extern bool err_flag;

        void error_at(int place, string fmt, ...);
    }
    using namespace error;
}
