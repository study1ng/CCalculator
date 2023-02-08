#include "calculator.hpp"
namespace np_calculator
{
    namespace tokenizer
    {
        void tokenize(const string &expr, bool &err_flag, Token &head)
        {
            string::const_iterator cur = expr.begin();
            string::const_iterator end = num(cur);
            head = *(new Token(NUM, cur, end));
            cur = end;
            if (!is_end(cur))
            {
                error_at(cur - expr.begin(), "couldn't tokenize");
                err_flag = 1;
            }
            else
            {
                err_flag = 0;
            }
            head.connect(END, cur, ++cur);
        }
    }

    namespace parser
    {
        using tokenizer::go_next_token;
        using tokenizer::TOKENTYPE;
        Node num(Token &begin)
        {
            expect(TOKENTYPE::NUM, begin);
            string value(begin.get_string());
            go_next_token(&begin);
            return Node(NUM, value);
        }
        Node parse(const Token &begin)
        {
            Token cur = begin;
            Node head;
            while (cur.get_type() != TOKENTYPE::END)
            {
                Node ncur = num(cur);
                head = ncur;
            }
            return head;
        };
        int calculate(const Node &begin)
        {
            Node cur = begin;
            if (cur.get_type() == NUM)
            {
                return stodigit(cur.get_value());
            }
            else
            {
                return 0;
            }
        }
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
            // string expression("01234");
            string expression;
            cin >> expression;
            if (is_quit(expression))
            {
                return 0;
            }
            tokenizer::Token cur;
            tokenize(expression, err_flag, cur);
            if (err_flag)
            {
                continue;
            }
            set_attr("ans");
            new_line();
            cout << calculate(parse(cur)) << endl;
            delete &cur;
        };
    }
}
int main(void)
{
    return np_calculator::calculator();
}
