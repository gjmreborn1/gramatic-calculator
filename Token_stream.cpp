#include <iostream>
#include "Token_stream.h"

Token_stream ts;

Token_stream::Token_stream()
    : buffer({}), present(false) {
}

static const std::string declkey = "let";
static const std::string sqrtkey = "sqrt";
static const std::string powkey = "pow";

Token Token_stream::get() {
    if(present) {
        present = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;
    switch(ch) {
        case QUIT_KIND:
        case PRINT_KIND:
        case '(': case ')': case '+': case '-': case '*': case '/': case '%':
        case '{': case '}': case '!': case '=': case ',':
            return Token(ch);
        case '.':
        case '0': case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9': {
            std::cin.putback(ch);

            double val;
            std::cin >> val;
            return Token(NUMBER_KIND, val);
        }
        default:
            if(std::isalpha(ch)) {  // is start of some string token?
                std::string str_token;

                str_token += ch;
                while(std::cin.get(ch) && (std::isalpha(ch) || std::isdigit(ch) || ch == '_')) {
                    str_token += ch;
                }
                std::cin.putback(ch);

                if(str_token == declkey) {
                    return Token(LET_KIND);
                } else if(str_token == sqrtkey) {
                    return Token(SQRT_KIND);
                } else if(str_token == powkey) {
                    return Token(POW_KIND);
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
    while(std::cin >> curr) {
        if(curr == ch) {
            return;
        }
    }
}
