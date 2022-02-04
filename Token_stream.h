#pragma once

#include <istream>

#include "Token.h"

class Token_stream {
public:
    Token_stream(std::istream &is);
    Token get();
    void putback(Token t);
    void ignore(char ch);
    operator bool() const;
private:
    std::istream &data_source;
    Token buffer;
    bool present;
};

extern Token_stream ts;
