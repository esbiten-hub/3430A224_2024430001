#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Estructura nodo
struct NODO{
    NODO* left;
    NODO* right;
    int FE;
    string GO;
    double score;
    string function;
};

void insercionBalanceado(NODO** nodocabeza, bool* BO, string GO, double score, string function) {
    NODO* raiz = *nodocabeza; //Hace referenia al nodo actual
    NODO* nodo1;
    NODO* nodo2;

    if(raiz != nullptr) {
        if(score < raiz->score) {
            //Si score es menor, revisa subarbol izquierdo
            insercionBalanceado(&(raiz->left), BO, GO, score, function);
            if(*BO) { //Si el árbol creció hacia la izquierda
                switch (raiz->FE) { //Actuar según factor de equilibrio
                    case 1:
                        //En el subarbol izquierdo, con inclinación hacia la derecha
                        //al inrgresar un nodo por la izquierda, el factor de equilibrio se vuelve 0 (equilibrado)
                        raiz->FE = 0;
                        *BO = false; //No aumenta nivel del arbol
                        break;
                    case 0:
                        //En el subarbol izquierdo, equilibrado.
                        //Agregar nodo por la izquierda implica una inclinación hacia la izquierda (FE = -1)
                        raiz->FE = -1;
                        break;
                    case -1:
                        //En el subarbol izquierdo, con inclinación hacia la izquierda
                        //al inrgresar un nodo por la izquierda, la inclinacion -1 se vuelve -2.
                        //Se debe balancear el árbol -> Rotación II (Izquierda - Izquierda).
                        nodo1 = raiz->left;
                        if(nodo1-> FE <= 0) {
                            //Si el hijo izquierdo tiene FE <= 0, rotación II
                            raiz->left = nodo1->right;
                            nodo1->right = raiz;
                            raiz ->FE = 0;
                            raiz = nodo1;
                        } else {
                            //Rotacion ID (Izquierda - Derecha)
                            nodo2 = nodo1->right;
                            raiz->left = nodo2->right;
                            nodo2->right = raiz;
                            nodo1->right = nodo2->left;
                            nodo2->left = nodo1;
                            
                            //Actualiza los factores de equilibrio
                            if(nodo2->FE == -1)
                                raiz->FE = 1;
                            else
                                raiz->FE = 0;
                            
                            if(nodo2->FE == 1)
                                nodo1->FE = -1;
                            else
                                nodo1->FE = 0;

                            //Por definicion de la rotacion ID
                            //nodo 2 es el nuevo raiz
                            raiz = nodo2;
                        }

                        //Tanto la rotación II como ID dejan el factor de equilibrio en 0
                        raiz->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else if(score > raiz->score) {
            //Si score es mayor, revisa subarbol derecho
            insercionBalanceado(&(raiz->right), BO, GO, score, function);
            if(*BO) {
                switch (raiz->FE) {
                    case -1:
                        raiz->FE = 0;
                        *BO = false;
                        break;
                    case 0:
                        raiz->FE = 1;
                        break;
                    case 1:
                        nodo1 = raiz->right;
                        if(nodo1->FE >= 0) { //Rotacion DD
                            raiz->right = nodo1->left;
                            nodo1->left = raiz;
                            raiz->FE = 0;
                            raiz = nodo1;
                        } else { //Rotacion DI
                            nodo2 = nodo1->left;
                            raiz->right = nodo2->left;
                            nodo2->left = raiz;
                            nodo1->left = nodo2->right;
                            nodo2->right = nodo1;

                            if(nodo2->FE == 1)
                                raiz->FE = -1;
                            else
                                raiz->FE = 0;

                            if(nodo2->FE == -1)
                                nodo1->FE = 1;
                            else
                                nodo1->FE = 0;
                            raiz = nodo2;
                        }
                        raiz->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else {
            cout << "El elemento ya se encuentra en el árbol\n";
        }
    } else {
        //Inserta nodo en una hoja vacía
        raiz = new NODO();
        raiz->GO = GO;
        raiz->score = score;
        raiz->function = function;
        raiz->left = nullptr;
        raiz->right = nullptr;
        raiz->FE = 0;

        //Se realizó una inserción
        *BO = true;
    }

    *nodocabeza = raiz; //Actualiza la raíz del subárbol
}

void PreOrden(NODO* nodo, ofstream& fp) {
    if(nodo != nullptr) {
        //Si tiene hijo en la izquierda lo escribe
        if(nodo->left != nullptr) {
            //Escribe la conexion con su hijo iquierdo y el factor de equilibrio
            fp << "\"" << nodo->function << "\\n" << nodo->score << "\"" << " -> " << "\"" << nodo->left->function << "\\n" << nodo->left->score << "\"" << "[label=" << nodo->FE << "]" << ";\n";
        } else {
            //Si no tiene hijo izquierdo
            //Conecta a un hijo vacío de ejemplo
            fp << "\"" << nodo->function << "\\n" << nodo->score << "i\" [shape=point];\n";
            fp << "\"" << nodo->function << "\\n" << nodo->score << "\" -> \"" << nodo->function << "\\n" << nodo->score << "i\";\n";
        }
        if(nodo->right != nullptr) {
            //Escribe la conexion con su hijo derecho y el factor de equilibrio
            fp << "\"" << nodo->function << "\\n" << nodo->score << "\"" << " -> " << "\"" << nodo->right->function << "\\n" << nodo->right->score << "\"" << "[label=" << nodo->FE << "]" << ";\n";
        } else {
            //Si no tiene hijo derecho
            //Conecta a un hijo vacío de ejemplo
            fp << "\"" << nodo->function << "\\n" << nodo->score << "d\" [shape=point];\n";
            fp << "\"" << nodo->function << "\\n" << nodo->score << "\" -> \"" << nodo->function << "\\n" << nodo->score << "d\";\n";
        }
        PreOrden(nodo->left, fp);
        PreOrden(nodo->right, fp);
    }
}

void generarGrafo(NODO* raiz) {
    if(!raiz) return;
    //Crea grafo.txt e inicia primeras lineas
    ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=gray shape=box];\n"; //tipo de figuras nodos
    //Escribe en grafo.txt recorrido en preorden
    PreOrden(raiz, fp);
    fp << "}\n";
    fp.close();

    //Crea grafo.png
    system("dot -Tpng -ografo.png grafo.txt");
    //Abre el grafo
    system("eog grafo.png &");
}

void Busqueda(NODO* nodo, double score) {
    if(nodo != nullptr) {

        //si el score es menor, revisa por la izquierda
        if(score < nodo->score) {
            Busqueda(nodo->left, score);
        } else if(score > nodo->score) {

            //si el score es mayor, revisa por la derecha
            Busqueda(nodo->right, score);
        } else {

            //si el score es igual, lo encontró
            cout << "Encontrado...\n";
            cout << "///////////////\n";
            cout << "GO: " << nodo->GO << endl;
            cout << "Score: " << nodo->score << endl;
            cout << "Función: " << nodo->function << endl;
            cout << "///////////////\n";
        }
    } else {
        cout << "El elemento no se encuentra en el árbol\n";
    }
}

void menu(NODO* raiz) {
    int opcion;
    bool inicio;
    string GO, function;
    double score;

    do {
        cout << "====== Menu de árbol ======\n";
        cout << "1) Insertar\n";
        cout << "2) Buscar\n";
        cout << "3) Grafo\n";
        cout << "0) Salir\n\n";
        cout << "Opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingresar GO: ";
                cin >> GO;
                cout << "Ingresar score: ";
                cin >> score;
                cout << "Ingresar function: ";
                cin >> function;
                insercionBalanceado(&raiz, &inicio, GO, score, function);
                break;
            case 2:
                cout << "Ingrese el score para buscar: ";
                cin >> score;
                Busqueda(raiz, score);
                break;
            case 3:
                cout << "Generando gráfico...\n";
                generarGrafo(raiz);
                break;
            case 0:
                cout << "Saliendo...\n";
                return;
            default:
                cout << "Opcion no valida\n";
                break;
        }
    }while(opcion != 0);
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Hace falta un argumento\n";
        return 0;
    }

    ifstream file(argv[1]);
    string line;
    if(!file.is_open()) {
        cout << "No se pudo abrir el archivo\n";
        return 0;
    }

    NODO* raiz = nullptr;

    //Apartar encabezado
    getline(file, line);

    while(getline(file, line)) {
        string GO;
        double score;
        string function;
        bool inicio;

        //Obtiene la linea csv
        string linea = line;
        //Inicializa ss con contenido en la linea
        stringstream ss(linea);
        //Rescata los valores de la linea en GO, score y function
        getline(ss, GO, ',');
        getline(ss, function, ',');
        ss >> score;
        //Envia los valores al árbol para insertar
        insercionBalanceado(&raiz, &inicio, GO, score, function);
    }
    
    file.close();

    menu(raiz);

    return 0;
}