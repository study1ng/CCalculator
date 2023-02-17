#include "calculate.hpp"

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
            set_font("bold");
            set_ccolor("purple");
            set_attr("exp");
            new_line();
            string expression;
            getline(cin, expression);
            if (is_quit(expression))
            {
                set_font("bold");
                set_ccolor("red");
                set_attr("cmd");
                new_line();
                set_font("italic");
                set_ccolor("red");
                use_customized_font();
                cout << "get quit command at line " << line_number << endl;
                use_default();
                set_default();
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
            int ans = calculate::calculate(head);
            if (err_flag)
            {
                continue;
            }
            set_font("bold");
            set_ccolor("green");
            set_attr("ans");
            new_line();
            set_font("bold");
            set_ccolor("green");
            use_customized_font();
            cout << ans << endl;
            set_default();
            use_default();
        };
    }
}
int main(void)
{
    return np_calculator::calculator();
}
