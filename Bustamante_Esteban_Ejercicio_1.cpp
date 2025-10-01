#include <iostream>
#include <string>
using namespace std;

struct PACIENTE {
    string nombre;
    int edad;
    int peso;
    float altura;
};

PACIENTE creaPaciente(string nombre, int edad, int peso, float altura) {
    PACIENTE newPaciente;
    newPaciente.nombre = nombre;
    newPaciente.edad = edad;
    newPaciente.peso = peso;
    newPaciente.altura = altura;
    return newPaciente;
}

void escribirPaciente(PACIENTE paciente) {
    cout << "Nombre: " << paciente.nombre << ". Edad: " << paciente.edad << ". Peso: " << paciente.peso << ". Altura: " << paciente.altura << ".\n";
}

int main() {
    //Ingresa pacientes al arreglo
    PACIENTE pacientes[3] = {
        creaPaciente("Esteban", 19, 73, 1.78),
        creaPaciente("Benjamin", 19, 70, 1.80),
        creaPaciente("Hector", 21, 100, 1.70)
    };

    cout << "---- Pacientes registrados ----\n";
    for(int i = 0; i < 3; i++) {
        escribirPaciente(pacientes[i]);
    }

    return 0;
}