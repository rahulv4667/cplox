#include <Parser/Expression.hpp>

namespace Lox {

    Expression::Binary::Binary(Expression left, Token oprtr, Expression right)
    :   left(left),
        oprtr(oprtr),
        right(right)
    {}

    

};