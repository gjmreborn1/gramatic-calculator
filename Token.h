#pragma once

#include <ostream>

const char NUMBER_KIND = '8';

class Token {
public:
    char kind;
    double value;

    Token(char kind = ' ', double value = 0.0);
    std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &os, const Token &t);
};
