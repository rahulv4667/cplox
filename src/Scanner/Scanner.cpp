#include <string>
#include <variant>
#include <Scanner/Scanner.hpp>
#include <Error/Error.hpp>

namespace Lox {

    Scanner::Scanner(const std::string& source)
    : source(source),
      start(0), 
      current(0),
      line(1) {

    }

    std::vector<Token> Scanner::scanTokens() {
        
        while(!isAtEnd()) {
            // We are the beginning of the next lexeme
            start = current;
            scanToken();
        }

        this->tokens.emplace_back(TokenType::FILE_EOF, "", LiteralType(), line);
        return this->tokens;

    }

    bool Scanner::isAtEnd() {
        return this->current >= this->source.length();
    }

    char Scanner::advance() {
        return this->source[this->current++];
    }

    void Scanner::addToken(TokenType type) {
        this->addToken(type, LiteralType());
    }

    void Scanner::addToken(TokenType type, LiteralType literal) {
        std::string text = this->source.substr(start, current-start);
        this->tokens.emplace_back(type, text, literal, line);
    }

    void Scanner::scanToken() {
        char c = advance();

        switch(c) {
            case '(': addToken(TokenType::LEFT_PAREN); break;
            case ')': addToken(TokenType::RIGHT_PAREN); break;
            case '{': addToken(TokenType::LEFT_BRACE); break;
            case '}': addToken(TokenType::RIGHT_BRACE); break;
            case ',': addToken(TokenType::COMMA); break;
            case '.': addToken(TokenType::DOT); break;
            case '+': addToken(TokenType::PLUS); break;
            case '-': addToken(TokenType::MINUS); break;
            case '*': addToken(TokenType::STAR); break;
            case '/': addToken(TokenType::SLASH); break;
            case ';': addToken(TokenType::SEMICOLON); break;

            default: 
                error(line, "Unexpected character."); 
                break;
        }
    }

    

};
