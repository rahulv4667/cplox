#ifndef __SCANNER_H
#define __SCANNER_H

#include <string>
#include <vector>
#include <fstream>
#include <variant>
#include <map>
#include <Scanner/Token.hpp>

namespace Lox {

    class Scanner {
        private:
            std::string source;
            std::vector<Token> tokens;

            static std::map<std::string, TokenType> keywords;
            static std::map<std::string, TokenType> create_keywords();
            /**
             * `start` and `current` fields are offsets that index to the string.
             * `start` field points to the first character in lexeme being scanned
             * `current` points to the character currently being recognised.
             * 
             * `line` field tracks what source line `current` is on so we can produce
             * tokens that know their location.
             * 
             */
            int start;
            int current;
            int line;

            bool isAtEnd();
            void scanToken();
            bool match(char expected);

            char peek();
            char advance();
            char peekNext();
            void readNumber();
            void readString();
            void readIdentifier();
            bool isDigit(char c);
            bool isAlpha(char c);
            bool isAlphaNumeric(char c);
            void addToken(TokenType type);
            void addToken(TokenType type, LiteralType literal);
        public:
            Scanner(const std::string& source);
            std::vector<Token> scanTokens();
    };
}


#endif // __SCANNER_H