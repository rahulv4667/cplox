#include <string>
#include <variant>
#include <Scanner/Scanner.hpp>
#include <Error/Error.hpp>

namespace Lox {

    std::map<std::string, TokenType> Scanner::keywords = {
                {"and", TokenType::AND},
                {"class", TokenType::CLASS},
                {"else", TokenType::ELSE},
                {"false", TokenType::FALSE},
                {"true", TokenType::TRUE},
                {"fun", TokenType::FUN},
                {"for", TokenType::FOR},
                {"if", TokenType::IF},
                {"nil", TokenType::NIL},
                {"or", TokenType::OR},
                {"print", TokenType::PRINT},
                {"return", TokenType::RETURN},
                {"super", TokenType::SUPER},
                {"this", TokenType::THIS},
                {"true", TokenType::TRUE},
                {"var", TokenType::VAR},
                {"while", TokenType::WHILE}
            }; 


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
        std::string text = this->source.substr(this->start, this->current-this->start);
        this->tokens.emplace_back(type, text, literal, line);
    }

    bool Scanner::match(char expected) {
        if(this->isAtEnd()) return false;
        if(this->source[this->current]!=expected) return false;
        this->current++;
        return true;
    }

    char Scanner::peek() {
        if(this->isAtEnd()) return '\0';
        return this->source[this->current];
    }

    char Scanner::peekNext() {
        if((this->current)+1 >= this->source.length()) return '\0';
        return this->source[this->current+1];
    }

    bool Scanner::isAlpha(char c) {
        return isalpha(c)||c=='_';
    }

    bool Scanner::isAlphaNumeric(char c) {
        return this->isAlpha(c)||this->isDigit(c);
    }

    bool Scanner::isDigit(char c) {
        return c>='0' && c<='9';
    }


    void Scanner::readString() {

        while(this->peek() != '"' && !this->isAtEnd()) {
            if(this->peek()=='\n') line++;
            this->advance();
        }

        if(this->isAtEnd()) {
            Lox::error(line, "Unterminated string");
            return;
        }

        // don't change the order of below three statements;
        // Trim the surrounding quotes.
        std::string value = this->source.substr(this->start+1, (this->current)-(this->start)-1);

        // The closing ".
        this->advance();

        this->addToken(TokenType::STRING, LiteralType(value));        

    }

    
    void Scanner::readNumber() {
        while(this->isDigit(this->peek())) this->advance();

        // Handling fractional
        if(this->peek() == '.' && this->isDigit(this->peekNext())) {
            this->advance();
            while(this->isDigit(this->peek())) this->advance();
        }
            
        this->addToken(TokenType::NUMBER, 
                        std::stod(this->source.substr(this->start, (this->current)-(this->start))));
    }


    void Scanner::readIdentifier() {
        while(this->isAlphaNumeric(this->peek())) this->advance();

        std::string text = this->source.substr(this->start, this->current-this->start);
        if(Scanner::keywords.count(text) == 0) this->addToken(TokenType::IDENTIFIER);
        else this->addToken(Scanner::keywords[text]);
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
            case '!': addToken(match('=')?TokenType::BANG_EQUAL:TokenType::BANG); break;
            case '=': addToken(match('=')?TokenType::EQUAL_EQUAL:TokenType::EQUAL); break;
            case '<': addToken(match('=')?TokenType::LESS_EQUAL:TokenType::LESS); break;
            case '>': addToken(match('=')?TokenType::GREATER_EQUAL:TokenType::GREATER); break;
            case ';': addToken(TokenType::SEMICOLON); break;
            case '/': 
                if(match('/')) {
                    // A comment goes until the end of line
                    while(peek()!='\n' && !isAtEnd()) advance();
                } else {
                    addToken(TokenType::SLASH); 
                }
                break;

            case ' ':
            case '\r':
            case '\t':
                break;

            case '\n': this->line++; break;
            case '"': readString();
            

            default: 
                if(this->isDigit(c)) {
                    readNumber();
                } else if(this->isAlpha(c)) {
                    readIdentifier();
                } else {
                    error(line, "Unexpected character."); 
                }
                break;
        }
    }

    

};
