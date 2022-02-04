#include <iostream>
#include "Token_stream.h"

Token_stream ts {std::cin};

Token_stream::Token_stream(std::istream &is)
    : data_source(is), buffer({}), present(false) {
}

static const std::string declkey = "let";
static const std::string constkey = "const";
static const std::string sqrtkey = "sqrt";
static const std::string powkey = "pow";
static const std::string quitkey = "koniec";
static const std::string helpkey = "pomoc";

Token Token_stream::get() {
    if(present) {
        present = false;
        return buffer;
    }

    char ch;
    data_source >> ch;
    switch(ch) {
        case PRINT_KIND:
        case '(': case ')': case '+': case '-': case '*': case '/': case '%':
        case '{': case '}': case '!': case '=': case ',':
            return Token(ch);
        case '.':
        case '0': case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9': {
            data_source.putback(ch);

            double val;
            data_source >> val;
            return Token(NUMBER_KIND, val);
        }
        default:
            if(std::isalpha(ch)) {  // is start of some string token?
                std::string str_token;

                str_token += ch;
                while(data_source.get(ch) && (std::isalpha(ch) || std::isdigit(ch) || ch == '_')) {
                    str_token += ch;
                }
                data_source.putback(ch);

                if(str_token == declkey) {
                    return Token(LET_KIND);
                } else if(str_token == constkey) {
                    return Token(CONST_KIND);
                } else if(str_token == sqrtkey) {
                    return Token(SQRT_KIND);
                } else if(str_token == powkey) {
                    return Token(POW_KIND);
                } else if(str_token == helpkey) {
                    return Token(HELP_KIND);
                } else if(str_token == quitkey) {
                    return Token(QUIT_KIND);
                } else {
                    return Token(NAME_KIND, str_token);
                }
            }
            throw std::runtime_error("Nieprawidlowy token: " + std::string(1, ch));
    }
}

void Token_stream::putback(Token t) {
    if(present) {
        throw std::runtime_error("Wywolanie funkcji putback(), gdy bufor jest juz pelny.");
    }

    buffer = t;
    present = true;
}

void Token_stream::ignore(char ch) {
    if(present && buffer.kind == ch) {
        present = false;
        return;
    }

    present = false;
    char curr;
    while(data_source >> curr) {
        if(curr == ch) {
            return;
        }
    }
}

Token_stream::operator bool() const {
    return (bool) data_source;
}
