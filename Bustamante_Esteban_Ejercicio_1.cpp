#include <iostream>
using namespace std;

struct PILA {
    int MAX = 5;
    int tope = 0;
    int arreglo[5];
    bool band = false;

    void pila_vacia() {
        if(tope == 0) {
            band = true; //La pila esta vacia
        } else {
            band = false; //La pila no esta vacia
        }
    }

    void pila_llena() {
        if(tope == MAX) {
            band = true; //La pila esta llena
        } else {
            band = false; //La pila no esta llena
        }
    }

    void push(int dato) {
        pila_llena();
        if(!band) {
            arreglo[tope] = dato;
            tope++;
        } else {
            cout << "Desbordamiento, pilla llena\n";
        }
    }

    void pop() {
        pila_vacia();
        if(!band) {
            arreglo[tope - 1] = 0;
            tope--;
        } else {
            cout << "Subdesbordamiento, pila vacia\n";
        }
    }

    void mostrar() {
        for(int i = 1; i <= tope; i++) {
            cout << "|" << arreglo[tope - i] << "|\n";
        }
    }
};

void menu(PILA pila) {
    int opcion = 0;

    cout << "------ Menu ------\n";
    cout << "Agregar/push: [1]\n";
    cout << "Remover/pop [2]\n";
    cout << "Ver pila [3]\n";
    cout << "Salir [4]\n";
    cout << "------------------\n";

    cin >> opcion;
    
    if(opcion == 1) {
        int dato = 0;
        cout << "Ingrese un dato: ";
        cin >> dato;
        cin.ignore();
        pila.push(dato);
        menu(pila);
    } else if(opcion == 2) {
        pila.pop();
        menu(pila);
    } else if(opcion == 3) {
        pila.mostrar();
        menu(pila);
    } else if(opcion == 4) {
        cout << "Saliendo...\n";
    } else {
        cout << "Opcion invalida\n";
        menu(pila);
    }
}

int main() {
    PILA pila;
    menu(pila);
    return 0;
}