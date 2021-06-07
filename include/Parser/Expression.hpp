#ifndef __EXPRESSION_H
#define __EXPRESSION_H

#include <Scanner/Token.hpp>

namespace Lox {

    class Expression {
        class Binary;
        public:
            virtual ~Expression() = default;
        private:
            Expression() = default;
    };

    class Expression::Binary : public Expression {
        Expression left;
        Expression right;
        Token oprtr;
        Binary(Expression left, Token oprtr, Expression right);
    };

}

#endif // __EXPRESSION_H