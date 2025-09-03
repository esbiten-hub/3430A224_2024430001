#include <iostream>
#include <cstring>
using namespace std;

//Estructura Paciente
struct PACIENTE {
    string nombre;
    int edad;
    int peso;
    float altura;
    PACIENTE *next;
};

PACIENTE* creaPaciente(char *nombre, int edad, int peso, float altura) {
    PACIENTE *newPaciente = (PACIENTE*)malloc(sizeof(PACIENTE));
    newPaciente->nombre = nombre;
    newPaciente->edad = edad;
    newPaciente->peso = peso;
    newPaciente->altura = altura;
    newPaciente->next = NULL;
    return newPaciente;
}

void addPaciente(PACIENTE **head, PACIENTE *newPaciente) {
    if(*head == NULL) {
        *head = newPaciente;
    } else {
        PACIENTE *current = *head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newPaciente;
    }
}

void printPacientes(PACIENTE *head) {
    cout << "Lista de pacientes: " << endl;
    PACIENTE *current = head;
    while(current != NULL) {
        cout << "Nombre: " << current->nombre << ". Edad: " << current->edad << ". Peso: " << current->peso << ". Altura: " << current->altura << ".\n";
        current = current->next;
    }
}

void freePacientes(PACIENTE *head) {
    PACIENTE *current = head;
    while(current != NULL) {
        PACIENTE *next = current->next;
        free(current);
        current = next;
    }
}

int main() {

    PACIENTE* creaPaciente(char *name, int edad, int peso, float altura);

    PACIENTE *head = NULL;
    PACIENTE *newPaciente;

    newPaciente = creaPaciente("Esteban", 19, 73, 1.76);
    addPaciente(&head, newPaciente);
    newPaciente = creaPaciente("Benjamin", 19, 70, 1.80);
    addPaciente(&head, newPaciente);
    newPaciente = creaPaciente("Hector", 21, 100, 1.70);
    addPaciente(&head, newPaciente);

    printPacientes(head);

    freePacientes(head);
    
    return 0;
}