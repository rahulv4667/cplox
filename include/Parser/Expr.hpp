#include <Scanner/LiteralType.hpp>
#include <Scanner/Token.hpp>
namespace Lox {
	class Expr {
		public:
			class Binary;
			class Grouping;
			class Literal;
			class Unary;
		public:
			// virtual 
			// ~Expr() = default;
		// protected:
			Expr() = default;
			// Expr(const Expr& expr) = default;
			// Expr operator=(const Expr& expr) = default;
			Expr(const Expr& expr) {}
			Expr operator=(const Expr& expr) {}
		public:
			template<typename T>
			class Visitor;
			template<typename T>
			T accept(Visitor<T> visitor);
	};

	class Expr::Binary : public Expr {
		 Expr left;
		 Token oprtr;
		 Expr right;
		public:
			Binary( Expr left, Token oprtr, Expr right);
			// Binary() {}
			Binary(const Expr::Binary& binary):
			left(binary.left),
			right(binary.right),
			oprtr(binary.oprtr) {
				
			}

			template<typename T>
			T accept(Visitor<T> visitor) override;
	};

	class Expr::Grouping : public Expr {
		 Expr expression;
		public:
			Grouping( Expr expression);

			template<typename T>
			T accept(Visitor<T> visitor) override;
	};

	class Expr::Literal : public Expr {
		 LiteralType value;
		public:
			Literal( LiteralType value);

			template<typename T>
			T accept(Visitor<T> visitor) override;
	};

	class Expr::Unary : public Expr {
		 Token oprtr;
		 Expr right;
		public:
			Unary( Token oprtr, Expr right);

			template<typename T>
			T accept(Visitor<T> visitor) override;
	};

	template<typename T>
	class Expr::Visitor {
		public:
			virtual T visit(Expr::Binary& binary);
			virtual T visit(Expr::Grouping& grouping);
			virtual T visit(Expr::Literal& literal);
			virtual T visit(Expr::Unary& unary);
	};

	}