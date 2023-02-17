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
        vector<int> new_line_font(1, 0);
        int char_color = 39;
        int background_color = 49;
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
        void set_ccolor(int color)
        {
            char_color = color;
        }
        void set_ccolor(string color)
        {
            if (color == "black")
            {
                char_color = 30;
            }
            else if (color == "red")
            {
                char_color = 31;
            }
            else if (color == "green")
            {
                char_color = 32;
            }
            else if (color == "blown")
            {
                char_color = 33;
            }
            else if (color == "blue")
            {
                char_color = 34;
            }
            else if (color == "purple")
            {
                char_color = 35;
            }
            else if (color == "gray")
            {
                char_color = 36;
            }
            else if (color == "white")
            {
                char_color = 37;
            }
            else if (color == "none")
            {
                char_color = 39;
            }
        }
        void set_bcolor(int color)
        {
            background_color = color;
        }
        void set_bcolor(string color)
        {
            if (color == "black")
            {
                background_color = 40;
            }
            else if (color == "red")
            {
                background_color = 41;
            }
            else if (color == "green")
            {
                background_color = 42;
            }
            else if (color == "blown")
            {
                background_color = 43;
            }
            else if (color == "blue")
            {
                background_color = 44;
            }
            else if (color == "purple")
            {
                background_color = 45;
            }
            else if (color == "gray")
            {
                background_color = 46;
            }
            else if (color == "white")
            {
                background_color = 47;
            }
            else if (color == "none")
            {
                background_color = 49;
            }
        }
        void set_font(string font)
        {
            if (font == "italic")
            {
                new_line_font.emplace_back(3);
            }
            else if (font == "bold")
            {
                new_line_font.emplace_back(1);
            }
            else if (font == "half bright")
            {
                new_line_font.emplace_back(2);
            }
            else if (font == "under bar")
            {
                new_line_font.emplace_back(4);
            }
            else if (font == "blink")
            {
                new_line_font.emplace_back(5);
            }
            else if (font == "none")
            {
                new_line_font.clear();
                new_line_font.emplace_back(0);
            }
        }
        void set_font(int font)
        {
            new_line_font.emplace_back(font);
        }
        void set_default()
        {
            set_font("none");
            set_bcolor("none");
            set_ccolor("none");
        }
        void use_customized_font()
        {
            cout << "\033[";
            for (const int &i : new_line_font)
            {
                cout << i << ";";
            }
            cout << char_color << ";" << background_color << "m";
        }
        void use_default()
        {
            cout << "\033[m";
        }
        void new_line(void)
        {
            use_customized_font();
            cout << new_line_attr << new_line_mark;
            set_default();
            use_default();
        }
    }
    namespace error
    {
        bool err_flag;
        void error_at(int place, string fmt, ...)
        {
            va_list ap;
            va_start(ap, fmt);
            set_font("bold");
            set_ccolor("red");
            set_attr("err");
            new_line();
            set_font("italic");
            set_ccolor("red");
            use_customized_font();
            for (int i = 0; i < place; ++i)
            {
                cerr << " ";
            }
            cerr << "^";
            vfprintf(stderr, fmt.c_str(), ap);
            printf("\n");
            use_default();
            set_default();
            err_flag = 1;
        }
    }
}