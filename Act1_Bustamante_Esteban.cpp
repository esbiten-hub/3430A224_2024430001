#include <iostream>
#include <random>
using namespace std;

//genera un numero aleaotorio entre -1 a 7, excluyendo 0
int numero_aleatorio() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1, 7);
    
    int num;
    do {
        num = dis(gen);
    } while (num == 0); //repetir si sale 0

    return num;
}

//inicializa la matriz con pesos aleaotorios
//ceros en la diagonal para referirse al costo 0 de un mismo nodo
void inicializar_matriz_enteros(int **M, int N) {
    for(int fila = 0; fila < N; fila++) {
        for(int columna = 0; columna < N; columna++) {
            if(fila == columna) {
                M[fila][columna] = 0;
            } else {
                M[fila][columna] = numero_aleatorio();
            }
        }
    }
}

//llena un vector de caracteres con espacios en blanco
void inicializar_vector_caracter(char vector[], int N) {
    int columna;

    for(columna = 0; columna < N; columna++) {
        vector[columna] = ' ';
    }
}

//crea nombres de nodos tipo 'a', 'b', 'c'...
void leer_nodos(char vector[], int N) {
    int i;
    int inicio = 97;

    for(i = 0; i < N; i++) {
        vector[i] = inicio + i;
    }
}

//imprime contenido de la matriz (filas y columnas) de enteros
void imprimir_matriz(int **M, int N) {
    int columna, fila;

    for(fila = 0; fila < N; fila ++) {
        for(columna = 0; columna < N; columna ++) {
            printf("matriz[%d,%d]: %d ", fila, columna, M[fila][columna]);
        }
        printf("\n");
    }
}

void imprimir_grafo(int **M, char V[], int N) {
    FILE *fp;
    fp = fopen("grafo.dot", "w");
    fprintf(fp, "graph G {\n");

    for(int i = 0; i < N; i++) {
        fprintf(fp, "  %c;\n", V[i]); //Declarar cada nodo
    }
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            if(M[i][j] > 0) {
                fprintf(fp, "  %c -- %c [label=%d];\n", V[i], V[j], M[i][j]);
            }
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);

    system("dot -Tpng grafo.dot -o grafo.png");
    system("eog grafo.png &");
}

void aplicar_prim(char V[], char U[], char VU[], char L[], int **M, int N) {
    int cantidadU = 0;
    int cantidadVU = N;
    int mejorU, mejorV;
    
    //Agregamos V[0] a U (primer nodo)
    U[cantidadU] = V[0];
    cantidadU++;
    //Remover V[0] de VU
    for(int i = 0; i < cantidadVU - 1; i++) {
        VU[i] = VU[i + 1];
    }
    cantidadVU--;

    while(cantidadU != N) {
        int minPeso = 999;
        //Buscar el par (u,v) con 'u' en U y 'v' en VU
        for(int i = 0; i < cantidadU; i++) {
            for(int j = 0; j < cantidadVU; j++) {
                //Mejor peso
                int peso = M[U[i] - 'a'][VU[j] - 'a'];
                cout << "////////////////////\n";
                cout << "El peso entre " << U[i] << " y " << VU[j] << " es " << peso << endl;
                if(peso > 0 && peso < minPeso) {
                    minPeso = peso;
                    mejorU = i;
                    mejorV = j;
                } else {
                    cout << "No hay conexion\n";
                }
            }
        }
        //Agregar el mejor nodo encontrado
        U[cantidadU] = VU[mejorV];
        cantidadU++;
        cout << "Se agrega " << U[cantidadU - 1] << endl;
        //Registrar la arista en L
        L[cantidadU - 2] = U[mejorU];
        L[cantidadU - 1] = VU[mejorV];
        cout << "Se creo L -> " << L[cantidadU - 2] << " - " << L[cantidadU - 1] << endl;
        cout << "////////////////////\n";
        //Remover el nodo de VU
        for(int k = mejorV; k < cantidadVU - 1; k++) {
            VU[k] = VU[k + 1];
        }
        cantidadVU--;
    }
    //Escribir L
    for(int i = 0; i < N - 1; i++) {
        cout << "(" << L[i] << ", " << L[i + 1] << ")" << endl;
    }







}

int main(int argc, char **argv) {
    //valida canidad de parámetros mínimos
    if(argc < 2) {
        cout << "Debe ingresar un parámetro" << endl;
        return 0;
    }
    //valida tamaño mínimo de N
    const int N = atoi(argv[1]);
    if(N <= 2) {
        cout << "N debe ser mayor a 2" << endl;
        return 0;
    }

    char V[N], U[N], VU[N], L[N];

    //Valores de la matriz
    int **M;
    M = new int*[N];
    for(int i=0; i<N; i++) {
        M[i] = new int[N];
    }
    inicializar_matriz_enteros(M, N);
    imprimir_matriz(M, N);

    //Inicializar V, U, VU y L
    inicializar_vector_caracter(V, N);
    inicializar_vector_caracter(U, N);
    inicializar_vector_caracter(VU, N);
    inicializar_vector_caracter(L, N);

    //
    leer_nodos(V, N);
    leer_nodos(VU, N);

    imprimir_grafo(M, V, N);
    //Aplicar Prim
    aplicar_prim(V, U, VU, L, M, N);











}