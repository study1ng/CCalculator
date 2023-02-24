#include "calculate.hpp"

namespace np_calculator
{
    namespace calculate
    {
        int stodigit(const string &i)
        {
            int ans = 0;
            for (auto c : i)
            {
                ans *= 10;
                ans += c - '0';
            }
            return ans;
        }
        int calculate(Node &begin)
        {
            static map<string, VarStatus> var_list;
            if (begin.get_type() == parser::NODETYPE::NUM)
            {
                return stodigit(begin.get_value());
            }
            if (begin.get_type() == parser::NODETYPE::PLUS)
            {
                return calculate(*begin.get_lhs()) + calculate(*begin.get_rhs());
            }
            if (begin.get_type() == parser::NODETYPE::MINUS)
            {
                return calculate(*begin.get_lhs()) - calculate(*begin.get_rhs());
            }
            if (begin.get_type() == parser::NODETYPE::MUL)
            {
                return calculate(*begin.get_lhs()) * calculate(*begin.get_rhs());
            }
            if (begin.get_type() == parser::NODETYPE::DIV)
            {
                int lhs = calculate(*begin.get_lhs());
                int rhs = calculate(*begin.get_rhs());
                if (rhs == 0)
                {
                    error_at(0, "zero division error");
                    return 1;
                }
                return lhs / rhs;
            }
            if (begin.get_type() == parser::NODETYPE::MOD)
            {
                return calculate(*begin.get_lhs()) % calculate(*begin.get_rhs());
            }
            if (begin.get_type() == parser::NODETYPE::VAR)
            {
                if (begin.get_lhs() && begin.get_lhs()->get_type() == parser::NODETYPE::DEF_EQ)
                {
                    begin.get_lhs()->get_lhs()->stock();
                    if (var_list.count(begin.get_value()))
                    {
                        var_list.at(begin.get_value()) = VarStatus(INT, begin.get_lhs()->get_lhs());
                    }
                    else
                    {
                        var_list.insert(pair<string, VarStatus>(begin.get_value(), VarStatus(INT, begin.get_lhs()->get_lhs())));
                    }
                    return calculate(*(begin.get_lhs()->get_lhs()));
                }
                else if (!(begin.get_lhs()))
                {
                    VarStatus stat = var_list.at(begin.get_value());
                    if (stat.type == INT)
                    {
                        return calculate(*(stat.value));
                    }
                }
            }
            error_at(0, "calculate failure");
            return 0;
        }
    }
}