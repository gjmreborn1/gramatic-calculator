#include "grammar.h"
#include "Token_stream.h"

#include <cmath>

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
 * Term:
 *      Primary
 *      Term "*" Primary
 *      Term "/" Primary
 *      Term "%" Primary
 */
double term() {
    double lval = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '*':
                lval *= primary();
                t = ts.get();
                break;
            case '/': {
                double rval = primary();
                if (rval == 0) throw std::runtime_error("Dzielenie przez zero.");

                lval /= rval;
                t = ts.get();
                break;
            }
            case '%': {
                double rval = primary();
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
 * Primary:
 *      Number
 *      "(" Expression ")"
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
        case NUMBER_KIND:
            return t.value;
        default:
            throw std::runtime_error("Oczekiwano czynnika.");
    }
}