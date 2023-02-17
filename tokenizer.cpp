#include "fundamental.hpp"
#include "tokenizer.hpp"
namespace np_calculator
{
    namespace tokenizer
    {
        string::const_iterator num(string::const_iterator &begin)
        {
            go_next_word(begin);
            while (*begin == '0')
            {
                ++begin;
            }
            string::const_iterator cur = begin;
            while ('0' <= *cur && *cur <= '9')
            {
                ++cur;
            }
            return cur;
        }
        string::const_iterator var(string::const_iterator &begin)
        {
            go_next_word(begin);
            string::const_iterator cur = begin + 1;
            while (('0' <= *cur && *cur <= '9') || ('a' <= *cur && *cur <= 'z') || ('A' <= *cur && *cur <= 'Z'))
            {
                ++cur;
            }
            return cur;
        }
        bool is_end(string::const_iterator &begin)
        {
            go_next_word(begin);
            return (*begin == '\n' || *begin == '\0');
        }
        void go_next_word(string::const_iterator &i)
        {
            while (*i == ' ' || *i == '\t')
            {
                ++i;
            }
        }

        void go_next_token(Token *cur)
        {
            Token *next = cur->get_next();
            delete cur;
            *cur = *next;
        }

        void tokenize(const string &expr, Token &head)
        {
            string::const_iterator cur = expr.begin();
            go_next_word(cur);
            if (!('0' <= *cur && *cur <= '9') && *cur != '(' && *cur != '$')
            {
                error_at(cur - expr.begin(), "expected the first token as number or variable");
                err_flag = 1;
                return;
            }
            string::const_iterator end;
            if ('0' <= *cur && *cur <= '9')
            {
                end = num(cur);
                head = *(new Token(NUM, cur, end));
            }
            else if (*cur == '(')
            {
                end = cur + 1;
                head = *(new Token(SIGN, cur, end));
            }
            else if (*cur == '$')
            {
                end = var(cur);
                head = *(new Token(VAR, cur, end));
            }
            Token *tcur = &head;
            cur = end;
            // WHY: IF use do-while statement THEN the head will be undefined
            while (!is_end(cur))
            {
                if (*cur == '+' || *cur == '-' || *cur == '*' || *cur == '/' || *cur == '%' || *cur == '(' || *cur == ')')
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
                if (*cur == '$')
                {
                    end = var(cur);
                    tcur -> connect(VAR, cur, end);
                    tcur = tcur -> get_next();
                    cur = end;
                    continue;
                }
                if (*cur == ':' && *(cur + 1) == '=')
                {
                    end = cur + 2;
                    tcur -> connect(SIGN, cur, end);
                    tcur = tcur -> get_next();
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
}