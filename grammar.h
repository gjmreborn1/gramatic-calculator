#pragma once

/*
 * Simple grammar of calculator expressions
 *
 * Statement:
 *      Expression
 *      Print
 *      Quit
 * Print:
 *      ;
 * Quit:
 *      k
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
 *      "-" Primary
 *      "+" Primary
 * Number:
 *      floating-point-literal
 *
 *
 * Data comes from std::cin through stream object ts (Token_stream).
 */

double expression();
double term();
double strong_primary();
double primary();
