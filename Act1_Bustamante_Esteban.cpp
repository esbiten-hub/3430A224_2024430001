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

void aplicar_prim(char V[], char S[], char VS[], int D[], int **M, int N) {
    //
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

    char V[N], S[N], VS[N];
    int D[N];

    //Valores de la matriz
    int **M;
    M = new int*[N];
    for(int i=0; i<N; i++) {
        M[i] = new int[N];
    }
    inicializar_matriz_enteros(M, N);
    
    //Inicializar V, D Y VS
    inicializar_vector_caracter(V, N);
    inicializar_vector_caracter(S, N);
    inicializar_vector_caracter(VS, N);

    //
    leer_nodos(V, N);

    //Aplicar Prim
    aplicar_prim(V, S, VS, D, M, N);











}