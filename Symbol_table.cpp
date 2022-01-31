#include "Symbol_table.h"

#include <iostream>

Symbol_table symtab;

double Symbol_table::get(const std::string &name) const {
    for(const Variable &var : var_table) {
        if(var.name == name) {
            return var.value;
        }
    }

    throw std::runtime_error("Pobieranie: niezdefiniowana zmienna: " + name);
}

void Symbol_table::set(const std::string &name, double val) {
    for(Variable &var : var_table) {
        if(var.name == name) {
            if(var.isConst) {
                throw std::runtime_error("Proba zmiany wartosci stalej");
            } else {
                var.value = val;
                return;
            }
        }
    }

    throw std::runtime_error("Ustawianie: niezdefiniowana zmienna: " + name);
}

bool Symbol_table::is_declared(const std::string &name) const {
    for(const Variable &var : var_table) {
        if(var.name == name) {
            return true;
        }
    }
    return false;
}

double Symbol_table::define(const std::string &name, double val, bool isConst) {
    if(is_declared(name)) {
        throw std::runtime_error(name + " - podwojna deklaracja.");
    }

    var_table.push_back(Variable {name, val, isConst});
    return val;
}

void Symbol_table::print() const {
    std::cout << "Zdefiniowane nazwy:\n";

    for(const Variable &var : var_table) {
        std::cout << "\t" << var.name << ": " << var.value;

        if(var.isConst) {
            std::cout << " (const)";
        }

        std::cout << std::endl;
    }
}
