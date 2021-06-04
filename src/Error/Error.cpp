#include <Error/Error.hpp>

namespace Lox {

    bool hadError = false;

    void report(int line, const std::string& where, const std::string& message) {
        std::cout<<"[Line "<<line<<"] Error "<<where<<" : "<<message<<"\n";
        Lox::hadError = true;
    }

    void error(int line, const std::string& message) {
        report(line, "", message);
    }
}