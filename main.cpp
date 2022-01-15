#include <iostream>

#include "grammar.h"
#include "Token_stream.h"

const std::string prompt = "> ";
const std::string result = "= ";

/* For windows .exe CMD */
void keep_window_open();

void calculate();

int main() {
    try {
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

void calculate() {
    while(std::cin) {
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

            ts.putback(t);
            std::cout << result << expression() << std::endl;
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
