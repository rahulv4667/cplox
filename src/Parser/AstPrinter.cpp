#include <Parser/Expr.hpp>
#include <string>
#include <vector>
#include <sstream>
namespace Lox {
template<typename T=void>
class AstPrinter: public Expr::Visitor<std::string> {
    public:
    std::string print(Expr::Binary expr) {
        return expr.accept(this);
    }

    std::string print(Expr::Grouping expr) {
        return expr.accept(this);
    }

    std::string print(Expr::Literal expr) {
        return expr.accept(this);
    }

    std::string print(Expr::Unary expr) {
        return expr.accept(this);
    }

    std::string parenthesize(const std::string& name, std::vector<Expr> exprs) {
        std::stringstream ss;
        ss<<"("<<name;
        for(Expr expr: exprs) {
            ss<<" "<<expr.accept(this);
        }
        ss<<")";

        return ss.str();
    }

    std::string visit(Expr::Binary& expr) override {
        return this->parenthesize(expr.oprtr.lexeme, {expr.left, expr.right});
    }

    std::string visit(Expr::Grouping& expr) override {
        return this->parenthesize("group", expr.expression);
    }

    std::string visit(Expr::Literal& expr) override {
        if(expr.value.isNull()) return "nil";
        return expr.value.toString();
    }

    std::string visit(Expr::Unary& expr) override {
        return this->parenthesize(expr.oprtr.lexeme, {expr.right});
    }
};

};