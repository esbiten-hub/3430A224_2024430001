#include <iostream>
#include <string>
using namespace std;

struct PACIENTE {   //Estructura Paciente
    string nombre;
    int edad;
    int peso;
    float altura;
    PACIENTE *next;
};

struct Nodo {
    PACIENTE data; //Instancia del paciente
    Nodo* next; //Puntero tipo Nodo
};

Nodo* crearNodo(const PACIENTE& p) {
    Nodo* n = new Nodo;
    n->data = p;
    n->next = nullptr;
    return n;
}

void insertarFinal(Nodo*& head, const PACIENTE& p) {
    Nodo* n = crearNodo(p);

    if(!head) {
        head = n;
        return;
    }
    Nodo* cur = head;
    while(cur->next) cur = cur->next; //mientras tenga referencia al siguiente
    cur->next = n; //se enlaza al ultimo cur
}

void insertarInicio(Nodo*& head, const PACIENTE& p) {
    Nodo* n = crearNodo(p);

    if(!head) {
        head = n;
        return;
    }
    n->next = head; //Enlaza el "head" al next del nuevo nodo
    head = n; //Ahora head es el nuevo nodo
}

void mostrar(const Nodo* head) {
    cout << "\n==== Inventario de Pacientes ====\n";
    const Nodo* cur = head;
    int pos = 0;
    while(cur) {
        cout << "#Pos " << pos << '\n';
        cout << "Nombre: " << cur->data.nombre << '\n';
        cout << "Edad: " << cur->data.edad << '\n';
        cout << "Peso: " << cur->data.peso << '\n';
        cout << "Altura: " << cur->data.altura << '\n';
        cout << "+-----------------------+\n";
        cur = cur->next;
        ++pos;
    }
    if(pos == 0) cout << "(lista vacia)\n";
}

bool eliminarEnPosicion(Nodo*& head, int pos) {
    if(!head || pos < 0) return false; //Si no hay cabeza o posicion invalida
    //En caso de eliminar cabeza
    if(pos == 0) {
        Nodo* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }
    //Para otra posicion
    Nodo* cur = head;
    for(int i = 0; cur && i < pos - 1; i++) {
        cur = cur->next;
    }
    //Posicion invalida o no existe siguiente
    if(!cur || !cur->next) return false;
    //Reemplazar y borrar
    Nodo* borrar = cur->next;
    cur->next = borrar->next;
    delete borrar;
    return true;
}

void liberarLista(Nodo*& head) {
    while(head) {
        Nodo* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    Nodo* lista = nullptr;
    //Inserciones de ejemplo
    insertarFinal(lista, {"Esteban", 19, 73, 1.78});
    insertarFinal(lista, {"Benjamin", 19, 70, 1.80});
    insertarFinal(lista, {"Hector", 21, 100, 1.70});
    //Mostrar lista
    mostrar(lista);
    //Eliminar un paciente
    !eliminarEnPosicion(lista, 1) ? cout << "Posicion invalida\n" : cout << "Paciente eliminado\n";
    //Agregar al inicio
    insertarInicio(lista, {"Catalina", 25, 68, 1.74});

    //Mostrar inventario final
    mostrar(lista);
    //Limpieza final
    liberarLista(lista);
    return 0;
}