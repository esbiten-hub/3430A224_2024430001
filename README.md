Se recomienda tener instalado el visor de imágenes eog.
Compilar el codigo con: g++ -Wall Bustamante_Esteban_Lab4.cpp -o Lab4 y ejecutar el compilado con ./Lab4

Inicialmente el programa pide crear el árbol, al menos la raíz de este. Esta instancia consta de un set de valores para verificar que no se repitan números durante la creación.
Luego se accede al menú que consta de 5 funciones:
Insertar -> agrega un número al árbol moviendose a los hijos izquierdos o derechos según el tamaño del número.
Eliminar -> busca el número a eliminar, lo reemplaza considerando tres casos:
  Si tiene hijo izquierdo - Si tiene hijo derecho - Si tiene ambos hijos.
Modificar -> busca el número a modificar y reemplaza su valor.
  Esta función no considera el reordenamiento del árbol si rompe la regla que considera que:
    Valor menor al raíz -> hijo izquierdo
    Valor mayor al raíz -> hijo derecho
  Recorrer árbol -> Escribe recorrido en Preorden, Inorden y Postorden.
  Generar grafo -> Guarda un .txt y .png del árbol.
