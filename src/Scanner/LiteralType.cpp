#include <Scanner/LiteralType.hpp>
#include <sstream>
namespace Lox {

    LiteralType::LiteralType() {}
    LiteralType::LiteralType(const std::string& value): value(value) {}
    LiteralType::LiteralType(double d): value(d) {}

    void LiteralType::operator=(const LiteralType& literal) {
        this->value = literal.value;
    }

    std::ostream& operator<<(std::ostream& os, const LiteralType& literal) {
        // switch(literal.value.index()) {
        //     case 0: os<<(std::get<double>(literal.value));
        //             break;
                
        //     case 1: os<<(std::get<std::string>(literal.value));
        //             break;
        // }

        // Source for understanding below code: 
        // https://arne-mertz.de/2018/05/modern-c-features-stdvariant-and-stdvisit/
        std::visit([&os](auto const& e){
            os<<e;
        }, literal.value);

        return os;
    }

    bool LiteralType::isNull() {
        return (this->value).valueless_by_exception();
    }

    std::string LiteralType::toString() {
        std::stringstream ss;
        ss<<(*this); // works coz we have overloaded operator<<
        return ss.str();
    }

};