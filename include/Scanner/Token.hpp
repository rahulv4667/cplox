#ifndef __TOKEN_H
#define __TOKEN_H
#include "LiteralType.hpp"

namespace Lox {

    #define type_name(type) (#type)
    
    enum class TokenType {
        // Single-character tokens
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, 

        // Two-character tokens
        // Bang is !
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Literals
        IDENTIFIER, STRING, NUMBER,

        // Keywords
        AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
        PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

        FILE_EOF
    };


    class Token {
        TokenType type;
        std::string lexeme;
        LiteralType literal;
        int line;

        public:
            Token(TokenType tokenType, std::string lexeme, LiteralType literal, int line);
            friend std::ostream& operator<<(std::ostream& os, const Token& token);
            void* getLiteralValue();
    };

};

#endif // __TOKEN_H