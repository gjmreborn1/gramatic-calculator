#include "Token.h"

Token::Token(char kind, double value)
    : kind(kind), value(value) {
}

std::string Token::to_string() const {
    if(kind == NUMBER_KIND) {
        return std::to_string(value);
    } else {
        return {kind};
    }
}

std::ostream &operator<<(std::ostream &os, const Token &t) {
    os << t.to_string();

    return os;
}
