#include <Scanner/Token.hpp>

namespace Lox {
    Token::Token(TokenType tokenType, std::string lexeme, LiteralType literal, int line)
    : type(tokenType),
      lexeme(lexeme),
      literal(literal),
      line(line) 
    {
    }

    std::ostream& operator<<(std::ostream& os, const Token& token) {
        os<<type_name(token.type)<<" "<<token.lexeme<<" "<<token.literal;
        return os;
    }
};