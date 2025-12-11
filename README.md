# Alineamiento Global de Secuencias ADN — Needleman–Wunsch
### Programa en C++ con generación de visualizaciones (Graphviz)

---

## 📘 Descripción general
Este programa implementa el **algoritmo de Needleman-Wunsch** para realizar alineamientos globales entre dos secuencias de ADN.
Incluye:
- Lectura de archivos FASTA.
- Lectura de una matriz de similitud U (4x4).
- Penalización de gaps (V).
- Construcción de la matriz de puntuación f.
- Backtracking para obtener el alineamiento.
- Cálculo de:
    - % identidad excluyendo gaps
    - % identidad incluyendo gaps
    - Cobertura del alineamiento
- Exportación de:
    - Un grafo del alineamiento (alineamiento.dot → alineamiento.png)
    - La cuadrícula de puntuaciones y recorrido (cuadricula.dot → cuadricula.png)

---

## 🧱 Arquitectura del proyecto
 
```plaintext
Proyecto/
│
├── Lectura de datos
│   ├── leerFasta()        → Lee y limpia archivos FASTA.
│   ├── leer_funU()        → Lee la matriz de similitud U.
│   └── asignaNucleotido() → Convierte A, C, G y T a índices 0–3.
│
├── Funciones de similitud
│   ├── valor_de_similitud()  → Devuelve U[base1][base2].
│   └── muestraMatrizSimilitud() → Imprime la matriz U.
│
├── Algoritmo principal
│   └── algoritmo_NeedlemanWunsch()
│        → Rellena la matriz f (m+1 × n+1) con:
│             f[i][j] = max(diagonal, arriba, izquierda)
│
├── Backtracking y resultados
│   ├── backtracking()     → Reconstruye alineamiento.
│   ├── muestraAlineamiento() → Imprime alineamiento por bloques.
│   └── muestraSimilitud() → Calcula identidad y cobertura.
│
├── Visualización (Graphviz)
│   ├── alineamientoGraphviz() → Grafica matches/mismatches/gaps.
│   └── cuadriculaGraphviz()   → Genera grilla completa + flechas del recorrido.
│
└── main()
    ├── Valida parámetros.
    ├── Lee FASTA y matriz U.
    ├── Ejecuta Needleman–Wunsch.
    ├── Imprime alineamiento y resultados de similitud.
    └── Genera archivos .dot y .png con Graphviz.
```

---

## ⚙️ Parámetros y ejecución

### 🔧 Compilación

```bash
g++ -Wall proyecto_Bustamante_Esteban.cpp -o proyecto
```

### ▶️ Ejecución
El pograma requiere de **4 parámetros obligatorios**, cada uno con una bandera:

|-Parámetro-|-Descripción-|
|-|-|
| -C1 <archivo> | Secuencia FASTA 1 |
| -C2 <archivo> | Secuencia FASTA 2 |
| -U <archivo> | Matriz de similitud U (4x4) |
| -V <valor> | Penalización por gap |

Ejemplo:
```bash
./proyecto -C1 cad1.fasta -C2 cad2.fasta -U U.txt -V -2
```

Cabe destacar que los archivos **.fasta** pueden ser **.txt** u otro, mientras el interior tenga formato fasta no habrá error.

Después de ejecutar, se generarán:
- alineamiento.dot y alineamiento.png
- cuadricula.dot y cuadricula.png

---

## 📊 Explicación del funcionamiento

### 1️⃣ Lectura FASTA

- Ignora encabezados (**>id**).
- Elimina espacios, tabs y saltos de línea.
- Ensambla secuencias de A, C, T y G filtrando caracteres invisibles.

### 2️⃣ Matriz de similitud U

Formato con valores de ejemplo:
```plaintext
   A  C  G  T
A  1 -1 -1 -1
C -1  1 -1 -1
G -1 -1  1 -1
T -1 -1 -1  1
```

Se asigna a una **matriz U (4x4)**.

### 3️⃣ Construcción de matriz f

Se aplica **Needleman-Wunsch**:
```plaintext
f[i][j] = max(
    f[i-1][j-1] + U[T[i-1]][S[j-1]],   // diagonal → match/mismatch
    f[i-1][j]   + V,                   // arriba   → gap en S
    f[i][j-1]   + V                    // izquierda→ gap en T
)
```

### 4️⃣ Backtracking

Comienza desde **f[m][n]** y recorre hacia:
- 🟥 diagonal → match / mismatch
- 🟦 arriba → gap en secuencia S
- 🟦 izquierda → gap en secuencia T

El resultado final son dos cadenas alineadas con **|** en caso de match y **-** en caso de gap.

### 5️⃣ Resultados de similitud

El programa calcula:

- Identidad sin gaps: solo bases comparables (T vs T, G vs A, etc.)
- Identidad sin gaps: match respecto al ancho total del alineamiento.
- Cobertura: (posicioón sin gaps) / (ancho del alineamiento)

Ejemplo:

```bash
% Identidad (excluyendo gaps) 93%
% Identidad (incluyendo gaps) 91%
Cobertura: 97%
```

---

## 📷 Visualización (Graphviz)

### 📌 **alineamiento.png**

- Cada carácter es un nodo.
- **Verde** = match
- **Rojo** = mismatch
- **Gris** = gap

### 📌 **cuadricula.png**

- Una grilla completa muestra cada valor de **f[i][j]**.
- **Flechas rojas** → movimientos diagonales (matches/mismatches).
- **Flechas azules** → movimientos desde arriba/izquierda.
- Representación visual del camino recorrido.

---

## 👨‍💻 Autoría

**Esteban Alfonso Bustamante Villarreal**  
Pregrado de Ingeniería Civil en Bioinformática  
**Universidad de Talca — Facultad de Ingeniería**  

---

## 📚 Referencias

- [Algoritmo de Needleman-Wunsch]
- [Documentación Graphviz]

---

> **Versión:** 1.0.0  
> **Última actualización:** Diciembre 2025  
> **Licencia:** Uso académico y educativo

