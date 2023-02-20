#include "fundamental.hpp"
namespace np_calculator
{
    extern bool quit_flag;
    extern bool command_flag;
    namespace command
    {
        struct CommandUsage;
        class Param;
        class Command;
        struct CommandUsage
        {
            private:
            static unsigned int longest;
            public:
            string name, usage;
            CommandUsage(string name, string usage) : name(name), usage(usage)
            {
                if (name.length() > longest)
                {
                    longest = name.length();
                }
            }
            void help() const { cout << setw(longest) << name << "= " << usage << endl;}
        };
        enum COMMANDTYPE
        {
            QUIT,
            HELP,
            SET_DEFAULT_FONT,
            SET_DEFAULT_CHAR_COLOR,
            SET_DEFAULT_BACKGROUND_COLOR,
            SET_NEWLINE_FONT,
            SET_NEWLINE_CHAR_COLOR,
            SET_NEWLINE_BACKGROUND_COLOR,
        };
        class Param
        {
        private:
            string::const_iterator begin, end;
            Param *next = nullptr;
        public:
            Param() {}
            Param(string::const_iterator begin, string::const_iterator end) : begin(begin), end(end) {}
            void connect(Param *next) { this->next = next; }
            Param *get_next() const { return next; }
            string::const_iterator get_begin() const {return begin;}
            string::const_iterator get_end() const {return end;}
            string get_value() const { return string(begin, end); }
        };
        class Command
        {
        private:
            COMMANDTYPE type;
            const Param *param = nullptr;

        public:
            Command() {}
            Command(COMMANDTYPE type) : type(type) {}
            inline void connect(Param *param) { this->param = param; }

            inline const Param* get_param() { return this->param; }
            inline void go_next_param()
            {
                const Param *tmp = param->get_next();
                delete param;
                param = tmp;
            }
            inline bool is_type(COMMANDTYPE i) { return type == i; }
        };
        void check_command(const string &expression);
        bool is_start_with(string::const_iterator & begin, const char *i);
        void check_command(const string &exp);
        Command tokenize(const string &expr);
        void do_command(Command &i);
        extern vector<CommandUsage> commands;
    }
}