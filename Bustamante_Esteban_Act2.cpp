#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;

struct PILA {
    int MAX = 0;
    int tope = 0;
    int arreglo[10];
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

        pila_llena(); //Actualiza valor de la bandera

        if(!band) { //Si no esta llena la pila, agrega.
            arreglo[tope] = dato;
            tope++;
        } else {
            cout << "Desbordamiento, pilla llena\n";
        }
    }

    void pop() {

        pila_vacia(); //Actualiza valor de la bandera

        if(!band) { //Si no esta vacia la pila, elimina.
            arreglo[tope - 1] = 0;
            tope--;
        } else {
            cout << "Subdesbordamiento, pila vacia\n";
        }
    }
};

PILA* removerContenedor(PILA tablero[], int ancho) {
    int contenedor = 0;
    cout << "Ingrese el indicador del contenedor a remover: ";
    cin >> contenedor;
    cin.ignore();

    for(int i = 0; i < ancho ; i++) { 
        if (tablero[i].arreglo[tablero[i].tope - 1] == contenedor) {
            tablero[i].pop();
            return tablero;
        }
    }
    cout << "El contenedor esta bloqueado o no existe\n";
    return tablero;
}

PILA* moverContenedor(PILA tablero[], int ancho) {
    int moveContenedor = 0;
    int ubicacion = 0;

    cout << "Ingrese el indicador del contenedor a mover: ";
    cin >> moveContenedor;

    for(int i = 0; i < ancho ; i++) { 
        if (tablero[i].arreglo[tablero[i].tope - 1] == moveContenedor) {
            cout << "Ingrese la pila donde dejará el contenedor: (1-" << ancho << "): ";
            cin >> ubicacion;
            cin.ignore();

            //Encuentra la pila donde dejar el contenedor
            tablero[ubicacion - 1].push(moveContenedor);
            if(tablero[ubicacion - 1].band) {
                return tablero;
            } else {
                tablero[i].pop();
                return tablero;
            }
        }
    }
    cout << "El contenedor esta bloqueado o no existe\n";
    return tablero;
}

PILA* mostrarTablero(PILA tablero[], int ancho) {
    for(int altura = tablero[0].MAX; altura > 0; altura--) {
        for(int pila = 0; pila < ancho; pila++) {
            if(altura <= tablero[pila].tope) {
                if(tablero[pila].arreglo[altura - 1] != 0) {
                cout << "|" << tablero[pila].arreglo[altura - 1] << "| ";
            } else {
                cout << "| | ";
            }   
            } else {
                cout << "| | ";
            }
        }
        cout << "\n";
    }
    return tablero;
}

int menu(PILA tablero[], int ancho) {
    int opcion = 0;

    while(true) {
        cout << "------ Menu ------\n";
        cout << "Remover un contenedor [1]\n";
        cout << "Mover un contenedor [2]\n";
        cout << "Ver tablero [3]\n";
        cout << "Salir [4]\n";
        cout << "------------------\n";

        cin >> opcion;

        if(opcion == 1) {
            removerContenedor(tablero, ancho);
        } else if(opcion == 2) {
            moverContenedor(tablero, ancho);
        } else if(opcion == 3) {
            mostrarTablero(tablero, ancho);
        } else if(opcion == 4) {
            cout << "Saliendo...\n";
            break;
        } else {
            cout << "Opcion invalida\n";    
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int ancho = 0;
    int largo = 0;

    for(int i = 1; i < argc; i++) {
        i == 1 ? ancho = atoi(argv[i]) : largo = atoi(argv[i]);
    }
    cout << "Se definió el ancho: " << ancho << " y el largo " << largo << endl;

    //Crea un tablero con pilas de tope aleatorio
    int indicador = 1;
    PILA tablero[ancho];
    srand(time(0));
    for(int i = 0; i < ancho; i++) {
        int numContenedores = 0;

        numContenedores = rand() % largo + 1;
        PILA pila;
        pila.MAX = largo;

        for(int i = 0; i < numContenedores; i++) {
            pila.push(indicador);
            indicador++;
        }
        tablero[i] = pila;
    }

    menu(tablero, ancho);
    return 0;
}