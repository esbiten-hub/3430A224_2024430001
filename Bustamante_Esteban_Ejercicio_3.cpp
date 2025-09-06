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
    n->next = head; //Enlaza el "head" al next del nodo recien creado
    head = n; //Ahora head pasa a ser el nodo recien creado
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

void calculoPromedios(const Nodo* head) {
    const Nodo* cur = head;
    int suma_edad = 0;
    int suma_peso = 0;
    int total_pacientes = 0;
    float promedio_edad = 0;
    float promedio_peso = 0;

    while(cur) { //Recorre la lista sumando edades y pesos
        suma_edad += cur->data.edad;
        suma_peso += cur->data.peso;
        total_pacientes++; //Cuenta la cantidad de pacientes
        cur = cur->next;
    }
    if(total_pacientes > 0) {
        //Calcula los promedios
        promedio_edad = suma_edad/total_pacientes;
        promedio_peso = suma_peso/total_pacientes;

        cout << "El promedio de edad de los pacientes es: " << promedio_edad << ".\n";
        cout << "El promedio de peso de los pacientes es: " << promedio_peso << ".\n";
    }
}

void calculoIMC(const Nodo* head) {
    const Nodo* cur = head;
    while(cur) {
        float pacienteIMC = 0;
        pacienteIMC = (cur->data.peso/(cur->data.altura * cur->data.altura));
        cout << "IMC de paciente " << cur->data.nombre << " es " << pacienteIMC << ".\n"; 
        cur = cur->next;
    }
}

int main() {
    Nodo* lista = nullptr;
    //Inserciones de ejemplo
    insertarInicio(lista, {"Tomas", 20, 67, 1.75});
    insertarFinal(lista, {"Esteban", 19, 73, 1.78});
    insertarFinal(lista, {"Benjamin", 19, 70, 1.80});
    insertarFinal(lista, {"Hector", 21, 100, 1.70});
    //Mostrar lista
    mostrar(lista);
    
    //Promedios
    calculoPromedios(lista);
    //IMC
    calculoIMC(lista);
    
    //Limpieza final
    liberarLista(lista);
    return 0;
}