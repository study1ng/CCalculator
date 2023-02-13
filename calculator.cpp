#include "parser.hpp"
namespace np_calculator
{
    using parser::parse;
}
namespace np_calculator
{
    int calculator(void)
    {
        int line_number = 0;
        while (true)
        {
            err_flag = false;
            ++line_number;
            set_attr("exp");
            new_line();
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
            tokenizer::tokenize(expression, cur);
            if (err_flag)
            {
                continue;
            }
            parser::Node head = parse(cur, expression);
            if (err_flag)
            {
                continue;
            }
            int ans = parser::calculate(head);
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
