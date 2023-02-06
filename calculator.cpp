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

    class token;
    bool is_quit(string);
    string num(string::const_iterator&);
    bool is_end(string::const_iterator&);
    void set_attr(string);
    void set_mark(string);
    void new_line(void);
    void error_at(int place, string fmt, ...);
    token tokenize(const string& expr, bool& err_flag);

    int calcaulator(void);

    enum NODETYPE
    {
        NUM,
    };
    class token
    {
        private:
        TOKENTYPE type;
        string value;
        token* next;
        public:
        token(const TOKENTYPE type, const string value): type(type), value(value){};
        token(){};
        void set_next(const TOKENTYPE type, const string value)
        {
            this->next = new token(type, value);
        }
        token* get_next(void)
        {
            return this->next;
        }
        TOKENTYPE get_type(void)
        {
            return this->type;
        }
        string get_string(void)
        {
            return this->value;
        }
    };
    void go_next_word(string::const_iterator &i)
    {
        while (*i == ' ')
        {
            ++i;
        }
    }
    void go_next_token(token* cur)
    {
        token* next = cur->get_next();
        delete cur;
        cur = next;
    }
    token tokenize(const string &expr, bool &err_flag)
    {
        token *head;
        string::const_iterator cur = expr.begin();
        head = new token(NUM, num(cur));
        if (!is_end(cur))
        {
            error_at(cur - expr.begin(), "contains no-number word");
            err_flag = 1;
            return *head;
        }
        else
        {
            err_flag = 0;
        }
        head->set_next(END, "\0");
        return *head;
    }
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
    string num(string::const_iterator& begin)
    {
        go_next_word(begin);
        if (!('0' <= *begin && *begin <= '9'))
        {
            return string("");
        }
        while (*begin == '0')
        {
            ++begin;
        }
        string::const_iterator cur = begin;
        while ('0' <= *begin && *begin <= '9')
        {
            ++begin;
        }
        return string(cur, begin);
    }
    bool is_end(string::const_iterator& begin)
    {
        go_next_word(begin);
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
        bool err_flag = false;
        while (true)
        {
            set_attr("exp");
            new_line();
            string expression;
            cin >> expression;
            if (is_quit(expression))
            {
                return 0;
            }
            token cur = tokenize(expression, err_flag);
            if (err_flag)
            {
                continue;
            }
            set_attr("ans");
            new_line();
            cout << expression << " = " << cur.get_string() << endl;
            delete &cur;
        };
    }
}