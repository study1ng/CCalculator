#include "calculator.hpp"
namespace np_calculator
{
    namespace tokenizer
    {
        void tokenize(const string &expr, Token &head)
        {
            string::const_iterator cur = expr.begin();
            go_next_word(cur);
            if (!('0' <= *cur && *cur <= '9'))
            {
                error_at(cur - expr.begin(), "expected the first token as number");
                err_flag = 1;
                return;
            }
            string::const_iterator end;
            end = num(cur);
            head = *(new Token(NUM, cur, end));
            Token *tcur = &head;
            cur = end;
            // WHY: IF use do-while statement THEN the head will be undefined
            while (!is_end(cur))
            {
                go_next_word(cur);
                if (*cur == '+' || *cur == '-')
                {
                    end = cur + 1;
                    tcur->connect(SIGN, cur, end);
                    tcur = tcur->get_next();
                    cur = end;
                    continue;
                }
                if ('0' <= *cur && *cur <= '9')
                {
                    end = num(cur);
                    tcur->connect(NUM, cur, end);
                    tcur = tcur->get_next();
                    cur = end;
                    continue;
                }
                error_at(cur - expr.begin(), "couldn't be tokenize");
                err_flag = 1;
                return;
            }
            tcur->connect(END, cur, ++cur);
        }
    }

    namespace parser
    {
        using tokenizer::go_next_token;
        using tokenizer::TOKENTYPE;
        // num = (0-9)+
        void num(Token &begin, const string &expr, Node &cur)
        {
            expect(TOKENTYPE::NUM, begin, expr);
            if (err_flag)
            {
                return;
            }
            cur = Node(NUM, begin.get_begin(), begin.get_end());
            go_next_token(&begin);
        }
        // expr = num ('+'|'-' num)*
        void expr(Token &begin, const string &exp, Node &head)
        {
            num(begin, exp, head);
            while (!begin.is_type(TOKENTYPE::END))
            {
                Node *lhs = new Node();
                *lhs = head;
                expect(TOKENTYPE::SIGN, begin, exp);
                if (err_flag)
                {
                    return;
                }
                if (begin.get_string() == "+")
                {
                    head = Node(PLUS);
                }
                else if (begin.get_string() == "-")
                {
                    head = Node(MINUS);
                }
                go_next_token(&begin);
                head.connect_l(lhs);
                Node *rhs = new Node();
                num(begin, exp, *rhs);
                if (err_flag)
                {
                    return;
                }
                head.connect_r(rhs);
            }
        }
        Node parse(const Token &begin, const string &exp)
        {
            Token cur = begin;
            Node head;
            expr(cur, exp, head);
            return head;
        };
        int calculate(const Node &begin)
        {
            Node cur = begin;
            if (cur.get_type() == NUM)
            {
                return stodigit(cur.get_value());
            }
            if (cur.get_type() == PLUS)
            {
                return calculate(*cur.get_lhs()) + calculate(*cur.get_rhs());
            }
            if (cur.get_type() == MINUS)
            {
                return calculate(*cur.get_lhs()) - calculate(*cur.get_rhs());
            }
            else
            {
                error_at(0, "function calculate had type other than NUM, PLUS, MINUS");
                return 0;
            }
        }
    }

    bool is_quit(string s)
    {
        return (s == "quit" || s == "q");
    };
    int calculator(void)
    {
        int line_number = 0;
        while (true)
        {
            err_flag = false;
            ++line_number;
            new_liner::set_attr("exp");
            new_liner::new_line();
            string expression;
            getline(cin, expression);
            if (is_quit(expression))
            {
                set_attr("cmd");
                new_line();
                cout << "get quit command at line " << line_number << endl;
                return 0;
            }
            tokenizer::Token cur;
            tokenize(expression, cur);
            if (err_flag)
            {
                continue;
            }
            parser::Node head = parse(cur, expression);
            if (err_flag)
            {
                continue;
            }
            int ans = calculate(head);
            if (err_flag)
            {
                continue;
            }
            set_attr("ans");
            new_line();
            cout << ans << endl;
        };
    }
}
int main(void)
{
    return np_calculator::calculator();
}
