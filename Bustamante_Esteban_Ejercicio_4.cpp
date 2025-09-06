#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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
    while(cur) { //Recorre la lista
        float pacienteIMC = 0;

        pacienteIMC = (cur->data.peso/(cur->data.altura * cur->data.altura)); //Calcula peso/altura²
        cout << "IMC de paciente " << cur->data.nombre << " es " << pacienteIMC << ".\n"; 
        cur = cur->next;
    }
}

void cargarCSV(Nodo*& head) {
    char encabezado[100];
    string linea;

    ifstream archivo("pacientes.csv");
    if(!archivo.is_open()) {
        cout << "No se pudo abrir el archivo\n";
        return;
    }
    
    archivo.getline(encabezado, 100); //Salta la primera linea

    while(getline(archivo, linea)) { //Lee cada linea
        string nombre, edad, peso, altura; //Atributos que guarda cada linea

        //Se asignan los valores
        stringstream ss(linea);
        getline(ss, nombre, ',');
        getline(ss, edad, ',');
        getline(ss, peso, ',');
        getline(ss, altura, ',');

        //Se convierten a los tipos de datos correctos
        int edad_int = stoi(edad);
        int peso_int = stoi(peso);
        float altura_float = stof(altura);

        //Se agrega el paciente a la lista
        insertarFinal(head, {nombre, edad_int, peso_int, altura_float});
    }
    archivo.close();
}

void menu(Nodo*& lista) {
    int opcion = 0;

    cout << "---- Menú ----\n";
    cout << "Agregar [1]\n";
    cout << "Remover en posicion [2]\n";
    cout << "Calcular promedios [3]\n";
    cout << "Calcular IMC [4]\n";
    cout << "Mostrar [5]\n";
    cout << "Cargar informacion desde CSV [6]\n";
    cout << "Salir [7]\n";

    cin >> opcion;
    cin.ignore();

    if(opcion == 1) {
        int opcion_2 = 0;
        string nombre;
        int edad;
        int peso;
        float altura;

        cout << "Ingrese el nombre del paciente: ";
        cin >> nombre;
        cin.ignore();
        cout << "Ingrese la edad del paciente: ";
        cin >> edad;
        cin.ignore();
        cout << "Ingrese el peso del paciente: ";
        cin >> peso;
        cin.ignore();
        cout << "Ingrese la altura del paciente: ";
        cin >> altura;
        cin.ignore();

        cout << "Insertar al Inicio [1]\n";
        cout << "Insertar al Final [2]\n";

        cin >> opcion_2;
        cin.ignore();

        if(opcion_2 == 1) {
            insertarInicio(lista, {nombre, edad, peso, altura});
        } else if(opcion_2 == 2) {
            insertarFinal(lista, {nombre, edad, peso, altura});
        }

        menu(lista);
    } else if(opcion == 2) {
        
        int pos;
        cout << "Ingrese la posicion del paciente:\n";
        cin >> pos;
        cin.ignore();

        eliminarEnPosicion(lista, pos);

        menu(lista);
    } else if(opcion == 3) {
        calculoPromedios(lista);
        menu(lista);
    } else if(opcion == 4) {
        calculoIMC(lista);
        menu(lista);
    } else if(opcion == 5) {
        mostrar(lista);
        menu(lista);
    } else if(opcion == 6) {
        cargarCSV(lista);
        menu(lista);
    } else if(opcion == 7) {
        cout << "Saliendo...\n";
    } else {
        cout << "Ingrese una opcion válida.\n";
        menu(lista);
    }

}

int main() {
    Nodo* lista = nullptr;
    menu(lista);
    return 0;
}