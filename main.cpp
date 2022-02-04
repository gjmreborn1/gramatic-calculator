#include <iostream>

#include "grammar.h"
#include "Token_stream.h"
#include "Symbol_table.h"

const std::string prompt = "> ";
const std::string result = "= ";

/* For windows .exe CMD */
void keep_window_open();

void calculate();

int main() {
    try {
        symtab.define("pi", 3.1415926535, true);
        symtab.define("e", 2.7182818284, true);

        calculate();

        keep_window_open();
        return 0;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        keep_window_open();
        return 1;
    } catch(...) {
        std::cerr << "Nieznany wyjatek.\n";
        keep_window_open();
        return 2;
    }
}

void clean_up() {
    ts.ignore(PRINT_KIND);
}

void display_help() {
    std::cout << "Kalkulator. Dostepne polecenia: +, -, *, /, %, !, sqrt(expr), pow(a, b)" << std::endl;
    std::cout << "Dzialaja nawiasy () i {}." << std::endl;
    std::cout << "pomoc - pomoc" << std::endl;
    std::cout << "koniec - zakoncz program" << std::endl;
    std::cout << "; - wyswietl wynik biezacego wyrazenia" << std::endl;
    std::cout << "Zmienne definiujemy operatorem let, a stale operatorem const." << std::endl;

    symtab.print();
}

void calculate() {
    while(ts) {
        try {
            std::cout << prompt;
            Token t = ts.get();

            // skip all PRINT_KIND
            while (t.kind == PRINT_KIND) {
                t = ts.get();
            }

            if (t.kind == QUIT_KIND) {
                return;
            }

            if(t.kind == HELP_KIND) {
                display_help();
            } else {
                ts.putback(t);
                std::cout << result << statement() << std::endl;
            }
        } catch(std::exception &e) {
            std::cerr << e.what() << std::endl;
            clean_up();
        }
    }
}

void keep_window_open() {
    while (std::cin.get() != '\n');

    std::cout << "Wprowadz cokolwiek (podtrzymuje okno): ";
    std::cin.get();
}
