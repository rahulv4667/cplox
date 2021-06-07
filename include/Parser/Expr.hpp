#include <Scanner/LiteralType.hpp>
#include <Scanner/Token.hpp>
namespace Lox {
	class Expr {
		class Binary     ;
		class Grouping   ;
		class Literal    ;
		class Unary      ;
		public:
			virtual ~Expr() = default;
		private:
			Expr() = default;
	};

	class Expr::Binary      : public Expr {
		 Expr left;
		 Token oprtr;
		 Expr right;
		Binary     ( Expr left, Token oprtr, Expr right);
	};

	class Expr::Grouping    : public Expr {
		 Expr expression;
		Grouping   ( Expr expression);
	};

	class Expr::Literal     : public Expr {
		 LiteralType value;
		Literal    ( LiteralType value);
	};

	class Expr::Unary       : public Expr {
		 Token oprtr;
		 Expr right;
		Unary      ( Token oprtr, Expr right);
	};

	}