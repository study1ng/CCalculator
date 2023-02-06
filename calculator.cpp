#include "calculator.hpp"
namespace np_calculator
{
    namespace tokenizer
    {
        void tokenize(const string &expr, bool &err_flag, token& head)
        {
            string::const_iterator cur = expr.begin();
            string::const_iterator end = num(cur);
            head = *(new token(NUM, cur, end));
            cur = end;
            if (!is_end(cur))
            {
                error_at(cur - expr.begin(), "contains no-number word");
                err_flag = 1;
            }
            else
            {
                err_flag = 0;
            }
            head.set_next(END, cur, ++cur);
        }
    }

    namespace parser
    {
        using tokenizer::go_next_token;
        using tokenizer::TOKENTYPE;
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
    int calculator(void)
    {
        bool err_flag = false;
        while (true)
        {
            new_liner::set_attr("exp");
            new_liner::new_line();
            string expression;
            cin >> expression;
            if (is_quit(expression))
            {
                return 0;
            }
            tokenizer::token cur;
            tokenize(expression, err_flag, cur);
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
int main(void)
{
    return np_calculator::calculator();
}
