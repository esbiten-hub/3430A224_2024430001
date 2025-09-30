#include <iostream>
#include <fstream>
using namespace std;

struct Nodo {
    string resn;
    string resid;
    Nodo* Siguiente;
};

struct Cola {
    Nodo* frente;
    Nodo* final;
    bool BAND;

    bool Cola_Vacia() {
        if(frente == nullptr) {
            BAND = true;
        } else {
            BAND = false;
        }
        return BAND;
    }
    bool Cola_Llena() {
        BAND = false; //lista dinamica no se llena
        return BAND;
    }
};

void Insertar_Cola(Cola*& cola, string resn, int resid) {

    cola->Cola_Llena();
    if(cola->BAND == true) {
        cout << "La cola esta llena.\n";
        return;
    }

    Nodo* nuevo = new Nodo();
    nuevo->resn = resn;
    nuevo->resid = resid;
    nuevo->Siguiente = nullptr;

    cola->Cola_Vacia();
    if(cola->BAND == true) {
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        cola->final->Siguiente = nuevo;
        cola->final = nuevo;
    }
    cout << "Residuo " << nuevo->resn << "ingresado.\n";
}

void menu() {
    int opcion;

    do {
        cout << "==== Menu Cola de Aminoacidos ====\n";
        cout << "1. Insertar Aminoacido\n";
        cout << "2. Modificar el resn de un residuo\n";
        cout << "3. Eliminar Aminoacido\n";
        cout << "4. Mostrar Cola\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
    } while(opcion != 5);
}

int main() {
    //Inicializa la cola
    Cola* cola = new Cola();
    cola->frente = nullptr;
    cola->final = nullptr;

    ifstream archivo("3W9R_Resids_ChainA_Format_Uniq.pdb");
    if(!archivo.is_open()) {
        cout << "Error al abrir el archivo.\n";
        return 0;
    }

    string linea;
    while(getline(archivo, linea)) {
        string resn = linea.substr(0, 3);
        int resid = stoi(linea.substr(4, 7));
        Insertar_Cola(cola, resn, resid);



    }


    




    return 0;
}