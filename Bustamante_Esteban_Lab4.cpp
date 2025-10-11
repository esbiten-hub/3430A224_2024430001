#include <iostream>
#include <fstream>
#include <set>
using namespace std;

//Estructura de un nodo
struct Node {
    int info;
    Node* left;
    Node* right;
};


Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Función para crear el árbol
void crea_arbol(Node* &apnodo, set<int>& valores) {
    if(apnodo == nullptr) {
        int valor;
        do {
            cout << "Ingrese valor para el nodo: ";
            cin >> valor;
            if(valores.count(valor)) { //Revisa si el valor ya existe en el "set"
                cout << "El valor ya existe. Ingrese otro valor.\n";
            }
        } while (valores.count(valor));

        apnodo = createNode(valor); // Crea el nodo
        valores.insert(valor); // Agrega el valor al set
    }

    char resp;

    // Preguntar por hijo izquierdo
    cout << "¿Existe nodo por la izquierda de " << apnodo->info << "? (s/n): ";
    cin >> resp;
    if(resp == 's' || resp == 'S') {
        apnodo->left = nullptr;
        crea_arbol(apnodo->left, valores); // llamada recursiva con nodo izquierdo
    } else {
        apnodo->left = nullptr;
    }

    // Preguntar por hijo derecho
    cout << "¿Existe nodo por la derecha de " << apnodo->info << "? (s/n): ";
    cin >> resp;
    if(resp == 's' || resp == 'S') {
        apnodo->right = nullptr;
        crea_arbol(apnodo->right, valores); // llamada recursiva con nodo derecho
    } else {
        apnodo->right = nullptr;
    }
}

void printPreorden(Node* nodo) {
    if(nodo != nullptr) {
        cout << nodo->info << " ";

        printPreorden(nodo->left);
        printPreorden(nodo->right);
    }
}


void printInorden(Node* nodo) {
    if(nodo != nullptr) {
        printInorden(nodo->left);
        cout << nodo->info << " ";
        printInorden(nodo->right);
    }
}

void printPosorden(Node* nodo) {
    if(nodo != nullptr) {
        printPosorden(nodo->left);
        printPosorden(nodo->right);
        cout << nodo->info << " ";
    }
}


void recorrerArbol(Node*& nodo) {
    cout << "Recorrido en preorden: ";
    printPreorden(nodo);
    cout << "\nRecorrido en inorden: ";
    printInorden(nodo);
    cout << "\nRecorrido en postorden: ";
    printPosorden(nodo);
    cout << "\n";
    return;
}

void insertarNumero(Node*& nodo, int num) {
    if(num < nodo->info) {
        // Si el numero es menor -> revisa nodo izquierdo
        //si nodo izquierdo existe -> llamada recuriva, si no -> agrega
        if(nodo->left == nullptr) {
            nodo->left = createNode(num);
        } else {
            insertarNumero(nodo->left, num);
        }
    } else {
        // Si el numero es mayor -> revisa nodo derecho
        //si nodo derecho existe -> llamada recuriva, si no -> agrega
        if(num > nodo->info) {
            if(nodo->right == nullptr) {
                nodo->right = createNode(num);
            } else {
                insertarNumero(nodo->right, num);
            }
        } else {
            cout << "El número ya existe en el árbol.\n";
        }
    }
}

void eliminarNumero(Node*& nodo, int num) {
    if(nodo != nullptr) {
        //Busca el nodo con el numero a eliminar
        if(num < nodo->info) {
            eliminarNumero(nodo->left, num);
        } else {
            if(num > nodo->info) {
                eliminarNumero(nodo->right, num);
            } else {
                //Guarda el nodo a eliminar en un nodo auxiliar
                //para no perder la referencia antes de eliminarlo
                Node* OTRO;
                OTRO = nodo;
                if(OTRO->right == nullptr) {
                    //Si no tiene hijo derecho, el arbol se engancha con el hijo izquierdo
                    nodo = OTRO->left;
                } else {
                    if(OTRO->left == nullptr) {
                        //Si no tiene hijo izquierdo, el arbol se engancha con el hijo derecho
                        nodo = OTRO->right;
                    } else {
                        //Si tiene ambos hijos, busca el nodo mas grande del subarbol izquierdo
                        //para sustituir el nodo a eliminar
                        Node* aux;
                        Node* aux1;
                        aux = nodo->left;
                        bool BO = false;
                        while(aux->right != nullptr) {
                            aux1 = aux;
                            aux = aux->right;
                            BO = true;
                        }
                        //Reemplaza el nodo a eliminar con el nodo mas grande del subarbol izquierdo
                        nodo->info = aux->info;
                        OTRO = aux;
                        //Sirve para reconectar el arbol
                        if(BO == true) {
                            aux1->right = aux->left;
                        } else {
                            nodo->left = aux->left;
                        }
                    }
                    //Libera memoria
                    delete OTRO;
                }
            }
        }
    } else {
        cout << "El número no existe en el árbol.\n";
    }
}

void modificarNumero(Node*& nodo, int num) {
    //Si el numero es menor -> revisa nodo izquierdo
    //Si el numero es mayor -> revisa nodo derecho
    if(num < nodo->info) {
        if(nodo->left == nullptr) {
            cout << "La información no se encuentra en el árbol.\n";
        } else {
            modificarNumero(nodo->left, num);
        }
    } else {
        if(num > nodo->info) {
            if(nodo->right == nullptr) {
                cout << "La información no se encuentra en el árbol.\n";
            } else {
                modificarNumero(nodo->right, num);
            }
        
        //Si encuentra el numero a modificar, reemplaza con la nueva informacion
        } else {
            cout << "La información está en el árbol.\n";
            cout << "Ingrese la nueva información: ";
            cin >> nodo->info;
        }
    }
}

void escribirRecorrido(Node* nodo, ofstream& fp) {
    if(nodo != nullptr) {
        if(nodo->left != nullptr) {
            //Escribe la conexion del nodo con su hijo izquierdo
            fp << "\"" << to_string(nodo->info) << "\" -> \"" << to_string(nodo->left->info) << "\";\n";
        } else {
            //Crea un nodo auxiliar vacio para hacer referencia a proximos nodos
            string cadena = to_string(nodo->info) + "i";
            fp <<  "\"" << cadena << "\" [shape=point];\n";
            fp << "\"" << to_string(nodo->info) << "\" -> \"" << cadena << "\";\n";
        }

        if(nodo->right != nullptr) {
            //Escribe la conexion del nodo con su hijo derecho
            fp << "\"" << to_string(nodo->info) << "\" -> \"" << to_string(nodo->right->info) << "\";\n";
        } else {
            //Crea un nodo auxiliar vacio para hacer referencia a proximos nodos
            string cadena = to_string(nodo->info) + "d";
            fp << "\"" << cadena << "\" [shape=point];\n";
            fp << "\"" << to_string(nodo->info) << "\" -> \"" << cadena << "\";\n";
        }

        //Llamada recursiva para los nodos hijos
        //Es un recorrido en preorden
        escribirRecorrido(nodo->left, fp);
        escribirRecorrido(nodo->right, fp);
    }
}

void generarGrafo(Node* nodo) {
    ofstream fp("grafo.txt");

    if (!fp.is_open()) {
        cerr << "Error al abrir el archivo grafo.txt\n";
        return;
    }

    // Encabezado
    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    // Cuerpo del grafo
    escribirRecorrido(nodo, fp);

    fp << "}\n";

    fp.close();

    // Generar y mostrar la imagen del árbol
    system("dot -Tpng -o grafo.png grafo.txt");
    system("eog grafo.png");
}


void menu(Node*& root) {
    int opcion;
    int num;

    do {
        cout << "====== Menu de árbol binario ======\n";
        cout << "1. Insertar número\n";
        cout << "2. Eliminar número buscado\n";
        cout << "3. Modificar un elemento buscado\n";
        cout << "4. Recorrer el árbol en Preorden, Inorden y Posorden\n";
        cout << "5. Generar grafo del árbol\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
                cout << "Ingrese el número a insertar: ";
                cin >> num;
                insertarNumero(root, num);
                break;
            case 2:
                cout << "Ingrese el número a eliminar: ";
                cin >> num;
                eliminarNumero(root, num);
                break;
            case 3:
                cout << "Ingrese el número a modificar: ";
                cin >> num;
                modificarNumero(root, num);
                break;
            case 4:
                recorrerArbol(root);
                break;
            case 5:
                generarGrafo(root);
                break;
            case 6:
                cout << "Saliendo...\n";
                return;
            default:
                cout << "Opcion no valida\n";
                break;
        }
    } while(opcion != 6);
}


int main() {
    Node* root = nullptr;
    set<int> valores; // Conjunto para verificar duplicados

    cout << "Para comenzar cree el árbol binario\n";
    crea_arbol(root, valores);

    menu(root);
    return 0;
}