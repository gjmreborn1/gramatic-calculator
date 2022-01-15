#pragma once

#include "Token.h"

class Token_stream {
public:
    Token_stream();
    Token get();
    void putback(Token t);
    void ignore(char ch);
private:
    Token buffer;
    bool present;
};

extern Token_stream ts;
