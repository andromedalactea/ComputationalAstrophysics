/*
    Este programa genera puntos aleatorios en un cuadrado de lado 100 y calcula los vecinos de un punto de interes
    utilizando una lista enlazada. El programa guarda los puntos generados en un archivo llamado posiciones.dat
    y los vecinos del punto de interes en un archivo llamado vecinos.dat.

    El programa recibe como entrada el número de puntos a generar y el id del punto de interes.

    Para compilar el programa se debe ejecutar el siguiente comando:
    gcc 2_linked_list_algorim.c -o 2_linked_list_algorim_ejecutable.out -lm

    Para ejecutar el programa se debe ejecutar el siguiente comando:
    ./2_linked_list_algorim_ejecutable.out 

    El programa grafica los puntos generados y los vecinos del punto de interes utilizando el script de gráficación proporcionado,
    que también lo puedes encontrar el final de este archivo.

*/

// Librerias de C
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

// Variables globales
#define GRID_SIZE 100 // Tamaño del cuadrado en el que se generan los puntos
#define TOTAL_CELLS 36 // Debe ser un número que tenga raíz cuadrada entera (En el caso de un cuadrado en la generación de puntos)
#define h 18 // Distancia de máxima de los puntos vecinos 

// Define la estructura de un punto junto con su celda correspondiente
typedef struct point_cell {
    double x;
    double y;
    int cell_x;
    int cell_y;
} PointCell;

// Prototipos de funciones
void initialize_positions(const int , PointCell *);
void calculate_cell(double x, double y);
void calculate_neighbours_linked_list(const int, const int, PointCell *);

// Funcion principal
void main(void)
{
    int nPuntos, nVecinos, puntoConVecinos;

    // Define el numero de puntos
    nPuntos = 1000;

    // Define el punto de interes
    printf("Ingrese el id del punto que quiere ver (El script de gráficación esta predeterminado para el punto 10):\n");
    scanf("%d",&puntoConVecinos);

    // Definiendo los arreglos
    PointCell points[nPuntos];

    // Inicializa el arreglo de puntos
    initialize_positions(nPuntos, points);
  
    // Calcula los vecinos del punto de interes
    calculate_neighbours_linked_list(puntoConVecinos, nPuntos, points);
} // Fin de la funcion principal

// Esta funcion inicializa las coordenadas x, y de cada punto junto con su celda asignada

void initialize_positions(const int nPuntos, PointCell *points)
{
  int i;

  FILE *fPuntos = fopen("posiciones.dat","w");

  // Inicializar la semilla del generador de números aleatorios con el tiempo actual
  srand48(time(NULL));

  // Inicializa con números aleatorios
  for (i = 0; i < nPuntos; i++)
  {
    // Generando las posiciones aleatorias
    points[i].x = drand48() * GRID_SIZE;
    points[i].y = drand48() * GRID_SIZE;

    // Calculando la celda a la que pertenece el punto
    points[i].cell_x = (int)ceil(sqrt(TOTAL_CELLS) * points[i].x / GRID_SIZE);
    points[i].cell_y = (int)ceil(sqrt(TOTAL_CELLS) * points[i].y / GRID_SIZE);

    // Graba en un archivo los puntos junto con su id y celda asignada
    fprintf(fPuntos, "%d %lf %lf %d %d\n", i, points[i].x, points[i].y, points[i].cell_x, points[i].cell_y);
  }

  fclose(fPuntos);
}


void calculate_neighbours_linked_list(const int puntoConVecinos, const int nPuntos, PointCell *points)
{
    // Archivo para guardar los vecinos
    FILE *fVecinos = fopen("vecinos.dat", "w");

    // Obteniendo las coordenadas del punto de interes
    float x = points[puntoConVecinos].x;
    float y = points[puntoConVecinos].y;

    // Obteniendo la celda a la que pertenece el punto de interes
    int cell_x = points[puntoConVecinos].cell_x;
    int cell_y = points[puntoConVecinos].cell_y;

    for(int i = 0; i < nPuntos; i++)
    {
        // Si el punto pertenece a la misma celda que el punto de interes o a sus celdas adyacentes y además esta a menos de una distancia h
        if( abs(points[i].cell_x - cell_x) <= 1 && abs(points[i].cell_y - cell_y) <= 1 )
        {
            // Calcula la distancia entre los puntos solo los de las celdas vecinas
            double distance = sqrt(pow(points[i].x - x, 2) + pow(points[i].y - y, 2));
            if (distance < h)
            {
                // Graba en un archivo los vecinos del punto de interes
                fprintf(fVecinos," %d %lf %lf %d %d\n", i, points[i].x, points[i].y, points[i].cell_x, points[i].cell_y);
            }
        }
    }
}


// Script de graficación
/*
reset
set term pngcairo size 900,600    
set output 'grafico.png'          

# Establecer rangos y etiquetas de ejes
set xrange [0:100]
set yrange [0:100]
set xlabel 'Eje X' offset 0,0.1
set ylabel 'Eje Y' offset 2,0

# Título del gráfico
set title "Vecinos de un punto dado con el algoritmo Linked List"

# Establecer el grid con celdas de 12.5x12.5, líneas moradas, continuas y gruesas
set xtics 16.6666
set ytics 16.6666
set format x "%0.0f"  # Formato para redondear a entero más cercano en eje X
set format y "%0.0f"  # Formato para redondear a entero más cercano en eje Y
set grid xtics ytics lc rgb 'purple' lt 1 lw 2

# Configurar la leyenda para que esté fuera del área de graficación
set key outside right top vertical Right noreverse enhanced autotitles box lt black linewidth 1.0

plot 'posiciones.dat' using 2:3 with points pt 7 lc rgb 'blue' title 'Todos los puntos', \
     'vecinos.dat' using 2:3 with points pt 7 lc rgb 'red' title 'Vecinos', \
     'posiciones.dat' using ($1 == 10 ? $2 : 1/0):($1 == 10 ? $3 : 1/0) with points pt 7 lc rgb 'green' title 'Punto de interés'


IMPORTTANTE: Para cambiar el punto de interés, se debe modificar el valor de $1 == 10 (ambos) por el id del punto deseado. y para el cual se hizo la ejecución del programa.
*/