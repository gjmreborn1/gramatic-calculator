#pragma once

#include "Token.h"

class Token_stream {
public:
    Token_stream();
    Token get();
    void putback(Token t);
private:
    Token buffer;
    bool present;
};

extern Token_stream ts;
