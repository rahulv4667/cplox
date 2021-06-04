#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <variant>
#include "Scanner/Token.hpp"

namespace Lox {

    class Scanner {
        private:
            std::string source;
            std::vector<Token> tokens;

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

            char advance();
            void addToken(TokenType type);
            void addToken(TokenType type, LiteralType literal);
        public:
            Scanner(const std::string& source);
            std::vector<Token> scanTokens();
    };
}