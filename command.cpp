#include "command.hpp"

namespace np_calculator
{
    bool quit_flag = false;
    bool command_flag = false;

    namespace command
    {
        unsigned int CommandUsage::longest = 0;
        vector<CommandUsage> commands{
            CommandUsage("quit", "usage: quit.\n. Quit from calculator, this will take no params"),
            CommandUsage("help", "usage: help [param]\nPrint usage infomration, to know about specific information, put the command name in the param.param can be 'production_rule', 'commands'."),
            CommandUsage("set default font", "usage: set default font + [param]*\nparams can be 'bold', 'italic', 'half_bright', 'under_bar', 'blink', 'none'. If you put none in the params, none will replace any used font"),
            CommandUsage("set default char color", "usage: set default char color + [param]\nParam can be 'black', 'red', 'green', 'blown', 'blue', 'purple', 'gray', 'none'."),
            CommandUsage("set default background color", "usage: set default background color + [param]\nparam can be 'black', 'red', 'green', 'blown', 'blue', 'purple', 'gray', 'none'."),
            CommandUsage("set newline font", "usage: set newline font + [param]*\nparams can be 'bold', 'italic', 'half_bright', 'under_bar', 'blink', 'none'. If you put none in the params, none will replace any used font."),
            CommandUsage("set newline char color", "usage: set newline char color + [param]\nParam can be 'black', 'red', 'green', 'blown', 'blue', 'purple', 'gray', 'none'."),
            CommandUsage("set newline background color", "usage: set newline background color + [param]\nparam can be 'black', 'red', 'green', 'blown', 'blue', 'purple', 'gray', 'none'.")};
        bool is_start_with(string::const_iterator &begin, const char *i)
        {
            string::const_iterator tmp = begin;
            for (int j = 0; *(i + j); ++j)
            {
                if (*begin != *(i + j))
                {
                    begin = tmp;
                    return false;
                }
                ++begin;
            }
            return true;
        }
        Command tokenize(const string &expr)
        {
            string::const_iterator begin = expr.begin();
            go_next_word(begin);
            Command *command;
            go_next_word(begin);
            ++begin;
            if (is_start_with(begin, "quit"))
            {
                command = new Command(QUIT);
            }
            else if (is_start_with(begin, "set default background color"))
            {
                command = new Command(SET_DEFAULT_BACKGROUND_COLOR);
            }
            else if (is_start_with(begin, "set default char color"))
            {
                command = new Command(SET_DEFAULT_CHAR_COLOR);
            }
            else if (is_start_with(begin, "set default font"))
            {
                command = new Command(SET_DEFAULT_FONT);
            }
            else if (is_start_with(begin, "set newline font"))
            {
                command = new Command(SET_NEWLINE_FONT);
            }
            else if (is_start_with(begin, "set newline char color"))
            {
                command = new Command(SET_NEWLINE_CHAR_COLOR);
            }
            else if (is_start_with(begin, "set newline background color"))
            {
                command = new Command(SET_NEWLINE_BACKGROUND_COLOR);
            }
            else if (is_start_with(begin, "help"))
            {
                command = new Command(HELP);
            }
            else
            {
                command = new Command(HELP);
                error_at(begin - expr.begin(), "Does not match any commands. To check what command is there, input: %%help");
                err_flag = 1;
                return *command;
            }
            if (is_end(begin))
            {
                return *command;
            }
            Param *pbegin;
            string::const_iterator end = begin;
            while (*end == ' ')
            {
                ++end;
            }
            while (*end != ' ' && *end != '\0')
            {
                ++end;
            }
            pbegin = new Param(begin, end);
            Param *pcur = pbegin;
            begin = end;
            while (!is_end(begin))
            {
                while (*end == ' ')
                {
                    ++end;
                }
                while (*end != ' ' && *end != '\0')
                {
                    ++end;
                }
                pcur->connect(new Param(begin, end));

                begin = end;
                pcur = pcur->get_next();
            }
            command->connect(pbegin);
            return *command;
        }
        void do_command(Command &i)
        {
            if (i.is_type(QUIT))
            {
                if (i.get_param())
                {
                    commands.at(0).help();
                }
                set_newline_font("bold");
                set_newline_char_color("red");
                set_attr("cmd");
                newline();
                set_newline_font("italic");
                set_newline_char_color("red");
                use_newline_customized_font();
                cout << "get quit command at line " << line_number << endl;
                quit_flag = true;
                return;
            }
            if (i.is_type(SET_NEWLINE_BACKGROUND_COLOR))
            {
                if (!i.get_param())
                {
                    commands.at(7).help();
                    return;
                }
                string color = i.get_param()->get_value();
                set_newline_background_color(color);
                return;
            }
            if (i.is_type(SET_NEWLINE_CHAR_COLOR))
            {
                if (!i.get_param())
                {
                    commands.at(6).help();
                    return;
                }
                string color = i.get_param()->get_value();
                set_newline_char_color(color);
                return;
            }
            if (i.is_type(SET_DEFAULT_BACKGROUND_COLOR))
            {
                if (!i.get_param())
                {
                    commands.at(4).help();
                    return;
                }
                string color = i.get_param()->get_value();
                set_default_background_color(color);
                return;
            }
            if (i.is_type(SET_DEFAULT_CHAR_COLOR))
            {
                if (!i.get_param())
                {
                    commands.at(3).help();
                    return;
                }
                string color = i.get_param()->get_value();
                set_default_char_color(color);
                return;
            }
            if (i.is_type(SET_DEFAULT_FONT))
            {
                if (!i.get_param())
                {
                    commands.at(2).help();
                    return;
                }
                while (i.get_param())
                {
                    string font = i.get_param()->get_value();
                    set_default_font(font);
                    i.go_next_param();
                }
            }
            if (i.is_type(SET_NEWLINE_FONT))
            {
                if (!i.get_param())
                {
                    commands.at(5).help();
                    return;
                }
                while (i.get_param())
                {
                    string font = i.get_param()->get_value();
                    set_newline_font(font);
                    i.go_next_param();
                }
            }
            if (i.is_type(HELP))
            {
                if (!(i.get_param()))
                {
                    cout << "Calulator.\n To get help about commands, type help command. Type help [param] to get help about the param, which includes 'command', 'production_rule'.\n";
                    return;
                }
                if (i.get_param()->get_value() == "command")
                {
                    cout << "Here is the list of commands." << endl;
                    for (const CommandUsage &i : commands)
                    {
                        i.help();
                        cout << endl;
                    }
                    return;
                }
                if (i.get_param()->get_value() == "production_rule")
                {
                    cout << "Here is the production rule" << endl
                         << "Num = (0-9)*" << endl
                         << "Variable = $(0-9a-zA-Z)*" << endl
                         << "Definition = Variable (:= Expr)?" << endl
                         << "Primary = Num | Definition | '('Expr')'" << endl
                         << "Mul = Primary [(* | / | %) num]*" << endl
                         << "Expr = Mul [(+ | -) num]*" << endl;
                    return;
                }
                commands.at(1).help();
            }
        }
        void check_command(const string &exp)
        {
            string::const_iterator begin = exp.begin();
            go_next_word(begin);
            command_flag = (*begin == '@');
        }
    }
}