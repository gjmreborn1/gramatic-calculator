#pragma once

#include "Token_stream.h"

/*
 * Simple grammar of calculator expressions
 *
 * Calculation:
 *      Statement
 *      Print
 *      Quit
 *      Help
 *      Calculation Statement
 * Statement:
 *      Expression
 *      Declaration
 * Declaration:
 *      "let" Name "=" Expression
 *      "const" Name "=" Expression
 * Print:
 *      ;
 * Quit:
 *      "koniec"
 * Help:
 *      "pomoc"
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
 *      Name "=" Expression
 *      "sqrt" "(" Expression ")"
 *      "pow" "(" Expression "," Expression ")"
 * Number:
 *      floating-point-literal
 *
 *
 * Data comes from data_source through stream object ts (Token_stream).
 */

double expression(Token_stream &ts);
double statement(Token_stream &ts);
double term(Token_stream &ts);
double strong_primary(Token_stream &ts);
double primary(Token_stream &ts);
