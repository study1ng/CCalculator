#include <iostream>
#include <string>
#include <cstdarg>
namespace np_calculator
{
    using std::cin;
    using std::cout;
    using std::cerr;
    using std::string;
    using std::endl;

    bool is_quit(string);
    string num(string::iterator&);
    bool is_end(const string::iterator&);
    void set_attr(string);
    void set_mark(string);
    void new_line(void);
    void error_at(int place, string fmt, ...);
    int calcaulator(void);
    
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
    }
    bool is_quit(string s)
    {
        return (s == "quit" || s == "q");
    };
    string num(string::iterator& begin)
    {
        if (!('0' <= *begin && *begin <= '9'))
        {
            return string();
        }
        string::iterator cur = begin;
        while ('0' <= *begin && *begin <= '9')
        {
            ++begin;
        }
        return string(cur, begin - 1);
    }
    bool is_end(const string::iterator& begin)
    {
        return *begin == '\n' || *begin == '\0';
    }
    string new_line_attr;
    string new_line_mark = ">> ";
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
    int calculator(void)
    {
        string expression("");
        while (true)
        {
            set_attr("exp");
            new_line();
            cin >> expression;
            if (is_quit(expression))
            {
                return 0;
            }
            string::iterator cur = expression.begin();
            string ans = num(cur);
            if (!is_end(cur))
            {
                error_at(cur - expression.begin(), "contains no-number word");
                continue;
            };
            set_attr("ans");
            new_line();
            cout << string(expression.begin(), cur) << " = " << string(expression.begin(), cur) << endl;
        };
    }
}