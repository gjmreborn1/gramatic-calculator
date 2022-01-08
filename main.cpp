#include <iostream>

#include "grammar.h"
#include "Token_stream.h"

/* For windows .exe CMD */
void keep_window_open();

int main() {
    try {
        double val = 0;
        while(std::cin) {
            Token t = ts.get();

            if(t.kind == 'k') {
                // koniec
                break;
            } else if(t.kind == ';') {
                // print
                std::cout << "= " << val << std::endl;
            } else {
                ts.putback(t);
            }
            val = expression();
        }
        keep_window_open();
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        keep_window_open();
        return 1;
    } catch(...) {
        std::cerr << "Nieznany wyjatek.\n";
        keep_window_open();
        return 2;
    }

    return 0;
}

void keep_window_open() {
    while (std::cin.get() != '\n');

    std::cout << "Wprowadz cokolwiek (podtrzymuje okno): ";
    std::cin.get();
}
