#include <iostream>
using namespace std;

void verificar_par(int x) {
    int resto = 0;
    if (x % 2 != resto) {
        cout << "El número " << x << " no es par\n";
    } else {
        cout << "El número " << x << " es par\n";
    }
}

void determinar_longitud(char cadena[]) {
    int contador = 0;
    for(int i = 0; cadena[i] != '\0'; i++) {
        contador++;
    }
    cout << "El largo del string es " << contador << '\n';
}

void menu() {
    int opcion = 0;

    cout << "========== Menú ==========\n";
    cout << "1. Determinar paridad de un número\n";
    cout << "2. Determinar pares en los números del 1 al 10\n";
    cout << "3. Determinar longitud de un string\n";
    cout << "4. Salir\n";

    cin >> opcion;
    cin.ignore();

    if(opcion == 1) {
        int numero = 0;
        cout << "Ingrese el número:\n";
        cin >> numero;
        verificar_par(numero);
        menu();
    } else if(opcion == 2) {
        for(int i = 1; i <= 10; i++) {
            verificar_par(i);
        }
        menu();
    } else if(opcion == 3) {
        char cadena[100];
        cout << "Ingrese la cadena de texto (sin espacios)\n";
        cin >> cadena;
        determinar_longitud(cadena);
        menu();
    } else if(opcion == 4) {
        cout << "Saliendo...\n";
    } else {
        cout << "Ingrese una opción válida\n";
        menu();
    }
}

int main() {
    menu();

    return 0;
}