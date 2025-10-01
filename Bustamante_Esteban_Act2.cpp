#include <iostream>
#include <fstream>
using namespace std;

struct Nodo {
    string resn;
    int resid;
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

void Lee_pdb(Cola*& cola, string resn, int resid) {

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
    cout << "Residuo " << nuevo->resn << " ingresado.\n";
}

void Insertar_Cola(Cola*& cola, string resn) {

    cola->Cola_Llena();
    if(cola->BAND == true) {
        cout << "La cola esta llena.\n";
        return;
    }
    
    Nodo* nuevo = new Nodo();
    nuevo->resn = resn;
    nuevo->resid = cola->final->resid + 1;
    nuevo->Siguiente = nullptr;

    cola->final->Siguiente = nuevo;
    cola->final = nuevo;
    cout << "Residuo " << nuevo->resn << " ingresado.\n";
    
}

void Modificar_Cola(Cola*& cola, string resn, int resid) {

    cola->Cola_Vacia();
    if(cola->BAND == true) {
        cout << "La cola esta vacia.\n";
        return;
    }

    Nodo* aux = cola->frente;
    while(aux != nullptr) {
        if(aux->resid == resid) {
            aux->resn = resn;
            cout << "Residuo modificado.\n";
            return;
        }
        aux = aux->Siguiente;
    }
    cout << "Residuo no encontrado.\n";
}

void Eliminar_Residuo(Cola*& cola, int resid) {

    cola->Cola_Vacia();
    if(cola->BAND == true) {
        cout << "La cola esta vacia.\n";
        return;
    }

    Nodo* aux = cola->frente;
    Nodo* anterior = nullptr;
    while(aux != nullptr) {
        if(aux->resid == resid) {
            if(aux == cola->frente) {
                cola->frente = aux->Siguiente;
            } else {
                anterior->Siguiente = aux->Siguiente;

            }
            delete aux;
            cout << "Residuo eliminado.\n";
            return;
        }
        anterior = aux;
        aux = aux->Siguiente;
    }
    cout << "Residuo no encontrado.\n";
}

void Mostrar_Cola(Cola* cola) {
    cola->Cola_Vacia();
    if(cola->BAND == true) {
        cout << "La cola esta vacia.\n";
        return;
    }

    Nodo* aux = cola->frente;
    while(aux != nullptr) {
        cout << aux->resn << " | " << aux->resid << "\n";
        aux = aux->Siguiente;
    }
}

void Exportar_Cola(Cola* cola) {
    cola->Cola_Vacia();
    if(cola->BAND == true) {
        cout << "La cola esta vacia.\n";
        return;
    }

    string outputDot = "primary_structure.dot";
    string outputPng = "primary_structure.png";
    string conexiones = "";

    Nodo* aux = cola->frente;
    
    while(aux->Siguiente != nullptr) {
        conexiones += aux->resn + to_string(aux->resid) + "->";
        conexiones += aux->Siguiente->resn + to_string(aux->Siguiente->resid) + "\n";
        aux = aux->Siguiente;
    }

    //Borra el ultimo salto de linea
    if(!conexiones.empty()) {
        conexiones.pop_back();
    }

    //Abrir o Crear archivo .dot
    ofstream outfile;
    outfile.open(outputDot);
    if(!outfile.is_open()) {
        cout << "No se pudo crear el archivo " << outputDot << "\n";
        return;
    }

    //Escribir encabezado de Graphviz
    outfile << "digraph G {\n";
    outfile << "rankdir = LR;\n";
    outfile << "node [style=filled fillcolor=yellow];\n";

    //Escribir conexiones
    outfile << conexiones << "\n";
    
    //Cerrar Graphviz
    outfile << "}\n";
        outfile.close();

    cout << "+ Archivo graphviz generado: " << outputDot << "\n";

    //Ejecutar comando bash (Graphviz) para generar PNG
    string comando = "dot -Tpng " + outputDot + " -o " + outputPng;
    cout << comando << "\n";

    int resultado;
    resultado = system(comando.c_str());
    if (resultado == 0) {
        cout << "+ Imagen graphviz generada: " << outputPng << "\n";
    } else {
        cout << "+ [ERROR]: Revise que esté instalado el software graphviz. Revise el comando de generacion de imagen. Revise el archivo input para la generacion de imagen.\n";
    }
}

void menu(Cola*& cola) {
    string resn;
    int resid;
    int opcion;

    do {
        cout << "==== Menu Cola de Aminoacidos ====\n";
        cout << "1. Insertar Aminoacido\n";
        cout << "2. Modificar el resn de un residuo\n";
        cout << "3. Eliminar Aminoacido\n";
        cout << "4. Mostrar cola\n";
        cout << "5. Exportar cola\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
                cout << "Ingrese el resn: ";
                cin >> resn;
                Insertar_Cola(cola, resn);
                break;
            case 2:
                cout << "Ingrese el resid a modificar (numero): ";
                cin >> resid;
                cout << "Ingrese el nuevo resn: ";
                cin >> resn;
                Modificar_Cola(cola, resn, resid);
                break;
            case 3:
                cout << "Ingrese el resid a eliminar (numero): ";
                cin >> resid;
                Eliminar_Residuo(cola, resid);
                break;
            case 4:
                Mostrar_Cola(cola);
                break;
            case 5:
                Exportar_Cola(cola);
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                return;
            default:
                cout << "Opcion no valida.\n";
        }
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
        Lee_pdb(cola, resn, resid);
    }

    menu(cola);
    return 0;
}