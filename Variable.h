#pragma once

#include "Token_stream.h"

#include <string>

class Variable {
public:
    std::string name;
    double value;
    bool isConst;
};

double declaration(Token_stream &ts, bool isConst);
