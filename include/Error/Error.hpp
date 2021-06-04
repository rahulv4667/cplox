#ifndef __ERROR_H
#define __ERROR_H

#include <iostream>

namespace Lox {

    extern bool hadError;

    void report(int line, const std::string& where, const std::string& message);
    void error(int line, const std::string& message);
}

#endif // __ERROR_H