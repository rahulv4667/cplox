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
        os<<token.type<<" "<<token.lexeme<<" "<<token.literal;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const TokenType token) {
      std::string s;
      #define PROCESS_VAL(p) case(p): s = #p; break;
      switch(token) {
        PROCESS_VAL(TokenType::AND);
        PROCESS_VAL(TokenType::BANG);
        PROCESS_VAL(TokenType::BANG_EQUAL);
        PROCESS_VAL(TokenType::CLASS);
        PROCESS_VAL(TokenType::COMMA);
        PROCESS_VAL(TokenType::DOT);
        PROCESS_VAL(TokenType::ELSE);
        PROCESS_VAL(TokenType::EQUAL);
        PROCESS_VAL(TokenType::EQUAL_EQUAL);
        PROCESS_VAL(TokenType::FALSE);
        PROCESS_VAL(TokenType::FILE_EOF);
        PROCESS_VAL(TokenType::FOR);
        PROCESS_VAL(TokenType::FUN);
        PROCESS_VAL(TokenType::GREATER);
        PROCESS_VAL(TokenType::GREATER_EQUAL);
        PROCESS_VAL(TokenType::IDENTIFIER);
        PROCESS_VAL(TokenType::IF);
        PROCESS_VAL(TokenType::LEFT_BRACE);
        PROCESS_VAL(TokenType::LEFT_PAREN);
        PROCESS_VAL(TokenType::LESS);
        PROCESS_VAL(TokenType::LESS_EQUAL);
        PROCESS_VAL(TokenType::MINUS);
        PROCESS_VAL(TokenType::NIL);
        PROCESS_VAL(TokenType::NUMBER);
        PROCESS_VAL(TokenType::OR);
        PROCESS_VAL(TokenType::PLUS);
        PROCESS_VAL(TokenType::PRINT);
        PROCESS_VAL(TokenType::RETURN);
        PROCESS_VAL(TokenType::RIGHT_BRACE);
        PROCESS_VAL(TokenType::RIGHT_PAREN);
        PROCESS_VAL(TokenType::SEMICOLON);
        PROCESS_VAL(TokenType::SLASH);
        PROCESS_VAL(TokenType::STAR);
        PROCESS_VAL(TokenType::STRING);
        PROCESS_VAL(TokenType::SUPER);
        PROCESS_VAL(TokenType::TRUE);
        PROCESS_VAL(TokenType::VAR);
        PROCESS_VAL(TokenType::WHILE);
      }
      #undef PROCESS_VAL

      os<<s;
      return os;
    }
};