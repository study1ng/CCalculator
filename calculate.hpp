#include "parser.hpp"

namespace np_calculator
{
    namespace calculate
    {
        using parser::Node;
        int stodigit(const string &i);
        int stodigit(string::const_iterator begin, string::const_iterator end);
        int calculate(Node &begin);
        enum VARTYPE
        {
            INT,
        };
        struct VarStatus
        {
            VARTYPE type;
            Node *value;
            VarStatus(VARTYPE type, Node *value) : type(type), value(value) {}
        };
    }
}