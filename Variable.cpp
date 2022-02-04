#include "Variable.h"
#include "Token_stream.h"
#include "grammar.h"
#include "Symbol_table.h"

#include <stdexcept>

/*
 * Declaration:
 *      "let" Name "=" Expression
 *      "const" Name "=" Expression
 */
double declaration(Token_stream &ts, bool isConst) {
    // "let" / "const" is already consumed

    Token t = ts.get();
    if(t.kind != NAME_KIND) {
        throw std::runtime_error("Oczekiwano nazwy w deklaracji.");
    }
    std::string var_name = t.name;

    Token t2 = ts.get();
    if(t2.kind != '=') {
        throw std::runtime_error("Brak znaku = w deklaracji zmiennej " + var_name);
    }

    double val = expression(ts);
    symtab.define(var_name, val, isConst);
    return val;
}
