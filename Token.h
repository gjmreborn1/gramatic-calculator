#pragma once

#include <ostream>

const char NUMBER_KIND = '8';
const char PRINT_KIND = ';';
const char QUIT_KIND = 'k';
const char LET_KIND = 'L';
const char CONST_KIND = 'C';
const char NAME_KIND = 'a';
const char SQRT_KIND = 's';
const char POW_KIND = 'p';
const char HELP_KIND = 'h';

class Token {
public:
    char kind;
    double value;
    std::string name;

    Token(char kind = ' ', double value = 0.0);
    Token(char kind, const std::string &name);
    std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &os, const Token &t);
};
