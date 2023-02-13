#include "fundamental.hpp"
namespace np_calculator
{
    bool is_quit(string s)
    {
        return (s == "quit" || s == "q");
    };
    namespace new_liner
    {
        string new_line_attr;
        string new_line_mark = ">> ";
    }
    
    namespace new_liner
    {
        void set_attr(string attr)
        {
            new_line_attr = attr;
        };
        void set_mark(string mark)
        {
            new_line_mark = mark;
        };
        void new_line(void)
        {
            cout << new_line_attr << new_line_mark;
        }
    }
    namespace error
    {
        bool err_flag;
        void error_at(int place, string fmt, ...)
        {
            va_list ap;
            va_start(ap, fmt);
            set_attr("err");
            new_line();
            for (int i = 0; i < place; ++i)
            {
                cerr << " ";
            }
            cerr << "^";
            vfprintf(stderr, fmt.c_str(), ap);
            cerr << endl;
            err_flag = 1;
        }
    }
}