#include <iostream>
#include "Token_stream.h"

Token_stream ts;

Token_stream::Token_stream()
    : buffer({}), present(false) {
}

Token Token_stream::get() {
    if(present) {
        present = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;
    switch(ch) {
        case ';':
        case 'k':
        case '(': case ')': case '+': case '-': case '*': case '/': case '%':
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
            throw std::runtime_error("Nieprawidlowy token.");
    }
}

void Token_stream::putback(Token t) {
    if(present) {
        throw std::runtime_error("Wywolanie funkcji putback(), gdy bufor jest juz pelny.");
    }

    buffer = t;
    present = true;
}
