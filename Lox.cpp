#include <iostream>
#include <fstream>
#include <string>
#include <Scanner/Scanner.hpp>
#include <Error/Error.hpp>
#include <Parser/Expr.hpp>
#include "src/Parser/AstPrinter.cpp"

namespace Lox{

    void run(std::string program) {
        
        Lox::Scanner scanner(program);
        std::vector<Lox::Token> tokens = scanner.scanTokens();
        std::cout<<"Total number of tokens:"<<tokens.size()<<std::endl;
        for(Token token: tokens) {
            std::cout<<token<<std::endl;
        }

    }

    void runFile(char **argv) {
        std::string fileName(argv[0]);
        std::ifstream ifs(fileName, std::ifstream::binary);

        ifs.seekg(0, ifs.end);
        size_t fileLength = ifs.tellg();
        ifs.seekg(0, ifs.beg);

        char *fileContent = new char[fileLength];
        ifs.read(fileContent, fileLength);

        if(ifs) {
            std::cout<<"File read by interpreter successfully...\n";
        } else {
            std::cout<<"There was error while reading the file. Interpreter could read only "
                    <<ifs.gcount()<<" characters\n";
            exit(EXIT_FAILURE);
        }

        std::string program(fileContent);
        delete[] fileContent;

        run(program);
        if(Lox::hadError) exit(EXIT_FAILURE);
    }

    void runPrompt() {
        std::string command;
        std::cout<<"\t\t\tWelcome to CPLOX Repl\t\t\t\n";
        std::cout<<">>>\t";
        while(std::getline(std::cin, command)) {
            
            run(command);

            // reset coz we needn't close the prompt for one wrong command
            Lox::hadError = false;
            std::cout<<">>>\t";
        }
    }

};

int main(int argc, char **argv) {
    // if(argc > 2) {
    //     std::cout<<"Usage: ./cplox [script]"<<std::endl;
    //     exit(EXIT_FAILURE);
    // } else if(argc==2) {
    //     Lox::runFile(argv);
    // } else {
    //     Lox::runPrompt();
    // }

    Lox::Expr::Binary expression(
        Lox::Expr::Unary(Lox::Token(Lox::TokenType::MINUS, "-", {}, 1),
                        Lox::Expr::Literal(123)),
        Lox::Token(Lox::TokenType::STAR, "*", {}, 1),
        Lox::Expr::Grouping(Lox::Expr::Literal(45.67))
    );

    auto ast = Lox::AstPrinter<void>();
    ast.print(expression);
    std::cout<<(new Lox::AstPrinter())->print(&expression);
}