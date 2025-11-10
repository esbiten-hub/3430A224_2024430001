#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

void burbuja(int arreglo[], int N) {
    for(int i = 0; i < N - 1; i++) {
        for(int j = 0; j < N - i - 1; j++) {
            if(arreglo[j] > arreglo[j + 1]) {
                int aux = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = aux;
            }
        }
    }
    //print arreglo
    for(int i = 0; i < N; i++) {
        cout << "a[" << i << "]" << arreglo[i] << " ";
    }
    cout << endl;
}

void insercion(int arreglo[], int N) {
    for(int i = 1; i < N; i++) {
        int aux = arreglo[i];
        int j = i - 1;
        while(j >= 0 && arreglo[j] > aux) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = aux;
    }
    //print arreglo
    for(int i = 0; i < N; i++) {
        cout << "a[" << i << "]" << arreglo[i] << " ";
    }
    cout << endl;
}

void seleccion(int arreglo[], int N) {
    for(int i = 0; i < N - 1; i++) {
        int menor = arreglo[i];
        int k = i;
        for(int j = i + 1; j < N; j++) {
            if(arreglo[j] < menor) {
                menor = arreglo[j];
                k = j;
            }
        }
        int aux = arreglo[i];
        arreglo[i] = arreglo[k];
        arreglo[k] = aux;
    }
    //print arreglo
    for(int i = 0; i < N; i++) {
        cout << "a[" << i << "]" << arreglo[i] << " ";
    }
    cout << endl;
}

void copiarArreglo(int arreglo[], int aux[], int N) {
    for(int i = 0; i < N; i++) {
        aux[i] = arreglo[i];
    }
}

void ordenamiento_interno(int arreglo[], int N) {
    //Burbuja
    int aux[N];
    copiarArreglo(arreglo, aux, N);
    auto start = high_resolution_clock::now();
    burbuja(aux, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Burbuja       | " << duration << " milisegundos\n";

    //Insercion
    copiarArreglo(arreglo, aux, N);
    start = high_resolution_clock::now();
    insercion(aux, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Insercion     | " << duration << " milisegundos\n";

    //Selección
    copiarArreglo(arreglo, aux, N);
    start = high_resolution_clock::now();
    seleccion(aux, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Seleccion     | " << duration << " milisegundos\n";
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        cout << "El programa requiere dos parámetros." << endl;
        return 0;
    }

    int N = atoi(argv[1]);
    char ver = tolower(argv[2][0]);

    if(N <= 0 || (ver != 's' && ver != 'n')) {
        cout << "Error: parámetros inválidos." << endl;
        return 0;
    }

    //Crea el arreglo
    int arreglo[N];
    srand(time(nullptr));
    for(int i = 0; i < N; i++) {
        arreglo[i] = rand() % 50;
    }

    //Imprime el arreglo si ver == 's'
    if(ver == 's') {
        for(int i = 0; i < N; i++) {
            cout << "a[" << i << "]" << arreglo[i] << " ";
        }
        cout << endl;
    }
    
    cout << "------------------------------\n";
    cout << "Método         | Tiempo\n";
    cout << "------------------------------\n";

    ordenamiento_interno(arreglo, N);
    return 0;
}