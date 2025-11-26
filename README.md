## Laboratorio 10: Automatización en conteo de residuos cargados en proteínas (PDB) y almacenamiento en .csv

## 📘 Descripción general
Este script en **BASH** procesa tres archivos de estructura proteica en formato **PDB** y genera un archivo **CSV** con el conteo de átomos **CA** de cada residuo aminoacídico perteneciente a:

**Residuos analizados:**
- LYS / ARG / HIS / GLU / ASP

**Proteínas PDB:**
- HEM_A.pdb
- GFP_A.pdb
- ACE2_A.pdb

El resultado es una tabla **CSV** con el conteo de las veces que aparece cada residuo en las tres proteínas, considerando unicamente el **Carbono Alfa (CA)**.

---

## 🔢 Procesamiento del script
El procesamiento se lleva a cabo por un ciclo **for** que reconoce cada archivo y residuo aminoacídico por medio de variables.
Cada residuo de la lista:
1. Se registra su nombre en la primera columna del CSV.
2. Para cada proteína:
- Se buscan las líneas que contengan **"CA"** y el nombre el residuo.
- Se cuentan con **wc -l**.
3. Se agrega el conteo a la columna correspondiente.

**Ejemplo de búsqueda**
```bash
grep "CA" HEM_A.pdb | grep "LYS" | wc -l
```
Retorna el número de residuos **LYS** en átomos **CA**.

El **output** finalmente es:
```plaintext
residuos_cargados.csv
```

---

## 🧱 Arquitectura del proyecto
```plaintext
laboratorio10.bash
│
├── Estructuras proteicas
│   ├── HEM_A.pdb      
│   ├── GFP_A.pdb      
│   └── ACE2_A.pdb  
│
├── Listas internas
│   ├── archivos_fuente[] → Archivos proteicos
│   └── residuos[]        → Residuos cargados
│
├── Procesamiento
│   ├── Búsqueda con grep → Filtra residuo + CA.
│   ├── Conteo con wc -l  → Cuenta coincidencias por proteína.
│   └── Construcción CSV  → Escribe encabezado y filas.
│
└── Salida
    └── residuos_cargados.csv
```

---

## 🖨️ Salida esperada
El CSV utiliza columnas separadas por **;**:

| aas | HEM | GFP | ACE2 |
|-|-|-|-|
| **LYS** | # | # | # |
| **ARG** | # | # | # |
| **HIS** | # | # | # |
| **GLU** | # | # | # |
| **ASP** | # | # | # |

---

## ⚙️ Instalación
Requisitos:
- **bash** (Linux, macOS, WSL, Git Bash)
- Archivos **PDB** en el mismo directorio del script.

Permisos:
```bash
chmod +x laboratorio10.bash
```
---

▶️ Ejecución
Ubicado en el mismo directorio del script y los archivos **.pdb**, ejecutar:
```bash
./laboratorio10.bash
```

Salida generada:
```bash
residuos_cargados.csv
```

---

## 👨‍💻 Autoría

**Esteban Alfonso Bustamante Villarreal**
Pregrado de Ingeniería Civil en Bioinformática
**Universidad de Talca — Facultad de Ingeniería**

---

## 📚 Referencias
- PDB Format - *Protein Data Bank Documentation*

---

> **Versión:** 1.0.0  
> **Última actualización:** Noviembre 2025  
> **Licencia:** Uso académico y educativo





