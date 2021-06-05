#ifndef __LITERAL_TYPE_H
#define __LITERAL_TYPE_H
#include <variant>
#include <string>
#include <iostream>

namespace Lox {

    class LiteralType {
        public:
            std::variant<double, std::string> value;

            LiteralType();
            LiteralType(const std::string& value);
            LiteralType(double d);
            void operator=(const LiteralType& value);
            friend std::ostream& operator<<(std::ostream& os, const LiteralType& literal);
    };

};

#endif // __LITERAL_TYPE_H