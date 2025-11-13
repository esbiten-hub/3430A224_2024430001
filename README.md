# 🖥️ Métodos de ordenamiento interno

---

## 📘 Descripción general

Este prgrama implementa **cinco algoritmos de ordenamiento interno** y compara sus tiempos de ejecución al ordenar el mismo conjunto de datos aleatorios. La cantidad de datos es ingresada por el usuario, un dato **N**.
Los algoritmos incluidos son:
Método cuadrático (n²):
- Burbuja (Bubble Sort)
- Inserción (Insertion Sort)
- Selección (Selection Sort)

Método logarítmico (log₂ (n)):
- Shellsort
- Quicksort

El programa mide el tiempo de ejecución de cada algoritmo utilizando la función **high_resolution_clock::now()** de la librería **<chrono>** en C++.

---

## 🧩 Arquitectura del proyecto


```plaintext
Laboratorio8.cpp/
│
├── Inclusión de librerías estándar
│    ├── <iostream>    → Entrada y salida de datos.
│    ├── <random>      → Generación de números aleatorios.
│    ├── <chrono>      → Medición de tiempos de ejecución.
│
├── Implementación de algoritmos de ordenamiento
│    ├── burbuja()     → Método cuadrático (n²)
│    ├── insercion()   → Método cuadrático (n²)
│    ├── seleccion()   → Método cuadrático (n²)
│    ├── shellsort()   → Método logarítmico (log₂ (n))
│    ├── quicksort()   → Método logarítmico (log₂ (n))
│    └── reduce()      → Función auxiliar de partición usada por quicksort.
│
├── Funciones auxiliares
│    ├── copiarArreglo() → Copia el contenido de un arreglo en otro.
│    ├── printArreglo()  → Muestra los elementos de un arreglo por consola.
│
├── Conjunto de algoritmos
│    └── ordenamiento_interno()
│         → Llama a cada algoritmo, mide su tiempo con <chrono> y muestra los resultados
│           en una tabla de comparación. Además, imprime los arreglos ordenados si el usuario lo solicita.
│
└── Función principal (main)
     ├── Valida los parámetros ingresados por el usuario (N y ver).
     ├── Genera los datos aleatorios.
     ├── Muestra la cabecera de resultados.
     └── Llama a ordenamiento_interno() para ejecutar las pruebas.

```

---

## 🧩 Funcionalidades principales

✅ Generación automática de datos de pruebas.
    - A partir del parámetro **N** ingresado por el usuario, el programa crea un arreglo de números enteros de tamaño **N** con valores entre el [0, 99]
✅ Ejecución de cinco algoritmos de ordenamiento interno.
    - Cada algoritmo ordena una **copia independiente** del arreglo original.
✅ Medición precisa de tiempos de ejecución.
    - Se utiliza **high_resolution_clock** del módulo **<chrono>** para medir la duración de cada algoritmo con precisión en milisegundos.
✅ Visualización de resultados.
    - Si el usuario ingresa el parámetro 's', se muestra el orden final del arreglo realizado por cada algoritmo.
    - Si el usuario ingresa el parámetro 'n', **solo muestra tiempos de ejecución**.

---

## ⚙️ Instalación

Requisitos mínimos:
- Compilador g++.
- Sistema operativo compatible (Linux, macOS o Windows)
- Terminal para ejecutar el programa.

Clona o descarga el repositorio y ejecuta desde el directorio raíz:

🧱 **Compilación**
Desde una terminal, donde se encuentra el archivo **.cpp**, ejecutar:
```bash
    g++ -Wall Bustamante_Esteban_Act1.cpp -o Act1
```

▶️ **Ejecución**
El programa requiere **dos parámetros** o no inicia:
1. **N**: cantidad de elementos a ordenar (entero positivo).
2. **ver**: indica si se muestran los arreglos (**s** = sí, **n** = no).

**Ejemplos**

**Ejemplo 1 - sin mostrar el contenido de los arreglos.**
 ```bash
    ./Act1 10000 n
```

Salida esperada (real):
```bash
    ------------------------------
    Método         | Tiempo
    ------------------------------
    Burbuja       | 420 milisegundos
    Insercion     | 111 milisegundos
    Seleccion     | 202 milisegundos
    Shellsort     | 6 milisegundos
    Quicksort     | 2 milisegundos

```

**Ejemplo 2 - mostrando arreglos**
 ```bash
    ./Act1 4 s
```

Salida esperada (real):
```bash
    ------------------------------
    Método         | Tiempo
    ------------------------------
    Burbuja       | 0 milisegundos
    Insercion     | 0 milisegundos
    Seleccion     | 0 milisegundos
    Shellsort     | 0 milisegundos
    Quicksort     | 0 milisegundos
    ------------------------------
    Burbuja         |a[0]1 a[1]23 a[2]25 a[3]85 
    Insercion       |a[0]1 a[1]23 a[2]25 a[3]85 
    Seleccion       |a[0]1 a[1]23 a[2]25 a[3]85 
    Shellsort       |a[0]1 a[1]23 a[2]25 a[3]85 
    Quicksort       |a[0]1 a[1]23 a[2]25 a[3]85 

```
---

## 📊 Explicación de las funciones principales
| Función | Descripción |
|---------|-------------|
| burbuja() | Compara pares de elementos adyacentes y los intercambia entre sí. El elemento más pequeño se mueve a la izquierda. |
| insercion() | Ingresa elementos hacia la izquierda en una porción ya ordenada. |
| seleccion() | Busca el elemento más pequeño y lo coloca en orden. |
| shellsort() | Utiliza saltos para comparar elementos distantes entre sí. Gradualmente va reduciendo el intervalo de los altos. |
| quicksort() | Separa de forma iterativa el conjunto en subconjuntos manejados como pilas, donde los elementos a la izquierda de la partición sean menores a X y a la derecha mayores a X. |
| reduce() | Función auxiliar de **quicksort()** que realiza la partición del arreglo. |

---

## 🧠 Consideraciones
- Si el número **N** es pequeño (<1000), los tiempos de algunos algorítmos pueden mostrarse como **0 milisegundos** por la velocidad rápida de ejecución.

---

## 👨‍💻 Autoría

**Esteban Alfonso Bustamante Villarreal**
Pregrado de Ingeniería Civil en Bioinformática
**Universidad de Talca — Facultad de Ingeniería**

---

## 📚 Referencias
- [**Universidad de Talca – Facultad de Ingeniería**. *Algoritmos y Estructuras de Datos*, Tema_7-Busq_Interna-Cuadraticos.pdf y Tema_8-Busq_Interna-Logaritmicos.pdf]

---

> **Versión:** 1.0.0  
> **Última actualización:** Noviembre 2025  
> **Licencia:** Uso académico y educativo