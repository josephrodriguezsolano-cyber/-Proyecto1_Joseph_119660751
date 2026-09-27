# Tetris con Estructuras de Datos Lineales

Proyecto I del curso EIF207 Estructuras de Datos, II Ciclo 2026, Universidad Nacional de Costa Rica, Sede Regional Brunca (Campus Pérez Zeledón y Campus Coto). Estudiante: Joseph Emmanuel Rodríguez Solano, carné 119660751.

## 1. Descripción del Proyecto
Este proyecto es una versión interactiva del juego Tetris desarrollada en C++ con la biblioteca gráfica SFML 2.5+. El objetivo central fue implementar toda la lógica del juego utilizando únicamente estructuras de datos lineales creadas desde cero. Toda la asignación y liberación de memoria se realiza manualmente con punteros mediante new y delete, asegurando que no queden fugas de memoria al cerrar la aplicación o reiniciar partidas. La interfaz gráfica está separada de la capa de datos, comunicándose únicamente mediante variables básicas como coordenadas y números enteros.

## 2. Estructuras de Datos Implementadas
Para resolver cada mecánica del juego se implementaron las siguientes estructuras dinámicas:

Cola de piezas: Una cola dinámica basada en nodos y punteros frente y fin que gestiona la secuencia de tetrominós mediante el sistema de bolsas de 7 piezas aleatorias. Permite encolar y desencolar en tiempo constante O(1), además de consultar en pantalla las siguientes tres piezas que van a salir sin alterar el orden de la cola.

Pila de espera (Hold): Una pila dinámica con capacidad fija de un elemento que permite guardar la pieza activa para intercambiarla más adelante. Sus operaciones de inserción y extracción funcionan en tiempo O(1).

Historial y repetición (Replay): Una lista doblemente enlazada con punteros al nodo anterior y siguiente. Guarda cada movimiento de la pieza (posiciones, rotación y tipo) como datos numéricos simples. Permite deshacer con la tecla Z y rehacer con la tecla X en tiempo O(1) durante la partida, y recorrer toda la partida paso a paso o en reproducción automática al perder.

Cola de eventos: Una lista enlazada que inserta cada evento de forma ordenada según su tiempo de disparo (aumentos de velocidad, niveles y temporizadores de destello). Como los eventos se acomodan en su lugar cronológico al momento de insertarse, el evento más próximo siempre queda en la cabeza, permitiendo revisarlo y despacharlo en tiempo O(1) durante cada ciclo del juego.

Tablero de juego: Una lista enlazada compuesta por 20 nodos de fila, donde cada nodo contiene internamente un arreglo de 10 celdas. Cuando una fila se completa, el nodo se desenlaza de la lista y se libera de memoria con delete en tiempo O(1), y luego se inserta un nodo de fila vacía al inicio de la lista en O(1). Con esto las filas superiores bajan sin necesidad de mover valores celda por celda como en una matriz tradicional.

Gestor de puntajes y ordenamiento: Administra los registros de los 10 mejores puntajes almacenados en archivo. Se programaron manualmente dos algoritmos de ordenamiento: Inserción (O(n²)) y QuickSort (O(n log n)), permitiendo alternar cuál se usa para ordenar la tabla.

## 3. Requisitos y Entorno
El proyecto fue programado y probado en el entorno ZinjaI con el compilador MinGW GCC (C++14) en Windows. Requiere tener instalada la biblioteca SFML 2.5 (módulos graphics, window y system). Para que el programa abra correctamente fuera del IDE, los archivos DLL de SFML y la carpeta de recursos con las fuentes tipográficas deben encontrarse en la misma carpeta que el archivo ejecutable.

## 4. Instrucciones de Compilación y Ejecución
La forma directa de compilar y probar el proyecto es utilizando ZinjaI:
1. Abrir ZinjaI.
2. Ir a Archivo, elegir Abrir Proyecto y seleccionar el archivo del proyecto (ProyectoTetrisJosephRodriguez.zpr).
3. Asegurarse de que el perfil seleccionado sea Debug_Win32 o Release_Win32.
4. Presionar la tecla F9 para compilar y ejecutar el juego automáticamente.

## 5. Controles del Juego

Durante la partida:
Las flechas Izquierda y Derecha mueven la pieza a los lados. La flecha Arriba rota la pieza en sentido horario usando las 4 posiciones fijas precalculadas. La flecha Abajo acelera la caída y la Barra Espaciadora hace la caída instantánea al fondo. La tecla C envía la pieza activa a la casilla de espera o la intercambia si ya hay una guardada. La tecla Z deshace el movimiento anterior y la tecla X lo rehace. La tecla T cambia el algoritmo con el que se ordena el marcador de puntajes (Inserción o QuickSort). La tecla Escape abre el menú de pausa.

Menú de pausa:
Con las flechas Arriba y Abajo se eligen las opciones en pantalla (continuar jugando, reiniciar la partida o salir). Se confirma la opción con la tecla Enter o Espacio, y se puede regresar al juego presionando Escape nuevamente.

Pantalla de Game Over y Replay:
Al perder la partida, la Barra Espaciadora inicia o detiene la repetición automática. Las flechas Izquierda y Derecha permiten retroceder y avanzar la partida paso por paso. La tecla Inicio (o la letra I) regresa al primer movimiento de la partida y la tecla Fin (o la letra F) salta al último paso registrado. La tecla H oculta o muestra el cuadro de mejores puntajes para poder ver el tablero limpio, y la tecla R reinicia una partida nueva.
