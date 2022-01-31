#pragma once

/*
 * Simple grammar of calculator expressions
 *
 * Calculation:
 *      Statement
 *      Print
 *      Quit
 *      Calculation Statement
 * Statement:
 *      Expression
 *      Declaration
 * Declaration:
 *      "let" Name "=" Expression
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
 *      Name
 *      "sqrt" "(" Expression ")"
 *      "pow" "(" Expression "," Expression ")"
 * Number:
 *      floating-point-literal
 *
 *
 * Data comes from std::cin through stream object ts (Token_stream).
 */

double expression();
double statement();
double term();
double strong_primary();
double primary();
