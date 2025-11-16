#include <iostream>

using namespace std;

struct Nodo {
    int data; //valor almacenado
    Nodo* Siguiente; //puntero al valor almacenado por colision
};

//cada posición de la tabla tiene una cola asociada 
struct Cola {
    Nodo* frente;
    Nodo* final;
};


void printTabla(int arreglo[]) {
    for(int i = 0; i < 20; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

void printData(int arreglo[]) {
    for(int i = 0; i < 15; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

//Imprime la cola usada en el método de Encadenamiento
void printCola(Cola cola) {
    Nodo* aux = cola.frente;
    while(aux != NULL) {
        cout << aux->data << " ";
        aux = aux->Siguiente;
    }
    cout << endl;
}

//Función de hash
int funcHash(int data) {
    int pos;
    pos = (data % 19) + 1;
    return pos;
}

//Método de reasignación lineal
void PruebaLineal(int data, int tabla[]) {
    int DX = funcHash(data) + 1;
    int K = data;

    while(true) {

        //Forma de ciclar un arreglo lineal
        if(DX == 20) {
            DX = 1;
        }

        //Casilla vacía -> inserta
        if(tabla[DX - 1] == 0) {
            cout << "Mediante reasignación lineal, el dato se ingresa en la posición: " << DX << endl;
            tabla[DX - 1] = K;
            break;
        } else {
            //Avanzar siguiente casilla
            cout << "Colisión en la posición: " << DX << endl;
            DX += 1;
        }
    }
}

//Función auxiliar para reasignación cuadrática
//Mantiene DX dentro del rango de la tabla, es una forma de ciclar el arreglo
int ajusteDX(int DX) {
    while(DX >= 20) {
        DX -= 20;        
    }
    return DX;
}

//Método de reasignación cuadrática
void PruebaCuadratica(int data, int tabla[]) {
    int K = data;
    int D = funcHash(data);

    //Primer iteración
    int I = 1;
    int DX = (D + (I * I));

    while(true) {

        //Ciclar el arreglo
        if(DX >= 20) {
            DX = ajusteDX(DX);
        }
        
        //Casilla vacía -> inserta
        if(tabla[DX - 1] == 0) {
            cout << "Mediante reasignación cuadrática, el dato se ingresa en la posición: " << DX << endl;
            cout << D << " + (" << I << " * " << I << ") = " << DX << endl;
            tabla[DX - 1] = K;
            break;
        } else {
            //Colisión -> incrementa el cuadrado
            cout << "Colisión en la posición: " << DX << endl;
            I += 1;
            DX = (D + (I * I));
        }
    }
}

//Método de reasignación doble
void PruebaDobleDireccion(int data, int tabla[]) {
    int K = data;
    int D = funcHash(data);

    //Primera iteración
    cout << "Evaluar posición: ((" << D << " + 1) % 19) + 1 = ";
    int DX = ((D + 1) % 19) + 1;
    cout << DX << endl;

    while(true) {
        if(tabla[DX - 1] == 0) {
            cout << "Mediante reasignación doble, el dato se ingresa en la posición: " << DX << endl;
            tabla[DX - 1] = K;
            break;
        } else {
            cout << "Colisión en la posición: " << DX << endl;
            cout << "Evaluar posición: ((" << DX << " + 1) % 19) + 1 = ";
            DX = ((DX + 1) % 19) + 1;
            cout << DX << endl;
        }
    }
}

//Método de Encadenamiento
void PruebaEncadenamiento(int data, Cola colas[], int tabla[]) {
    int K = data;
    int D = funcHash(data);

    cout << "Posición de colisión actual " << D << endl;

    //Inserta al final de la cola
    Nodo* nuevo = new Nodo();
    nuevo->data = K;
    nuevo->Siguiente = NULL;
    colas[D - 1].final->Siguiente = nuevo;
    colas[D - 1].final = nuevo;
}

//Llama a los métodos de reasignación según el parámetro ingresado en 'reasign'
void reasign_data(int data, int tabla[], char reasign, Cola colas[]) {
    if(reasign == 'L') {
        PruebaLineal(data, tabla);

    } else if(reasign == 'C') {
        PruebaCuadratica(data, tabla);

    } else if(reasign == 'D') {
        PruebaDobleDireccion(data, tabla);

    } else if(reasign == 'E') {
        PruebaEncadenamiento(data, colas, tabla);
    }
}

//Inserta un dato en la tabla
bool insertData(int data, int tabla[], Cola colas[], char reasign) {
    int hashPos;
    hashPos = funcHash(data);

    cout << "Ingreso actual: " << data << endl;

    if(tabla[hashPos - 1] == 0) {
        tabla[hashPos - 1] = data;
        
        //Si reasign == 'E' crea la referencia a la cola
        if(reasign == 'E') {
            Cola cola;
            Nodo* nuevo = new Nodo();
            nuevo->data = data;
            nuevo->Siguiente = NULL;
            cola.frente = nuevo;
            cola.final = nuevo;
            colas[hashPos - 1] = cola;
        }

        cout << "El dato se ingresa en la posición: " << hashPos << endl;
        return true;
    } else {
        cout << "Colisión en la posición: " << hashPos << endl;
        return false;
    }
}

int main(int argc, char *argv[]) {
    //Valida cantidad de argumentos
    if(argc != 2) {
        cout << "Debe ingresar un argumento (L|C|D|E)\n";
        return 0;
    }
    //Valida el argumento
    char reasign = argv[1][0];
    if(reasign != 'L' && reasign != 'C' && reasign != 'D' && reasign != 'E') {
        cout << "El argumento debe ser (L|C|D|E)\n";
        return 0;
    }

    //Arreglo de datos
    int data[15] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};
    int tabla[20];

    //Crea e inicializa las colas
    Cola colas[20];
    for(int i = 0; i < 20; i++) {
        Cola cola;
        cola.frente = NULL;
        cola.final = NULL;
        colas[i] = cola;
    }

    //Inicializa la tabla
    for(int i = 0; i < 20; i++) {
        tabla[i] = 0;
    }

    cout << "Se ingresarán los siguientes datos: " << endl;
    printData(data);

    //Inserción de todos los datos secuencialmente
    for(int i = 0; i < 15; i++) {
        if(!insertData(data[i], tabla, colas, reasign)) {
            //Si hubo colisión llama a los métodos de reasignación
            reasign_data(data[i], tabla, reasign, colas);
        }

        //Muestra el estado de la tabla
        printTabla(tabla);
        //Si reasign == 'E' muestra el estado de las colas
        if(reasign == 'E') {
            for(int i = 0; i < 20; i++) {
            cout << "[" << i + 1 << "] ";
            printCola(colas[i]);
            }
        }
        cout << "\n";
    }
}