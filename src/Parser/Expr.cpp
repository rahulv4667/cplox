#include <Parser/Expr.hpp>
namespace Lox {
	Expr::Binary     ::Binary     ( Expr left, Token oprtr, Expr right) : 
		left(left),
		oprtr(oprtr),
		right(right)
	 {}
	Expr::Grouping   ::Grouping   ( Expr expression) : 
		expression(expression)
	 {}
	Expr::Literal    ::Literal    ( LiteralType value) : 
		value(value)
	 {}
	Expr::Unary      ::Unary      ( Token oprtr, Expr right) : 
		oprtr(oprtr),
		right(right)
	 {}
}