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
        int calculate(const Node &begin)
        {
            static map<string, VarStatus> var_list;
            Node cur = begin;
            if (cur.get_type() == parser::NODETYPE::NUM)
            {
                return stodigit(cur.get_value());
            }
            if (cur.get_type() == parser::NODETYPE::PLUS)
            {
                return calculate(*cur.get_lhs()) + calculate(*cur.get_rhs());
            }
            if (cur.get_type() == parser::NODETYPE::MINUS)
            {
                return calculate(*cur.get_lhs()) - calculate(*cur.get_rhs());
            }
            if (cur.get_type() == parser::NODETYPE::MUL)
            {
                return calculate(*cur.get_lhs()) * calculate(*cur.get_rhs());
            }
            if (cur.get_type() == parser::NODETYPE::DIV)
            {
                int lhs = calculate(*cur.get_lhs());
                int rhs = calculate(*cur.get_rhs());
                if (rhs == 0)
                {
                    error_at(0, "zero division error");
                    return 1;
                }
                return lhs / rhs;
            }
            if (cur.get_type() == parser::NODETYPE::MOD)
            {
                return calculate(*cur.get_lhs()) % calculate(*cur.get_rhs());
            }
            if (cur.get_type() == parser::NODETYPE::VAR)
            {
                if (cur.get_lhs() && cur.get_lhs()->get_type() == parser::NODETYPE::DEF_EQ)
                {
                    if (var_list.count(cur.get_value()))
                    {
                        var_list.at(cur.get_value()) = VarStatus(INT, cur.get_lhs()->get_lhs()->get_begin(), cur.get_lhs()->get_lhs()->get_end());
                    }
                    else
                    {
                        var_list.insert(pair<string, VarStatus>(cur.get_value(), VarStatus(INT, cur.get_lhs()->get_lhs()->get_begin(), cur.get_lhs()->get_lhs()->get_end())));
                    }
                    return calculate(*(cur.get_lhs()->get_lhs()));
                }
                else if (!(cur.get_lhs()))
                {
                    VarStatus stat = var_list.at(cur.get_value());
                    if (stat.type == INT)
                    {
                        return stodigit(stat.value);
                    }
                }
            }
            error_at(0, "calculate failure");
            return 0;
        }
    }
}