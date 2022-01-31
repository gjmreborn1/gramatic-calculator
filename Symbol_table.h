#pragma once

#include <vector>

#include "Variable.h"

class Symbol_table {
private:
    std::vector<Variable> var_table;
public:
    double get(const std::string &name) const;
    void set(const std::string &name, double val);

    bool is_declared(const std::string &name) const;
    double define(const std::string &name, double val, bool isConst);

    void print() const;
};

extern Symbol_table symtab;
