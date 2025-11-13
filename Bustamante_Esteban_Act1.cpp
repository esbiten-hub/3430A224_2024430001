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
}

void copiarArreglo(int arreglo[], int aux[], int N) {
    for(int i = 0; i < N; i++) {
        aux[i] = arreglo[i];
    }
}

void printArreglo(int arreglo[], int N) {
    for(int i = 0; i < N; i++) {
        cout << "a[" << i << "]" << arreglo[i] << " ";
    }
    cout << endl;
}

void shellsort(int arreglo[], int N) {
    int INT = N + 1; //tamaño de salto inicial
    bool BAND; //bandera de intercambio
    while(INT > 1) {
        INT /= 2; //reducir el intervalo
        BAND = true;
        while(BAND) {
            BAND = false;
            int i = 0;
            while((i + INT) < N) {
                if(arreglo[i] > arreglo[i + INT]) {
                    int aux = arreglo[i];
                    arreglo[i] = arreglo[i + INT];
                    arreglo[i + INT] = aux;
                    BAND = true;
                }
                i++;
            }
        }
    }
}

void reduce(int arreglo[], int INI, int FIN, int &POS) {
    int IZQ = INI;
    int DER = FIN;
    int AUX;
    bool BAND = true;
    POS = INI;

    while(BAND) {
        //Mover DER hacia la izquierda mientras A[POS] <= A[DER]
        while((arreglo[POS] <= arreglo[DER]) && (POS != DER)) {
            DER--;
        }
        if(POS == DER) {
            BAND = false;
        } else {
            AUX = arreglo[POS];
            arreglo[POS] = arreglo[DER];
            arreglo[DER] = AUX;
            POS = DER;

            //Mover IZQ hacia la derecha mientras A[POS] >= A[IZQ]
            while((arreglo[POS] >= arreglo[IZQ]) && (POS != IZQ)) {
                IZQ++;
            }
            if(POS == IZQ) {
                BAND = false;
            } else {
                AUX = arreglo[POS];
                arreglo[POS] = arreglo[IZQ];
                arreglo[IZQ] = AUX;
                POS = IZQ;
            }
        }
    }
}

void quicksort(int arreglo[], int N) {
    int INI, FIN, POS;
    int TOPE = 0;
    int PILAMENOR[N];
    int PILAMAYOR[N];

    TOPE = 1;
    PILAMENOR[TOPE] = 0;
    PILAMAYOR[TOPE] = N - 1;

    while(TOPE > 0) {
        INI = PILAMENOR[TOPE];
        FIN = PILAMAYOR[TOPE];
        TOPE--;
        reduce(arreglo, INI, FIN, POS);

        if(INI < (POS - 1)) {
            TOPE++;
            PILAMENOR[TOPE] = INI;
            PILAMAYOR[TOPE] = POS - 1;
        }

        if(FIN > (POS + 1)) {
            TOPE++;
            PILAMENOR[TOPE] = POS + 1;
            PILAMAYOR[TOPE] = FIN;
        }
    }
}

void ordenamiento_interno(int arreglo[], int N, char ver) {
    //Burbuja
    int aux_burbuja[N];
    copiarArreglo(arreglo, aux_burbuja, N);
    auto start = high_resolution_clock::now();
    burbuja(aux_burbuja, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Burbuja       | " << duration << " milisegundos\n";

    //Insercion
    int aux_insercion[N];
    copiarArreglo(arreglo, aux_insercion, N);
    start = high_resolution_clock::now();
    insercion(aux_insercion, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Insercion     | " << duration << " milisegundos\n";

    //Selección
    int aux_seleccion[N];
    copiarArreglo(arreglo, aux_seleccion, N);
    start = high_resolution_clock::now();
    seleccion(aux_seleccion, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Seleccion     | " << duration << " milisegundos\n";

    //Shellsort
    int aux_shellsort[N];
    copiarArreglo(arreglo, aux_shellsort, N);
    start = high_resolution_clock::now();
    shellsort(aux_shellsort, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Shellsort     | " << duration << " milisegundos\n";

    //Quicksort
    int aux_quicksort[N];
    copiarArreglo(arreglo, aux_quicksort, N);
    start = high_resolution_clock::now();
    quicksort(aux_quicksort, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Quicksort     | " << duration << " milisegundos\n";

    //Escribe el arreglo si ver == 's'
    if(ver == 's') {
        cout << "------------------------------\n";
        cout << "Burbuja         |";
        printArreglo(aux_burbuja, N);
        cout << "Insercion       |";
        printArreglo(aux_insercion, N);
        cout << "Seleccion       |";
        printArreglo(aux_seleccion, N);
        cout << "Shellsort       |";
        printArreglo(aux_shellsort, N);
        cout << "Quicksort       |";
        printArreglo(aux_quicksort, N);
    }
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
        arreglo[i] = rand() % 100;
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

    ordenamiento_interno(arreglo, N, ver);
    return 0;
}