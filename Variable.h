#pragma once

#include <string>
#include <vector>

class Variable {
public:
    std::string name;
    double value;
};

extern std::vector<Variable> var_table;

double get_value(const std::string &name);
void set_value(const std::string &name, double val);

bool is_declared(const std::string &name);
double define_name(const std::string &name, double val);

double declaration();
