## Laboratorio 9: Métodos de búsqueda y Hash

## 📘 Descripción general
Este programa implementa una **tabla de hash de 20 posiciones** y resuelve colisiones mediante cuatro métodos de reasignación:
- **L** -> Reasignación lineal
- **C** -> Reasignación Cuadrática
- **D** -> Reasignación por Doble Dirección
- **E** -> Encadenamiento mediante listas ligadas
El conjunto de datos problema es:
    23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64
Cada método muestra cómo maneja la colisión y cómo inserta el dato en la tabla.

---

## 🔢 La función Hash
El programa usa la función hash:
    *H(k) = (k mod 19) + 1
Para ingresar valores en la tabla e identificar la cola asociada.

---

## 🧱 Arquitectura del proyecto
```plaintext
Laboratorio9.cpp
│
├── Estructuras de datos
│    ├── Nodo            → Para almacenar un dato; usado en encadenamineto.
│    └── Cola            → Cada posición de la tabla posee una cola para manejar colisiones en encadenamiento.
│
├── Utilidades
│    ├── printTabla()    → Muestra la tabla hash.
│    ├── printData()     → Imprime los datos problema.
│    └── printCola()     → Muestra las colas ligadas en encadenamiento.
│
├── Función de hash
│    └── funcHash()      → Devuelve posición hash.
│
├── Métodos de reasignación
│    ├── PruebaLineal()          → Avanza secuencialmente en caso de colisión.
│    ├── PruebaCuadratica()      → Usa incrementos I² por iteración.
│    ├── PruebaDobleDireccion()  → Usa doble hash para hallar posiciones vacías.
│    └── PruebaEncadenamiento()  → Inserta nodos en lista ligada (cola).
│
├── Métodos de reasignación
│    └── reasign_data()  → Llama al método correspondiente según argumento L|C|D|E.
│
├── Inserción
│    └── insertData()    → Intenta insertar cada dato secuencialmente.
│
└── main()
     ├── Valida argumento del usuario.
     ├── Inicializa tabla y colas.
     ├── Inserta todos los datos.
     └── Muestra tabla y colas después de cada inserción.
```

---

🧩 Funcionamiento de los métodos

1. **Reasignación lineal (L)**
En caso de colisión, intenta:
```plaintext
    D = 3 //Posición de colisión
    DX = D + 1 //Primera iteración
    DX += 1 //Continúa hasta encontrar un espacio vacío
```

2. **Reasignación cuadrática (C)**
Calcula nuevas posiciones con:
    *DX = H(k) + I<sup>2*
Ejemplo:
```plaintext
    D = 3 //Posición de colisión
    I = 1 -> (3 + (1 * 1)) = 4
    I = 2 -> (3 + (2 * 2)) = 7
    I = 3 -> (3 + (3 * 3)) = 12
```

3. **Reasignación por Doble Dirección (D)**
Usa **una segunda función hash**:
    *DX = ((DX + 1) mod 19) + 1
De esta forma genera un ciclo alternativo.
```plaintext
    D = 3 //Posición de colisión
    DX = ((3 + 1) mod 19) + 1 = 5
    DX = ((5 + 1) mod 19) + 1 = 7
    DX = ((7 + 1) mod 19) + 1 = 9
```

4. **Encadenamiento con listas ligadas (E)**
Cada posición posee una **cola (lista ligada)**
```plaintext
    dato = 64 //Valor a ingresar
    D = 3 //Posición de colisión
    cola[3 - 1] -> 14 -> 81 -> 64 //Inserta '64' con posición '3 - 1' porque la cola tiene su primer elemento en '0'
```
Las inserciones se realizan hacia el final de la lista, razón del manejo en colas.

---

## ⚙️ Instalación
Requisitos:
- Compilador **g++**
- Terminal (Linux, macOS, Windows)

Compilación
```bash
    g++ -Wall Bustamante_Esteban_Act1.cpp -o Act1
```

▶️ Ejecución
El programa requiere un **parámetro obligatorio**:
| Parámetro | Método |
|-----------|--------|
| L | Reasignación Lineal |
| C | Reasignación cuadrática |
| D | Reasignación por Doble Dirección |
| E | Encadenamiento con listas ligadas|

Ejemplo:
```bash
    ./Act1 L
```

---

## 🖨️ Salida esperada
Cada inserción muestra:
- Dato actual.
- Posición hash.
- Colisiones detectadas.
- Estado completo de la tabla.
- Si el parámetro es E muestra las colas por índice.
Ejemplo parcial (real):
```plaintext
Ingreso actual: 80
Colisión en la posición: 5
Colisión en la posición: 6
Mediante reasignación cuadrática, el dato se ingresa en la posición: 9
5 + (2 * 2) = 9
0 43 59 0 23 42 5 0 80 66 81 49 0 28 14 0 0 55 37 0 
```

---

## 🧠 Consideraciones
- Encadenamiento permite almacenar **infinitos** elementos en una misma posición si asi lo indicara la función hash.

---

## 👨‍💻 Autoría

**Esteban Alfonso Bustamante Villarreal**
Pregrado de Ingeniería Civil en Bioinformática
**Universidad de Talca — Facultad de Ingeniería**

---

## 📚 Referencias
- [**Universidad de Talca – Facultad de Ingeniería**. *Algoritmos y Estructuras de Datos*, Tema_9_Busqueda_Interna.pdf]

---

> **Versión:** 1.0.0  
> **Última actualización:** Noviembre 2025  
> **Licencia:** Uso académico y educativo





