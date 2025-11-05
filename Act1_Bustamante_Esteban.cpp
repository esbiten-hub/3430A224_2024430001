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
    int col;

    for (col=0; col<N; col++) {
        vector[col] = ' ';
    }
}

//copia la primera fila de la matriz al vector D (distancias iniciales)
void inicializar_vector_D(int D[], int **M, int N) {
    int col;

    for (col=0; col<N; col++) {
        D[col] = M[0][col];
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

//imprime un vector de caracteres con nombre
void imprimir_vector_caracter(char vector[], int N, const char *nomVector) {
    int i;

    for(i = 0; i < N; i++) {
        printf("%s[%d]: %c ", nomVector, i, vector[i]);
    }
    printf("\n");
}

//imprime un vector D de costos
void imprimir_vector_entero(int vector[], int N) {
    int i;

    for(i = 0; i < N; i++) {
        printf("D[%d]: %d ", i, vector[i]);
    }
    printf("\n");
}

//agrega vértice a S[] (conjuntos ya visitados)
void agrega_vertice_a_S(char S[], char vertice, int N) {
    int i;
    
    //recorrer buscando un espacio vacio
    for(i = 0; i < N; i++) {
        if(S[i] == ' ') {
            S[i] = vertice;
            return;
        }
    }
}

//busca si un vertice ya esta en S[]
bool busca_caracter(char c, char vector[], int N) {
    int j;

    for(j = 0; j < N; j++) {
        if(c == vector[j]) {
            return true;
        }
    }
    return false;
}

//actualiza VS con los nodos que NO estan todavia en S
void actualizar_VS(char V[], char S[], char VS[], int N) {
    int j;
    int k = 0;

    inicializar_vector_caracter(VS, N);

    for(j = 0; j < N; j++) {
        //por cada caracter en V[] evalua si está en S[]
        //si no esta, lo agrega a VS[]
        if(!busca_caracter(V[j], S, N)) {
            VS[k] = V[j];
            k++;
        }
    }
}

//encuentra índice del vertice en V[]
int buscar_indice_caracter(char V[], char c, int N) {
    int i;

    for(i = 0; i < N; i++) {
        if(V[i] == c) {
            return i;
        }
    }
    return i;
}

//elige vértice con menor peso en VS[]
//busca su peso en D[]
int elegir_vertice(char VS[], int D[], char V[], int N) {
    int i = 0;
    int menor = 0;
    int peso, vertice;

    while(VS[i] != ' ') { //recorrer solo los válidos
        peso = D[buscar_indice_caracter(V, VS[i], N)];
        //descarta valores infinitos (-1) y 0
        if((peso != 1) && (peso != 0)) {
            if(i == 0) {
                menor = peso;
                vertice = VS[i];
            } else {
                if(peso < menor) {
                    menor = peso;
                    vertice = VS[i];
                }
            }
        }
        i++;
    }
    printf("\nvertice elegido: %c\n", vertice);
    return vertice;
}

//retorna el minimo entre el valor actual y uno posible nuevo
int calcular_minimo(int dw, int dv, int mvw) {
    int min = 0;

    // si w e infinito
    if(dw == -1) {
        //si existe camino hasta v y de v a w
        if(dv != -1 && mvw != -1) {
            min = dv + mvw;
        } else {
            min = -1;
        }

    } else {
        //comparacion con nueva posible ruta
        if(dv != -1 && mvw != -1) {
            if(dw <= (dv + mvw)) {
                min = dw;
            } else {
                min = (dv + mvw);
            }
        } else {
            min = dw;
        }
    }

    printf("dw; %d dv: %d mvw: %d min: %d\n", dw, dv, mvw, min);
    return min;
}

//actualiza pesos en D tras elegir un nuevo vertice
void actualizar_pesos(int D[], char VS[], int **M, char V[], char v, int N) {
    int i = 0;
    int indice_w, indice_v;

    printf("\nActualizando pesos en D[]\n");

    indice_v = buscar_indice_caracter(V, v, N);
    while(VS[i] != ' ') {
        if(VS[i] != v) {
            indice_w = buscar_indice_caracter(V, VS[i], N);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
        i++;
    }
}

void libera_memoria(int **M, int N) {
    for(int i = 0; i < N; i++) {
        delete[] M[i];
    }
    delete[] M;
}

//implementacion de algoritmo dijkstra
void aplicar_dijkstra(char V[], char S[], char VS[], int D[], int **M, int N) {
    int i;
    int v;

    //inicializar vector D[] segun datos de la matriz M[][]
    //estado inicial
    inicializar_vector_D(D, M, N);

    //estado inicial
    printf("------------ Estados iniciales ------------\n");
    imprimir_matriz(M, N);
    printf("\n");
    imprimir_vector_caracter(S, N, "S");
    imprimir_vector_caracter(VS, N, "VS");
    imprimir_vector_entero(D, N);
    printf("-------------------------------------------\n");

    //agrega primer vertice a VS
    printf("Agrega primer valor V[0] a S[] y actualiza VS[]\n\n");
    agrega_vertice_a_S(S, V[0], N);
    imprimir_vector_caracter(S, N, "S");
    //actualiza VS
    actualizar_VS(V, S, VS, N);
    imprimir_vector_caracter(VS, N, "VS");
    imprimir_vector_entero(D, N);

    //procesa el resto de nodos
    for(i = 1; i < N; i++) {
        //elige un vértice en v de VS[] tal que D[v] sea mínimo
        printf("\n\nElige el vértice menor en VS[] según valores en D[]\n");
        printf("Lo agrega a S[] y actualiza VS[]\n");
        v = elegir_vertice(VS, D, V, N);

        //
        agrega_vertice_a_S(S, v, N);
        imprimir_vector_caracter(S, N, "S");
        //actualiza VS
        actualizar_VS(V, S, VS, N);
        imprimir_vector_caracter(VS, N, "VS");
        
        //actualizar pesos
        actualizar_pesos(D, VS, M, V, v, N);
        imprimir_vector_entero(D, N);
    }
}

//genera archivo graphviz para visualizar el grafo
void imprimir_grafo(int **M, char vector[], int N) {
    int i, j;
    FILE *fp;

    fp = fopen("grafo.txt", "w");
    fprintf(fp, "%s\n", "digraph G {");
    fprintf(fp, "%s\n", "graph [rankdir=LR]");
    fprintf(fp, "%s\n", "node [style=filled fillcolor=yellow];");

    //imprimir solo aristas validas (ignora la diagonal principal)
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(i != j) {
                if(M[i][j] > 0) {
                    fprintf(fp, "%c%s%c [label=%d];\n", vector[i], "->", vector[j], M[i][j]);
                }
            }
        }
    }

    fprintf(fp, "%s\n", "}");
    fclose(fp);

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");

    libera_memoria(M, N);
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

    //Aplicar Dijkstra
    aplicar_dijkstra(V, S, VS, D, M, N);

    //Exporta grafo visual
    imprimir_grafo(M, V, N);
    


    return 0;
}