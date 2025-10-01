#include <iostream>
#include <cstring>
using namespace std;

struct PACIENTE {
    string nombre;
    int edad;
    int peso;
    float altura;
};

//Crea paciente con los atributos entregados
PACIENTE creaPaciente(string nombre, int edad, int peso, float altura) {
    PACIENTE newPaciente;
    newPaciente.nombre = nombre;
    newPaciente.edad = edad;
    newPaciente.peso = peso;
    newPaciente.altura = altura;
    return newPaciente;
}

void printPacientes(PACIENTE p1, PACIENTE p2, PACIENTE p3) {
    cout << "Pacientes ingresados:\n";
    cout << "Nombre: " << p1.nombre << ". Edad: " << p1.edad << ". Peso: " << p1.peso << ". Altura: " << p1.altura << ".\n";
    cout << "Nombre: " << p2.nombre << ". Edad: " << p2.edad << ". Peso: " << p2.peso << ". Altura: " << p2.altura << ".\n";
    cout << "Nombre: " << p3.nombre << ". Edad: " << p3.edad << ". Peso: " << p3.peso << ". Altura: " << p3.altura << ".\n";
}

int main() {
    PACIENTE p1, p2, p3;

    p1 = creaPaciente("Esteban", 19, 73, 1.78);
    p2 = creaPaciente("Benjamin", 19, 70, 1.80);
    p3 = creaPaciente("Hector", 21, 100, 1.70);

    printPacientes(p1, p2, p3);

    return 0;
}

