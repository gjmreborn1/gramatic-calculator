#pragma once

/*
 * Simple grammar of calculator expressions
 *
 * Expression:
 *      Term
 *      Expression "+" Term
 *      Expression "-" Term
 * Term:
 *      Primary
 *      Term "*" Primary
 *      Term "/" Primary
 *      Term "%" Primary
 * Primary:
 *      Number
 *      "(" Expression ")"
 * Number:
 *      floating-point-literal
 */

double expression();
double term();
double primary();
