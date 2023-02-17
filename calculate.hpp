#include "parser.hpp"

namespace np_calculator
{
    namespace calculate
    {
        using parser::Node;
        int stodigit(const string &i);
        int stodigit(string::const_iterator begin, string::const_iterator end);
        int calculate(const Node &begin);
        enum VARTYPE
        {
            INT,
        };
        struct VarStatus
        {
            VARTYPE type;
            string value;
            VarStatus(VARTYPE type, const string::const_iterator &begin, const string::const_iterator &end): type(type), value(begin, end){}
        };
    }
}