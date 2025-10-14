#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct NODO{
    NODO* left;
    NODO* right;
    int FE;
    string GO;
    double score;
    string function;
};

void insercionBalanceado(NODO** nodocabeza, bool* BO, string GO, double score, string function) {
    NODO* raiz = *nodocabeza;
    NODO* nodo1;
    NODO* nodo2;

    if(raiz != nullptr) {
        if(score< raiz->score) {
            insercionBalanceado(&(raiz->left), BO, GO, score, function);
            if(*BO) {
                switch (raiz->FE) {
                    case 1:
                        raiz->FE = 0;
                        *BO = false;
                        break;
                    case 0:
                        raiz->FE = -1;
                        break;
                    case -1:
                        nodo1 = raiz->left;
                        if(nodo1-> FE <= 0) { //Rotacion II
                            raiz->left = nodo1->right;
                            nodo1->right = raiz;
                            raiz ->FE = 0;
                            raiz = nodo1;
                        } else { //Rotacion ID
                            nodo2 = nodo1->right;
                            raiz->left = nodo2->right;
                            nodo2->right = raiz;
                            nodo1->right = nodo2->left;
                            nodo2->left = nodo1;
                            
                            if(nodo2->FE == -1)
                                raiz->FE = 1;
                            else
                                raiz->FE = 0;
                            
                            if(nodo2->FE == 1)
                                nodo1->FE = -1;
                            else
                                nodo1->FE = 0;
                            raiz = nodo2;
                        }
                        raiz->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else if(score > raiz->score) {
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
        raiz = new NODO();
        raiz->GO = GO;
        raiz->score = score;
        raiz->function = function;
        raiz->left = nullptr;
        raiz->right = nullptr;
        raiz->FE = 0;
        *BO = true;
    }

    *nodocabeza = raiz;
}

void PreOrden(NODO* nodo, ofstream& fp) {
    if(nodo != nullptr) {
        if(nodo->left != nullptr) {
            fp << "\"" << nodo->function << "\\n" << nodo->score << "\"" << " -> " << "\"" << nodo->left->function << "\\n" << nodo->left->score << "\"" << "[label=" << nodo->FE << "]" << ";\n";
        } else {
            fp << "\"" << nodo->function << "\\n" << nodo->score << "i\" [shape=point];\n";
            fp << "\"" << nodo->function << "\\n" << nodo->score << "\" -> \"" << nodo->function << "\\n" << nodo->score << "i\";\n";
        }
        if(nodo->right != nullptr) {
            fp << "\"" << nodo->function << "\\n" << nodo->score << "\"" << " -> " << "\"" << nodo->right->function << "\\n" << nodo->right->score << "\"" << "[label=" << nodo->FE << "]" << ";\n";
        } else {
            fp << "\"" << nodo->function << "\\n" << nodo->score << "d\" [shape=point];\n";
            fp << "\"" << nodo->function << "\\n" << nodo->score << "\" -> \"" << nodo->function << "\\n" << nodo->score << "d\";\n";
        }
        PreOrden(nodo->left, fp);
        PreOrden(nodo->right, fp);
    }
}

void generarGrafo(NODO* raiz) {
    if(!raiz) return;
    ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=gray shape=box];\n";
    PreOrden(raiz, fp);
    fp << "}\n";
    fp.close();
    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void Busqueda(NODO* nodo, double score) {
    if(nodo != nullptr) {
        if(score < nodo->score) {
            Busqueda(nodo->left, score);
        } else if(score > nodo->score) {
            Busqueda(nodo->right, score);
        } else {
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
        cout << GO << " " << function << " " << score << endl;
        //Crea el nodo
        //Hasta aqui todo bien, salta encabezado y lee primer GO object
        insercionBalanceado(&raiz, &inicio, GO, score, function);
    }
    
    file.close();

    menu(raiz);

    return 0;
}