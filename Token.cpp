#include "Token.h"

Token::Token(char kind, double value)
    : kind(kind), value(value) {
}

std::ostream &operator<<(std::ostream &os, const Token &t) {
    if(t.kind == NUMBER_KIND) {
        os << t.value;
    } else {
        os << t.kind;
    }

    return os;
}
