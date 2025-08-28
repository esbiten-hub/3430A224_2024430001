#include <iostream>
using namespace std;

double square(double x) { //Eleva al cuadrado el número dado
    return x * x;
}

void print_square(double x) { // Escribe el resultado en la terminal
    cout << "El cuadrado de " << x << " is " << square(x) << '\n';
}

int main() { // Inicio del programa C++
    print_square(1.234);
    print_square(5.555);

    return 0;
}