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
double expression(Token_stream &ts) {
    double lval = term(ts);
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '+':
                lval += term(ts);
                t = ts.get();
                break;
            case '-':
                lval -= term(ts);
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
double statement(Token_stream &ts) {
    Token t = ts.get();
    switch(t.kind) {
        case LET_KIND:
            return declaration(ts, false);
        case CONST_KIND:
            return declaration(ts, true);
        default:
            ts.putback(t);
            return expression(ts);
    }
}

/*
 * Term:
 *      StrongPrimary
 *      Term "*" StrongPrimary
 *      Term "/" StrongPrimary
 *      Term "%" StrongPrimary
 */
double term(Token_stream &ts) {
    double lval = strong_primary(ts);
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '*':
                lval *= strong_primary(ts);
                t = ts.get();
                break;
            case '/': {
                double rval = strong_primary(ts);
                if (rval == 0) throw std::runtime_error("Dzielenie przez zero.");

                lval /= rval;
                t = ts.get();
                break;
            }
            case '%': {
                double rval = strong_primary(ts);
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
double strong_primary(Token_stream &ts) {
    double lval = primary(ts);
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
double primary(Token_stream &ts) {
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            double expr = expression(ts);

            t = ts.get();
            if (t.kind != ')') throw std::runtime_error("Oczekiwano ').");

            return expr;
        }
        case '{': {
            double expr = expression(ts);

            t = ts.get();
            if (t.kind != '}') throw std::runtime_error("Oczekiwano '}'.");

            return expr;
        }
        case '-':
            return -primary(ts);
        case '+':
            return +primary(ts);
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
            double val = expression(ts);
            symtab.set(var_name, val);
            return val;
        }
        case SQRT_KIND: {
            t = ts.get();
            if (t.kind != '(') throw std::runtime_error("Oczekiwano '('.");

            double expr = expression(ts);

            t = ts.get();
            if (t.kind != ')') throw std::runtime_error("Oczekiwano ')'.");

            if(expr < 0) throw std::runtime_error("Argument funkcji pierwiastka kwadratowego jest ujemny.");

            return std::sqrt(expr);
        }
        case POW_KIND: {
            t = ts.get();
            if (t.kind != '(') throw std::runtime_error("Oczekiwano '('.");

            double expr = expression(ts);

            t = ts.get();
            if (t.kind != ',') throw std::runtime_error("Oczekiwano ','.");

            double expr2 = expression(ts);

            t = ts.get();
            if (t.kind != ')') throw std::runtime_error("Oczekiwano ')'.");

            return std::pow(expr, static_cast<int>(expr2));
        }
        default:
            throw std::runtime_error("Oczekiwano czynnika, napotkano: " + t.to_string());
    }
}