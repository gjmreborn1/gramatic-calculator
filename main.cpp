#include <iostream>

/* For windows .exe CMD */
void keep_window_open();

void error(const char *msg) { throw std::runtime_error(msg); }

int main() {
    int lval = 0, rval = 0;
    char op;

    std::cout << "Wpisz wyrazenie (obslugujemy operatory +, -, * oraz /): ";
    std::cout << "Dodaj x, aby zakonczyc wyrazenie (np. 1+2*3x): ";

    std::cin >> lval;
    if (!std::cin) error("Na poczatku nie ma argumentu.");
    /* Read operator and right operand alternately */
    while (std::cin >> op) {
        if (op != 'x') {
            std::cin >> rval;
        }
        if (!std::cin) error("Nie ma drugiego argumentu wyrazenia.");

        switch (op) {
            case '+':
                lval += rval;
                break;
            case '-':
                lval -= rval;
                break;
            case '*':
                lval *= rval;
                break;
            case '/':
                if(rval == 0) {
                    error("Proba dzielenia przez 0!");
                }
                lval /= rval;
                break;
            case 'x':
                std::cout << "Wynik: " << lval << std::endl;
                keep_window_open();
                return 0;
        }
    }

    error("Nieprawidlowe wyrazenie.");
    return 1;
}

void keep_window_open() {
    while (std::cin.get() != '\n');

    std::cin.get();
}
