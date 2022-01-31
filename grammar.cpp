#include "grammar.h"
#include "Variable.h"
#include "Token_stream.h"
#include "Symbol_table.h"

#include <cmath>

static double factorial(double n_d) {
    long n = static_cast<long>(n_d);

    long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    return result;
}

/*
 * Expression:
 *      Term
 *      Expression "+" Term
 *      Expression "-" Term
 */
double expression() {
    double lval = term();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '+':
                lval += term();
                t = ts.get();
                break;
            case '-':
                lval -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return lval;
        }
    }
}

/*
 * Statement:
 *      Expression
 *      Declaration
 */
double statement() {
    Token t = ts.get();
    switch(t.kind) {
        case LET_KIND:
            return declaration(false);
        case CONST_KIND:
            return declaration(true);
        default:
            ts.putback(t);
            return expression();
    }
}

/*
 * Term:
 *      StrongPrimary
 *      Term "*" StrongPrimary
 *      Term "/" StrongPrimary
 *      Term "%" StrongPrimary
 */
double term() {
    double lval = strong_primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '*':
                lval *= strong_primary();
                t = ts.get();
                break;
            case '/': {
                double rval = strong_primary();
                if (rval == 0) throw std::runtime_error("Dzielenie przez zero.");

                lval /= rval;
                t = ts.get();
                break;
            }
            case '%': {
                double rval = strong_primary();
                if (rval == 0) throw std::runtime_error("Dzielenie przez zero.");

                lval = fmod(lval, rval);
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return lval;
        }
    }
}

/*
 * StrongPrimary:
 *      Primary
 *      StrongPrimary "!"
 */
double strong_primary() {
    double lval = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '!':
                lval = factorial(lval);
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return lval;
        }
    }
}

/*
 * Primary:
 *      Number
 *      "(" Expression ")"
 *      "{" Expression "}"
 *      "-" Primary
 *      "+" Primary
 *      Name
 *      Name "=" Expression
 *      "sqrt" "(" Expression ")"
 *      "pow" "(" Expression "," Expression ")"
 */
double primary() {
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            double expr = expression();

            t = ts.get();
            if (t.kind != ')') throw std::runtime_error("Oczekiwano ').");

            return expr;
        }
        case '{': {
            double expr = expression();

            t = ts.get();
            if (t.kind != '}') throw std::runtime_error("Oczekiwano '}'.");

            return expr;
        }
        case '-':
            return -primary();
        case '+':
            return +primary();
        case NUMBER_KIND:
            return t.value;
        case NAME_KIND: {
            std::string var_name = t.name;

            t = ts.get();
            if(t.kind != '=') {
                ts.putback(t);
                return symtab.get(var_name);   // getting the variable value
            }

            // variable assignment
            double val = expression();
            symtab.set(var_name, val);
            return val;
        }
        case SQRT_KIND: {
            t = ts.get();
            if (t.kind != '(') throw std::runtime_error("Oczekiwano '('.");

            double expr = expression();

            t = ts.get();
            if (t.kind != ')') throw std::runtime_error("Oczekiwano ')'.");

            if(expr < 0) throw std::runtime_error("Argument funkcji pierwiastka kwadratowego jest ujemny.");

            return std::sqrt(expr);
        }
        case POW_KIND: {
            t = ts.get();
            if (t.kind != '(') throw std::runtime_error("Oczekiwano '('.");

            double expr = expression();

            t = ts.get();
            if (t.kind != ',') throw std::runtime_error("Oczekiwano ','.");

            double expr2 = expression();

            t = ts.get();
            if (t.kind != ')') throw std::runtime_error("Oczekiwano ')'.");

            return std::pow(expr, static_cast<int>(expr2));
        }
        default:
            throw std::runtime_error("Oczekiwano czynnika, napotkano: " + t.to_string());
    }
}