#pragma once
#include "tokenizer.hpp"
namespace np_calculator
{
    using tokenizer::Token;
    using tokenizer::tokenize;
    namespace parser
    {
        class Node;
        enum NODETYPE
        {
            NUM,
            PLUS,
            MINUS,
            MUL,
            DIV,
            MOD,
            VAR,
            DEF_EQ,
        };

        using tokenizer::go_next_token;
        using tokenizer::TOKENTYPE;
        void num(Token &begin, const string &expr, Node &cur);
        void variable(Token &begin, const string &expr, Node &cur);
        void definition(Token &begin, const string &exp, Node &cur);
        void primary(Token &begin, const string &exp, Node &head);
        void mul(Token &begin, const string &exp, Node &head);
        void expr(Token &begin, const string &exp, Node &head);
        void parse(const Token &begin, const string &exp, Node &head);
        bool consume(TOKENTYPE type, Token &i);
        void expect(TOKENTYPE type, Token &i, const string &expr);
        void expect(const char *expected, Token &actual, const string &expr);
    }

    namespace parser
    {
        class Node
        {
        private:
            NODETYPE type;
            string value;
            bool is_stocked = false;
            Node *lhs = nullptr;
            Node *rhs = nullptr;

        public:
            Node();
            Node(NODETYPE type);
            Node(NODETYPE type, const string::const_iterator &b, const string::const_iterator &e);
            ~Node();
            void connect_l(Node *l);
            void stock(void);
            void unstock(void)
            {
                this->is_stocked = false;
            }
            bool get_is_stocked(void)
            {
                return this->is_stocked;
            }
            void connect_r(Node *r);
            NODETYPE get_type() const;
            string get_value() const;
            string::const_iterator get_begin() const;
            string::const_iterator get_end() const;
            Node *get_lhs(void);
            Node *get_rhs(void);
        };
    }
}
