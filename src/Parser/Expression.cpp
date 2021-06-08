#include <Parser/Expression.hpp>

namespace Lox {

    Expression::Binary::Binary(Expression left, Token oprtr, Expression right)
    :   left(left),
        oprtr(oprtr),
        right(right)
    {}

    // template<typename T>
    // T Expression::accept(Visitor<T> v) {}

    template<typename T>
    T Expression::Binary::accept(Visitor<T> v) {
        return v.visit(*this);
    }

};