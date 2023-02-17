#include "parser.hpp"

namespace np_calculator
{
    namespace parser
    {
        bool consume(TOKENTYPE type, Token &i)
        {
            return i.is_type(type);
        }
        void expect(TOKENTYPE type, Token &i, const string &expr)
        {
            if (i.is_type(type))
            {
                return;
            }
            else if (type == TOKENTYPE::NUM)
            {
                error_at(i.get_place(expr.begin()), "expected NUM alternative to %s", i.get_string());
                return;
            }
        }
        void expect(const char *expected, Token &actual, const string &expr)
        {
            if (actual.get_string() == expected)
            {
                return;
            }
            else
            {
                error_at(actual.get_place(expr.begin()), "expected %s but get %s", expected, actual.get_string().c_str());
                return;
            }
        }
    }

    namespace parser
    {
        Node::Node(){};
        Node::Node(NODETYPE type) : type(type){};
        Node::Node(NODETYPE type, const string::const_iterator &b, const string::const_iterator &e) : type(type), begin(b), end(e){};

        void Node::connect_l(Node *l) { this->lhs = l; }
        void Node::connect_r(Node *r) { this->rhs = r; }
        NODETYPE Node::get_type(void) { return this->type; }
        string Node::get_value(void) { return string(begin, end); }
        string::const_iterator Node::get_begin(void) { return begin; }
        string::const_iterator Node::get_end(void) { return end; }
        Node *Node::get_lhs(void) { return this->lhs; }
        Node *Node::get_rhs(void) { return this->rhs; }
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
        void variable(Token &begin, const string &expr, Node &cur)
        {
            expect(TOKENTYPE::VAR, begin, expr);
            if (err_flag)
            {
                return;
            }
            cur = Node(VAR, begin.get_begin(), begin.get_end());
            go_next_token(&begin);
        }
        void definition(Token &begin, const string &exp, Node &cur)
        {
            variable(begin, exp, cur);
            if (err_flag)
            {
                return;
            }
            if (begin.get_string() == ":=")
            {
                cur.connect_l(new Node(DEF_EQ, begin.get_begin(), begin.get_end()));
                go_next_token(&begin);
                Node* lhs = new Node;
                expr(begin, exp, *lhs);
                cur.get_lhs()->connect_l(lhs);
            }
        }
        // primary = definition | num | '(' expr ')'
        void primary(Token &begin, const string &exp, Node &head)
        {
            if (begin.get_type() == TOKENTYPE::VAR)
            {
                definition(begin, exp, head);
            }
            else if (begin.get_type() == TOKENTYPE::NUM)
            {
                num(begin, exp, head);
            }
            else
            {
                expect("(", begin, exp);
                go_next_token(&begin);
                expr(begin, exp, head);
                expect(")", begin, exp);
                go_next_token(&begin);
            }
        }
        // mul = primary ('*'|'/' primary)*
        void mul(Token &begin, const string &exp, Node &head)
        {
            primary(begin, exp, head);
            while (!begin.is_type(TOKENTYPE::END))
            {
                Node *lhs = new Node();
                *lhs = head;
                expect(TOKENTYPE::SIGN, begin, exp);
                if (err_flag)
                {
                    return;
                }
                if (begin.get_string() == "*")
                {
                    head = Node(MUL);
                }
                else if (begin.get_string() == "/")
                {
                    head = Node(DIV);
                }
                else if (begin.get_string() == "%")
                {
                    head = Node(MOD);
                }
                else
                {
                    break;
                }
                go_next_token(&begin);
                head.connect_l(lhs);
                Node *rhs = new Node();
                primary(begin, exp, *rhs);
                if (err_flag)
                {
                    return;
                }
                head.connect_r(rhs);
            }
        }
        // expr = mul ('+'|'-' mul)*
        void expr(Token &begin, const string &exp, Node &head)
        {
            mul(begin, exp, head);
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
                else
                {
                    break;
                }
                go_next_token(&begin);
                head.connect_l(lhs);
                Node *rhs = new Node();
                mul(begin, exp, *rhs);
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

    }
}