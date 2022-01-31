#include "Variable.h"
#include "Token_stream.h"
#include "grammar.h"

#include <stdexcept>

std::vector<Variable> var_table;

double get_value(const std::string &name) {
    for(const Variable &var : var_table) {
        if(var.name == name) {
            return var.value;
        }
    }

    throw std::runtime_error("Pobieranie: niezdefiniowana zmienna: " + name);
}

void set_value(const std::string &name, double val) {
    for(Variable &var : var_table) {
        if(var.name == name) {
            var.value = val;
            return;
        }
    }

    throw std::runtime_error("Ustawianie: niezdefiniowana zmienna: " + name);
}

bool is_declared(const std::string &name) {
    for(const Variable &var : var_table) {
        if(var.name == name) {
            return true;
        }
    }
    return false;
}

double define_name(const std::string &name, double val) {
    if(is_declared(name)) {
        throw std::runtime_error(name + " - podwojna deklaracja.");
    }

    var_table.push_back(Variable {name, val});
    return val;
}

/*
 * Declaration:
 *      "let" Name "=" Expression
 */
double declaration() {
    // "let" is already consumed

    Token t = ts.get();
    if(t.kind != NAME_KIND) {
        throw std::runtime_error("Oczekiwano nazwy w deklaracji.");
    }
    std::string var_name = t.name;

    Token t2 = ts.get();
    if(t2.kind != '=') {
        throw std::runtime_error("Brak znaku = w deklaracji zmiennej " + var_name);
    }

    double val = expression();
    define_name(var_name, val);
    return val;
}
