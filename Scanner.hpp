#pragma once
#include <string>
#include <vector>
#include <fstream>

namespace Lox {

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
        Lox::TokenType type;
        std::string lexeme;
        std::any literal;
        int line;

        public:
            Token(TokenType tokenType, std::string lexeme, std::any literal, int line);
            friend std::ostream& operator<<(std::ostream& os, const Token& t);
    };

    class Scanner {
        public:
            Scanner(const std::string& source);
            
            std::vector<Token> scanTokens();
    };
}