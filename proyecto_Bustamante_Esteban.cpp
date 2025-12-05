#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string leerFasta(string path) {
    string linea;
    string seq = "";

    // Abre la ruta en solo lectura
    ifstream in(path);

    //Verifica si se pudo abrir el archivo de la ruta
    if(!in) {return seq;}
    
    while(getline(in, linea)) {

        // Limpiar linea en cada ciclo del while
        string seqTemp = "";

        //Salta solamente la primera linea (encabezado del FASTA)
        if(linea[0] == '>') {continue;}

        // Cada caracter de la linea -> se eliminan saltos de linea y luego es agregado seqTemp
        for(char c : linea) {
            if(c == '\r' || c == '\n' || c == '\t' || c == ' ') {continue;}
            else {seqTemp += c;}
        }

        // Se guarda seqTemp filtrado en seq
        seq += seqTemp;
    }
    return seq;
}

int asignaNucleotido(char nucleotido) {
    switch(nucleotido) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return -1;
    }
}

bool leer_funU(string path, int U[4][4]) {
    ifstream in(path);
    
    if(!in) {return false;}

    string linea;

    // Recibe la primera linea
    getline(in, linea);

    // Lee el resto
    for(int i = 0; i < 4; i++) {

        // Variables para cada linea
        char fila;
        int col1, col2, col3, col4;

        // Ejemplo -> A 1 -1 -1 -1
        in >> fila >> col1 >> col2 >> col3 >> col4;

        // Retorna número de la fila
        // Ejemplo: A -> 0
        int valor_fila = asignaNucleotido(fila);

        // Verifica si se pudo asignar
        if(valor_fila == -1) {return false;}

        // Asigna las columnas
        U[valor_fila][0] = col1;
        U[valor_fila][1] = col2;
        U[valor_fila][2] = col3;
        U[valor_fila][3] = col4;
    }
    return true;
}

int valor_de_similitud(char fila, char col, int U[4][4]) {
    int val;

    //Entrega el valor de similitud buscando en U la fila y columna entregada
    val = U[asignaNucleotido(fila)][asignaNucleotido(col)];

    return val;
}

void muestraMatrizSimilitud(int U[4][4]) {
    char bases[4] = {'A', 'C', 'G', 'T'};

    // Imprime el encabezado
    cout << "  ";
    for(int i = 0; i < 4; i++) {
        cout << bases[i] << " ";
    }
    cout << endl;

    // Imprime las filas
    for(int i = 0; i < 4; i++) {

        // Primero la base (letra)
        cout << bases[i] << " ";

        // Luego las columnas (valores)
        // Ej: A 1 -1 -1 -1
        for(int j = 0; j < 4; j++) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> algoritmo_Needleman_Wunsch(string S, string T, int U[4][4], int V) {

    int n = S.size(); // Columnas
    int m = T.size(); // Filas

    // Crea la matriz f que tendrá las puntuaciones
    vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));

    // Recorre cada casilla de la matriz f y asigna la puntuacion
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {

            // f[0][0] = 0
            if(i == 0 && j == 0) {
                f[i][j] = 0;
            }

            // Rellena la primera columna con el escalado de V
            else if(i > 0 && j == 0) {
                f[i][j] = f[i - 1][j] + V;
            }

            // Rellena la primera fila con el escalado de V
            else if(i == 0 && j > 0) {
                f[i][j] = f[i][j - 1] + V;
            }

            else {
                int top = f[i - 1][j] + V;
                int left = f[i][j - 1] + V;
                int diag = f[i - 1][j - 1] + valor_de_similitud(T[i - 1], S[j - 1], U);

                // Escoge el valor más alto
                int max = top;
                if(left > max) {max = left;}
                if(diag > max) {max = diag;}

                // Asigna el valor en la matriz
                f[i][j] = max;
            }
        }
    }

    return f;
}

void muestraAlineamiento(string S, string T, string pipes) {
    string lineaS = "";
    string lineaT = "";
    string lineaPipes = "";

    for(int i = 0; i < (int)S.size(); i++) {
        // Agrega a cada string
        lineaS += S[i];
        lineaT += T[i];
        lineaPipes += pipes[i];
        
        // Imprime bloques de 80 caracteres
        if((i + 1) % 80 == 0) {
            cout << lineaS << endl;
            cout << lineaPipes << endl;
            cout << lineaT << endl;
            cout << endl;

            lineaS = "";
            lineaT = "";
            lineaPipes = "";
        }
    }

    //Imprime el ultimo bloque (< 80)
    if(!lineaS.empty()) {
        cout << lineaS << endl;
        cout << lineaPipes << endl;
        cout << lineaT << endl;
        cout << endl;
    }
}

void backtracking(string S, string T, vector<vector<int>> f, int V, int U[4][4]) {
    int i = T.size(); // Fila
    int j = S.size(); // Columna

    string alineamientoS = "";
    string alineamientoT = "";

    while(i > 0 || j > 0) {

        //Vino desde la diagonal (caso de match o missmatch)
        if(i > 0 && j > 0 && f[i][j] == f[i - 1][j - 1] + valor_de_similitud(T[i - 1], S[j - 1], U)) {
            alineamientoS = S[j - 1] + alineamientoS;
            alineamientoT = T[i - 1] + alineamientoT;
            i--;
            j--;
            continue;
        }

        //Vino desde arriba
        else if(i > 0 && j > 0 && f[i][j] == f[i - 1][j] + V) {
            alineamientoS = "-" + alineamientoS;
            alineamientoT = T[i - 1] + alineamientoT;
            i--;
            continue;
        }

        //Vino desde la izquierda
        else if(i > 0 && j > 0 && f[i][j] == f[i][j - 1] + V) {
            alineamientoS = S[j - 1] + alineamientoS;
            alineamientoT = "-" + alineamientoT;
            j--;
            continue;
        }

        //Casos extremos
        if(i > 0) {
            alineamientoS = "-" + alineamientoS;
            alineamientoT = T[i - 1] + alineamientoT;
            i--;
        } else {
            alineamientoS = S[j - 1] + alineamientoS;
            alineamientoT = "-" + alineamientoT;
            j--;
        }
    }

    // String que guarda los pipes
    string pipes = "";
    for(int i = 0; i < (int)alineamientoS.size(); i++) {
        if(alineamientoS[i] == alineamientoT[i] && alineamientoS[i] != '-') {
            pipes += "|";
        } else {
            pipes += " ";
        }
    }

    cout << "--------------------------------------\n";
    cout << "Resultado del alineamiento:\n";
    cout << "--------------------------------------\n";

    // Imprimir alineamiento por bloques
    muestraAlineamiento(alineamientoS, alineamientoT, pipes);
}

void generarCuadricula(string S, string T, vector<vector<int>> f, int V, int U[4][4]) {
    ofstream archivo("cuadricula.dot");

    if(!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    int n = S.size(); // Columnas
    int m = T.size(); // Filas

    archivo << "digraph G {\n";
    archivo << "node [shape=box style=filled];\n";

    // Crea nodos
    for(int i = 0; i <= m; i++) {
        archivo << "{ rank=same; ";  // Fuerza cada fila horizontal

        for(int j = 0; j <= n; j++) {

            // Crea el nodo en f[0][0]
            if((i == 0 && j == 0)) {
                archivo << "N" << i << "_" << j 
                        << " [label=\" \"] ";
                continue;
            }

            // Crea los nodos de la primera columna -> string T
            if(j == 0) {
                archivo << "T" << i << "_" << j
                        << " [label=\"" << T[i - 1] << "\"] ";
                continue;
            }

            // Crea los nodos de la primera fila -> string S
            if(i == 0) {
                archivo << "S" << i << "_" << j
                        << " [label=\"" << S[j - 1] << "\"] ";
                continue;
            }

            // Crea los nodos de las puntuaciones
            archivo << "N" << i << "_" << j 
                    << " [label=\"" << f[i][j] << "\"] ";
        }

        archivo << "}\n";
    }

    // Conecta cada nodo con el siguiente (para una grilla rectangular)

    // De izquierda a derecha
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j < n; j++) {

            // En posicion (0,0) conecta a la derecha con la base S(0,1)
            if(i == 0 && j == 0) {
                archivo << "N" << i << "_" << j << " -> " << "S" << i << "_" << (j+1)
                        << " [style=invis];\n";
                continue;
            }
            
            // Con i > 0 y j == 0
            // En posicion (i,0) conecta a la derecha con un nodo N(i,j+1)
            if(j == 0) {
                archivo << "T" << i << "_" << j << " -> " << "N" << i << "_" << (j+1)
                        << " [style=invis];\n";
                continue;
            }
            
            // Con i = 0 y j > 0
            // En posicion (0,j) conecta a la derecha con la base S(0,j+1)
            if(i == 0) {
                archivo << "S" << i << "_" << j << " -> " << "S" << i << "_" << (j+1)
                        << " [style=invis];\n";
                continue;
            }
            
            // Con i > 0 y j > 0
            // En posicion (i,j) conecta a la derecha con un nodo N(i,j+1)
            if(i > 0 && j > 0) {
                archivo << "N" << i << "_" << j << " -> " << "N" << i << "_" << (j+1)
                        << " [style=invis];\n";
                continue;
            }
        }
    }

    // De arriba a abajo
    for(int j = 0; j <= n; j++) {
        for(int i = 0; i < m; i++) {

            // Conecta el " " hacia abajo con una base de T
            if(i == 0 && j == 0) {
                archivo << "N" << i << "_" << j << " -> " << "T" << (i+1) << "_" << j
                        << " [style=invis];\n";
                continue;
            }

            // Conecta base S hacia abajo con un nodo
            if(i == 0) {
                archivo << "S" << i << "_" << j << " -> " << "N" << (i+1) << "_" << j
                        << " [style=invis];\n";
                continue;
            }

            // Conecta base de T hacia abajo con otra base de T
            if(j == 0) {
                archivo << "T" << i << "_" << j << " -> " << "T" << (i+1) << "_" << j
                        << " [style=invis];\n";
                continue;
            }

            // Conecta nodo hacia abajo con otro nodo
            if(i > 0 && j > 0) {
                archivo << "N" << i << "_" << j << " -> " << "N" << (i+1) << "_" << j
                        << " [style=invis];\n";
                continue;
            }
        }
    }

    // Flechas del mejor recorrido
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {

            // Ignora el " " (i == 0 && j == 0), el string S (i == 0) y el string T (j == 0)
            if(i == 0 && j == 0) continue;
            if(i == 0) continue;
            if(j == 0) continue;

            int mejorPuntuacion = f[i][j];
            bool seleccion = false;

            // Diagonal -> prioridad
            if(!seleccion) {
                if(i - 1 >= 1 && j - 1 >= 1) {
                    int diag = f[i-1][j-1] + valor_de_similitud(T[i-1], S[j-1], U);
                    if(diag == mejorPuntuacion) {
                        archivo << "N" << i << "_" << j
                                << " -> N" << (i-1) << "_" << (j-1)
                                << " [color=red penwidth=2];\n";
                        seleccion = true;
                    }
                }
            }

            // Arriba -> segunda prioridad
            if(!seleccion && f[i-1][j] + V == mejorPuntuacion) {
                archivo << "N" << i << "_" << j << " -> "
                        << "N" << (i-1) << "_" << j
                        << " [color=blue penwidth=2];\n";
                seleccion = true;
            }

            // Izquierda -> tercera prioridad
            if(!seleccion && f[i][j-1] + V == mejorPuntuacion) {
                archivo << "N" << i << "_" << j << " -> "
                        << "N" << i << "_" << (j-1)
                        << " [color=blue penwidth=2];\n";
                seleccion = true;
            }
        }
    }

    archivo << "}\n";
    archivo.close();

    cout << "Archivo cuadricula.dot creado correctamente.\n";
}

int main(int argc, char *argv[]) {

    // Deben ser 9 parámetros
    if(argc != 9) {
        cout << "Cantidad de parámetros incorrecta" << endl;
        return 0;
    }

    int V = 0;
    int U[4][4];
    string cad1, cad2, funU;
    string S, T;

    // Asigna argumento según parámetro
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if(arg == "-C1") {cad1 = argv[++i];}
        else if(arg == "-C2") {cad2 = argv[++i];}
        else if(arg == "-U") {funU = argv[++i];}
        else if(arg == "-V") {V = atoi(argv[++i]);}
        else {
            cout << "Error: parámetro mal referenciado" << endl;
            return 0;
        }
    }

    // No acepta parámetros vacíos
    if(cad1 == "" || cad2 == "" || funU == "" || V == 0) {
        cout << "Se ha entregado un parámetro vacío" << endl;
        return 0;
    }

    // Lee los archivos y crea las secuencias en "string"
    S = leerFasta(cad1);
    T = leerFasta(cad2);
    // Verifica que se hayan ingresado las secuencias a los string
    if(S.empty() || T.empty()) {
        cout << "No se pudo leer las secuencias" << endl;
        return 0;
    }

    // Lee y crea la función de similitud U
    if(!leer_funU(funU, U)) {
        cout << "No se pudo leer la función de similitud" << endl;
    }

    // Llama al algoritmo que rellena la matriz f con las puntuaciones del alineamiento
    vector<vector<int>> f = algoritmo_Needleman_Wunsch(S, T, U, V);
   
    cout << "--------------------------------------\n";
    cout << "     Algoritmo de Needleman Wunsch    \n";
    cout << "--------------------------------------\n";
    cout << endl;
    // Imprime las secuencias
    cout << "Secuencia 1: " << S << endl;
    cout << "Secuencia 2: " << T << endl;
    cout << endl;
    // Muestra la matriz de similitud
    cout << "Se utilizará la función de similitud: \n";
    muestraMatrizSimilitud(U);
    cout << endl;


    // Backtracking para obtener el alineamiento
    backtracking(S, T, f, V, U);

    // Genera la cuadricula
    generarCuadricula(S, T, f, V, U);
    system("dot -Tpng cuadricula.dot -o cuadricula.png");

    return 0;
}