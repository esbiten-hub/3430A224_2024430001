#include <iostream>
using namespace std;

struct Nodo {
    string Nombre;
    string Carrera;
    float Promedio;
    Nodo* Siguiente;
};

struct Cola {
    Nodo* frente;
    Nodo* final;
    bool BAND;

    bool Cola_Vacia() {
        if(frente == nullptr) { //si no hay primer elemento -> true
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

void Insertar_Cola(Cola*& cola) {
    string nombre, carrera;
    float promedio;

    cola->Cola_Llena(); //verifica si la cola esta llena
    if(cola->BAND == true) {
        cout << "La cola esta llena.\n";
        return;
    }

    //Crea nodo
    Nodo* nuevo = new Nodo();
    cout << "Ingrese el nombre del estudiante: ";
    cin >> nombre;
    cout << "Ingrese la carrera del estudiante: ";
    cin >> carrera;
    cout << "Ingrese el promedio del estudiante: ";
    cin >> promedio;    
    nuevo->Nombre = nombre;
    nuevo->Carrera = carrera;
    nuevo->Promedio = promedio;
    nuevo->Siguiente = nullptr;

    cola->Cola_Vacia();
    if(cola->BAND == true) { //en caso de ser el primer elemento ingresado
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        cola->final->Siguiente = nuevo; //enlaza al final
        cola->final = nuevo;
    }
    cout << "Estudiante " << nuevo->Nombre << "ingresado.\n";
}

void Eliminar_Cola(Cola*& cola) {
    cola->Cola_Vacia();
    if(cola->BAND == true) {
        cout << "La cola esta vacia.\n";
        return;
    }

    //Elimina el primero de la cola
    Nodo* aux = cola->frente;
    cola->frente = aux->Siguiente;
    cout << "Estudiante " << aux->Nombre << " eliminado.\n";
    delete aux;
}

void Mostrar_Cola(Cola* cola) {
    cola->Cola_Vacia();
    if(cola->BAND == true) {
        cout << "La cola esta vacia.\n";
        return;
    }

    //Recorre la cola con el nodo aux hasta que llegue al final
    Nodo* aux = cola->frente;
    while(aux != nullptr) {
        cout << aux->Nombre << " | " << aux->Carrera << " | Promedio: " << aux->Promedio << endl;
        aux = aux->Siguiente;
    }
}

int main() {
    //Inicializa la Cola 
    Cola* cola = new Cola();
    cola->frente = nullptr;
    cola->final = nullptr;

    int opcion;

    do {
        cout << "==== Menu Cola de Estudiantes ====\n";
        cout << "1. Insertar Estudiante\n";
        cout << "2. Eliminar Estudiante\n";
        cout << "3. Mostrar Cola\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                Insertar_Cola(cola); //Encolar estudiante
                break;
            case 2:
                Eliminar_Cola(cola); //Desencolar estudiante            
                break;
            case 3:
                Mostrar_Cola(cola); //Mostrar cola
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    } while (opcion != 4);
    return 0;
}