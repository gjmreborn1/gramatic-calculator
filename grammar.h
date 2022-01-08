#pragma once

/*
 * Simple grammar of calculator expressions
 *
 * Expression:
 *      Term
 *      Expression "+" Term
 *      Expression "-" Term
 * Term:
 *      StrongPrimary
 *      Term "*" StrongPrimary
 *      Term "/" StrongPrimary
 *      Term "%" StrongPrimary
 * StrongPrimary:
 *      Primary
 *      StrongPrimary "!"
 * Primary:
 *      Number
 *      "(" Expression ")"
 *      "{" Expression "}"
 * Number:
 *      floating-point-literal
 */

double expression();
double term();
double strong_primary();
double primary();
