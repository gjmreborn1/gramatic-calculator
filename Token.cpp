#include "Token.h"

Token::Token(char kind, double value)
    : kind(kind), value(value) {
}

Token::Token(char kind, const std::string &name)
    : kind(kind), name(name) {
}

std::string Token::to_string() const {
    if(kind == NUMBER_KIND) {
        return std::to_string(value);
    } else if(kind == NAME_KIND) {
        return name;
    } else {
        return std::string(1, kind);
    }
}

std::ostream &operator<<(std::ostream &os, const Token &t) {
    os << t.to_string();

    return os;
}
