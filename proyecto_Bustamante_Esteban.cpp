#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string leerFasta(string path) {
    string linea;
    string seq = "";

    ifstream in(path);

    //Verifica si se pudo abrir el archivo
    if(!in) {return seq;}
    
    //Lee el archivo
    while(getline(in, linea)) {
        //Limpiar linea
        string seqTemp = "";

        //Salta la primera linea
        if(linea[0] == '>') {continue;}

        //Elimina saltos de linea
        for(char c : linea) {
            if(c == '\r' || c == '\n' || c == '\t' || c == ' ') {continue;}
            else {seqTemp += c;}
        }
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

    //Lee la primera linea
    getline(in, linea);

    //Lee el resto
    for(int i = 0; i < 4; i++) {
        char fila;
        int col1, col2, col3, col4;

        //Toma una fila -> A 1 -1 -1 -1
        in >> fila >> col1 >> col2 >> col3 >> col4;

        //Asigna fila
        int valor_fila = asignaNucleotido(fila);

        //Verifica si se pudo asignar
        if(valor_fila == -1) {return false;}

        //Asigna columnas
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

vector<vector<int>> algoritmo_Needleman_Wunsch(string S, string T, int U[4][4], int V) {
    int n = S.size();
    int m = T.size();

    //Creo la matriz f que tendrá las puntuaciones
    vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));

    //Lee cada casilla de la matriz f y asigna la puntuacion
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {

            //f[0][0] = 0
            if(i == 0 && j == 0) {
                f[i][j] = 0;
            }

            //Rellena la primera fila con el escalado de V
            else if(i > 0 && j == 0) {
                f[i][j] = f[i - 1][j] + V;
            }

            //Rellena la primera columna con el escalado de V
            else if(i == 0 && j > 0) {
                f[i][j] = f[i][j - 1] + V;
            }

            else {
                int top = f[i - 1][j] + V;
                int left = f[i][j - 1] + V;
                int diag = f[i - 1][j - 1] + valor_de_similitud(T[i - 1], S[j - 1], U);

                //Escoge el valor más alto
                int max = top;
                if(left > max) {max = left;}
                if(diag > max) {max = diag;}

                //Asigna el valor en la matriz
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
        //Agrega a cada string
        lineaS += S[i];
        lineaT += T[i];
        lineaPipes += pipes[i];
        
        //Al llegar a un limite imprime el bloque
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

    //Imprime el ultimo bloque
    if(!lineaS.empty()) {
        cout << lineaS << endl;
        cout << lineaPipes << endl;
        cout << lineaT << endl;
        cout << endl;
    }
}

void backtracking(string S, string T, vector<vector<int>> f, int V, int U[4][4]) {
    int i = T.size();
    int j = S.size();

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

    //String que guarda los pipes
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
    
    //Imprimir alineamiento por bloques
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
    archivo << "graph [splines=false];\n";  
    archivo << "node [shape=box width=0.6 height=0.6 fixedsize=true style=filled];\n";
    archivo << "edge [arrowsize=0.7];\n";

    // ---------- 1) Crear los nodos ----------
    for(int i = 0; i <= m; i++) {
        archivo << "{ rank=same; ";  // Fuerza cada fila horizontal

        for(int j = 0; j <= n; j++) {

            if((i == 0 && j == 0)) {
                archivo << "N" << i << "_" << j 
                        << " [label=\" \"] ";
                continue;
            }

            if(j == 0) {
                archivo << "T" << i << "_" << j
                        << " [label=\"" << T[i - 1] << "\"] ";
                continue;
            }

            if(i == 0) {
                archivo << "S" << i << "_" << j
                        << " [label=\"" << S[j - 1] << "\"] ";
                continue;
            }

            archivo << "N" << i << "_" << j 
                    << " [label=\"" << f[i][j] << "\"] ";
        }

        archivo << "}\n";
    }

    // ---------- 2) Conectar nodos invisiblemente para mantener la grilla ----------
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
            // En posicion (i,0) conecta a la derecha con un nodo (i,j+1)
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
            // En posicion (i,j) conecta a la derecha con un nodo (i,j+1)
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

            // Conecta el "0" hacia abajo con una base de T
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

            // Conecta abajo con un nodo
            if(i > 0 && j > 0) {
                archivo << "N" << i << "_" << j << " -> " << "N" << (i+1) << "_" << j
                        << " [style=invis];\n";
                continue;
            }
        }
    }

    // ---------- 3) Flechas REALES del máximo ----------
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {

            if(i == 0 && j == 0) continue;
            if(i == 0) continue;
            if(j == 0) continue;

            int best = f[i][j];
            bool drawn = false;

            // Diagonal -> prioridad
            if(!drawn) {
                if(i - 1 >= 1 && j - 1 >= 1) {
                    int diag = f[i-1][j-1] + valor_de_similitud(T[i-1], S[j-1], U);
                    if(diag == best) {
                        archivo << "N" << i << "_" << j
                                << " -> N" << (i-1) << "_" << (j-1)
                                << " [color=red penwidth=2];\n";
                        drawn = true;
                    }
                }
            }

            // Arriba
            if(!drawn && f[i-1][j] + V == best) {
                archivo << "N" << i << "_" << j << " -> "
                        << "N" << (i-1) << "_" << j
                        << " [color=blue penwidth=2];\n";
                drawn = true;
            }

            // Izquierda
            if(!drawn && f[i][j-1] + V == best) {
                archivo << "N" << i << "_" << j << " -> "
                        << "N" << i << "_" << (j-1)
                        << " [color=blue penwidth=2];\n";
                drawn = true;
            }
        }
    }

    archivo << "}\n";
    archivo.close();

    cout << "Archivo cuadricula.dot creado correctamente.\n";
}

int main(int argc, char *argv[]) {
    //Valida cantidad de argumentos
    if(argc != 9) {
        cout << "Cantidad de argumentos incorrecta" << endl;
        return 0;
    }

    int V = 0;
    int U[4][4];
    string cad1, cad2, funU;
    string S, T;

    //Asigna los argumentos
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if(arg == "-C1") {cad1 = argv[++i];}
        else if(arg == "-C2") {cad2 = argv[++i];}
        else if(arg == "-U") {funU = argv[++i];}
        else if(arg == "-V") {V = atoi(argv[++i]);}
        else {
            cout << "Argumento invalido" << endl;
            return 0;
        }
    }

    //Valida cantidad de argumentos
    if(cad1 == "" || cad2 == "" || funU == "" || V == 0) {
        cout << "Argumentos incorrectos" << endl;
        return 0;
    }

    //Lee los archivos
    S = leerFasta(cad1);
    T = leerFasta(cad2);
    //Verifica si se pudieron leer
    if(S.empty() || T.empty()) {
        cout << "No se pudo leer las secuencias" << endl;
        return 0;
    }

    //Lee la función de similitud
    if(!leer_funU(funU, U)) {
        cout << "No se pudo leer la función de similitud" << endl;
    }

    //Llama al algoritmo que rellena la matriz f con las puntuaciones del alineamiento
    vector<vector<int>> f = algoritmo_Needleman_Wunsch(S, T, U, V);
   
    //Backtracking para obtener el alineamiento
    backtracking(S, T, f, V, U);

    //Genera la cuadricula
    generarCuadricula(S, T, f, V, U);
    system("dot -Tpng cuadricula.dot -o cuadricula.png");

    return 0;
}