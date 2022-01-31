#pragma once

#include <string>

class Variable {
public:
    std::string name;
    double value;
    bool isConst;
};

double declaration(bool isConst);
