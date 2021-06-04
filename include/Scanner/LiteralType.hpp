#ifndef __LITERAL_TYPE_H
#define __LITERAL_TYPE_H
#include <variant>
#include <string>
#include <iostream>

namespace Lox {

    class LiteralType {
        public:
            std::variant<double, std::string> value;
            void operator=(const LiteralType& value);
            friend std::ostream& operator<<(std::ostream& os, const LiteralType& literal);
    };

};

#endif // __LITERAL_TYPE_H