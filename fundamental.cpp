#include "fundamental.hpp"
namespace np_calculator
{
    void go_next_word(string::const_iterator &i)
    {
        while (*i == ' ' || *i == '\t')
        {
            ++i;
        }
    }

    bool is_end(string::const_iterator &begin)
    {
        go_next_word(begin);
        return (*begin == '\n' || *begin == '\0');
    }
    namespace newliner
    {
        string newline_attr;
        string newline_mark = ">> ";
        vector<int> newline_font(1, 0);
        vector<int> default_font(1, 0);
        int newline_char_color = 39;
        int default_char_color = 39;
        int default_background_color = 49;
        int newline_background_color = 49;
    }

    namespace newliner
    {
        void set_attr(string attr)
        {
            newline_attr = attr;
        };
        void set_mark(string mark)
        {
            newline_mark = mark;
        };
        void set_newline_char_color(int color)
        {
            newline_char_color = color;
        }
        void set_newline_char_color(string color)
        {
            if (color == "black")
            {
                newline_char_color = 30;
            }
            else if (color == "red")
            {
                newline_char_color = 31;
            }
            else if (color == "green")
            {
                newline_char_color = 32;
            }
            else if (color == "blown")
            {
                newline_char_color = 33;
            }
            else if (color == "blue")
            {
                newline_char_color = 34;
            }
            else if (color == "purple")
            {
                newline_char_color = 35;
            }
            else if (color == "gray")
            {
                newline_char_color = 36;
            }
            else if (color == "white")
            {
                newline_char_color = 37;
            }
            else if (color == "none")
            {
                newline_char_color = 39;
            }
            else
            {
                cerr << "usage: set newline char color + [param]\nparam can be 'black', 'red', 'green', 'blown', 'blue', 'purple', 'gray', 'none";
            }
        }
        void set_newline_background_color(int color)
        {
            newline_background_color = color;
        }
        void set_newline_background_color(string color)
        {
            if (color == "black")
            {
                newline_background_color = 40;
            }
            else if (color == "red")
            {
                newline_background_color = 41;
            }
            else if (color == "green")
            {
                newline_background_color = 42;
            }
            else if (color == "blown")
            {
                newline_background_color = 43;
            }
            else if (color == "blue")
            {
                newline_background_color = 44;
            }
            else if (color == "purple")
            {
                newline_background_color = 45;
            }
            else if (color == "gray")
            {
                newline_background_color = 46;
            }
            else if (color == "white")
            {
                newline_background_color = 47;
            }
            else if (color == "none")
            {
                newline_background_color = 49;
            }
            else
            {
                cout << "usage: set newline background color + [param]\nparam can be 'black', 'red', 'green', 'blown', 'blue', 'purple', 'gray', 'none";
            }
        }
        void set_newline_font(string font)
        {
            if (font == "italic")
            {
                newline_font.emplace_back(3);
            }
            else if (font == "bold")
            {
                newline_font.emplace_back(1);
            }
            else if (font == "half_bright")
            {
                newline_font.emplace_back(2);
            }
            else if (font == "under_bar")
            {
                newline_font.emplace_back(4);
            }
            else if (font == "blink")
            {
                newline_font.emplace_back(5);
            }
            else if (font == "none")
            {
                newline_font.clear();
                newline_font.emplace_back(0);
            }
            else
            {
                cout << "usage: set newline font + [params]\nparams can be 'bold', 'italic', 'half_bright', 'under_bar', 'blink', 'none'"
                     << "if you put none in the params, none will replace any used font\n";
            }
        }
        void set_newline_font(int font)
        {
            newline_font.emplace_back(font);
        }
        void set_default_char_color(int color)
        {
            default_char_color = color;
        }
        void set_default_char_color(string color)
        {
            if (color == "black")
            {
                default_char_color = 30;
            }
            else if (color == "red")
            {
                default_char_color = 31;
            }
            else if (color == "green")
            {
                default_char_color = 32;
            }
            else if (color == "blown")
            {
                default_char_color = 33;
            }
            else if (color == "blue")
            {
                default_char_color = 34;
            }
            else if (color == "purple")
            {
                default_char_color = 35;
            }
            else if (color == "gray")
            {
                default_char_color = 36;
            }
            else if (color == "white")
            {
                default_char_color = 37;
            }
            else if (color == "none")
            {
                default_char_color = 39;
            }
            else
            {
                cout << "usage: set default char color + [param]\nparam can be 'black', 'red', 'green', 'blown', 'blue', 'purple', 'gray', 'none'.";
            }
        }
        void set_default_background_color(int color)
        {
            default_background_color = color;
        }
        void set_default_background_color(string color)
        {
            if (color == "black")
            {
                default_background_color = 40;
            }
            else if (color == "red")
            {
                default_background_color = 41;
            }
            else if (color == "green")
            {
                default_background_color = 42;
            }
            else if (color == "blown")
            {
                default_background_color = 43;
            }
            else if (color == "blue")
            {
                default_background_color = 44;
            }
            else if (color == "purple")
            {
                default_background_color = 45;
            }
            else if (color == "gray")
            {
                default_background_color = 46;
            }
            else if (color == "white")
            {
                default_background_color = 47;
            }
            else if (color == "none")
            {
                default_background_color = 49;
            }
            else
            {
                cout << "usage: set default background color + [param]\nparam can be 'black', 'red', 'green', 'blown', 'blue', 'purple', 'gray', 'none";
            }
        }
        void set_default_font(string font)
        {
            if (font == "italic")
            {
                default_font.emplace_back(3);
            }
            else if (font == "bold")
            {
                default_font.emplace_back(1);
            }
            else if (font == "half_bright")
            {
                default_font.emplace_back(2);
            }
            else if (font == "under_bar")
            {
                default_font.emplace_back(4);
            }
            else if (font == "blink")
            {
                default_font.emplace_back(5);
            }
            else if (font == "none")
            {
                default_font.clear();
                default_font.emplace_back(0);
            }
            else
            {
                cout << "usage: set default font + [params]\nparams can be 'bold', 'italic', 'half_bright', 'under_bar', 'blink', 'none'"
                     << "if you put none in the params, none will replace any used font";
            }
        }
        void set_default_font(int font)
        {
            default_font.emplace_back(font);
        }

        void set_default()
        {
            set_newline_font("none");
            set_newline_background_color("none");
            set_newline_char_color("none");
            set_default_background_color("none");
            set_default_char_color("none");
            set_default_font("none");
        }
        void use_newline_customized_font()
        {
            cout << "\033[";
            for (const int &i : newline_font)
            {
                cout << i << ";";
            }
            cout << newline_char_color << ";" << newline_background_color << "m";
        }
        void use_default_font()
        {
            cout << "\033[";
            for (const int &i : default_font)
            {
                cout << i << ";";
            }
            cout << default_char_color << ";" << default_background_color << "m";
        }
        void newline(void)
        {
            use_newline_customized_font();
            cout << newline_attr << newline_mark;
            use_default_font();
        }
    }
    namespace error
    {
        bool err_flag;
        void error_at(int place, string fmt, ...)
        {
            va_list ap;
            va_start(ap, fmt);
            set_newline_font("bold");
            set_newline_char_color("red");
            set_attr("err");
            newline();
            set_newline_font("italic");
            set_newline_char_color("red");
            use_newline_customized_font();
            for (int i = 0; i < place; ++i)
            {
                cerr << " ";
            }
            cerr << "^";
            vfprintf(stderr, fmt.c_str(), ap);
            printf("\n");
            use_default_font();
            err_flag = 1;
        }
    }
}