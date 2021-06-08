#ifndef __EXPRESSION_H
#define __EXPRESSION_H

#include <Scanner/Token.hpp>

namespace Lox {

    class Expression {

        template<typename T>
        class Visitor;

        class Binary;
        public:
            virtual ~Expression() = default;

            template<typename T>
            T accept(Visitor<T> visitor);
        private:
            Expression() = default;
    };

    class Expression::Binary : public Expression {
        Expression left;
        Expression right;
        Token oprtr;
        Binary(Expression left, Token oprtr, Expression right);

        template<typename T>
        T accept(Visitor<T> visitor) override;
    };

    template<typename T>
    class Expression::Visitor {
        public: 
            virtual T visit(Binary& b);
    };

}

#endif // __EXPRESSION_H