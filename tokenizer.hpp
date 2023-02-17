#pragma once

#include "fundamental.hpp"
namespace np_calculator
{
    namespace tokenizer
    {
        enum TOKENTYPE
        {
            NUM,
            END,
            SIGN,
            VAR,
        };
        class Token;
        class Token
        {
        private:
            TOKENTYPE type;
            Token *next = nullptr;
            string::const_iterator begin;
            string::const_iterator end;

        public:
            Token(const TOKENTYPE type, const string &value) : type(type), begin(value.begin()), end(value.end()){};
            Token(){};
            Token(const TOKENTYPE type, const string::const_iterator &begin, const string::const_iterator &end) : type(type), begin(begin), end(end){};
            void connect(const TOKENTYPE type, const string::const_iterator &begin, const string::const_iterator &end)
            {
                this->next = new Token(type, begin, end);
            }
            Token *get_next(void) const
            {
                return this->next;
            }
            TOKENTYPE get_type(void) const
            {
                return this->type;
            }
            string get_string(void) const
            {
                return string(begin, end);
            }
            const string::const_iterator &get_begin(void) const
            {
                return begin;
            }
            const string::const_iterator &get_end(void) const
            {
                return end;
            }
            int get_place(string::const_iterator str_begin) const
            {
                return this->begin - str_begin;
            }
            bool is_type(TOKENTYPE type) const
            {
                return this->type == type;
            }
        };
        void tokenize(const string &expr, Token &head);
        void go_next_token(Token *cur);
        void go_next_word(string::const_iterator &);
        string::const_iterator sig(string::const_iterator &);
        string::const_iterator num(string::const_iterator &);
        string::const_iterator var(string::const_iterator &begin);
        bool is_end(string::const_iterator &);
    }
}
