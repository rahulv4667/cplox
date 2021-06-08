#include <Parser/Expr.hpp>
namespace Lox {
	Expr::Binary::Binary( Expr left, Token oprtr, Expr right) : 
		left(left),
		oprtr(oprtr),
		right(right)
	 {}

	template<typename T>
	T Expr::Binary::accept(Visitor<T> visitor) {
		return visitor.visit(*this);
	}

	Expr::Grouping::Grouping( Expr expression) : 
		expression(expression)
	 {}

	template<typename T>
	T Expr::Grouping::accept(Visitor<T> visitor) {
		return visitor.visit(*this);
	}

	Expr::Literal::Literal( LiteralType value) : 
		value(value)
	 {}

	template<typename T>
	T Expr::Literal::accept(Visitor<T> visitor) {
		return visitor.visit(*this);
	}

	Expr::Unary::Unary( Token oprtr, Expr right) : 
		oprtr(oprtr),
		right(right)
	 {}

	template<typename T>
	T Expr::Unary::accept(Visitor<T> visitor) {
		return visitor.visit(*this);
	}

}