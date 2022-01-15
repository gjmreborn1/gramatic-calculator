#include "grammar.h"
#include "Token_stream.h"

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
        default:
            throw std::runtime_error("Oczekiwano czynnika, napotkano: " + t.to_string());
    }
}