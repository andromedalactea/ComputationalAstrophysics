/*
    Este programa genera puntos aleatorios en un cuadrado de lado 100 y calcula los vecinos de un punto de interes
    utilizando una lista enlazada. El programa guarda los puntos generados en un archivo llamado posiciones.dat
    y los vecinos del punto de interes en un archivo llamado vecinos.dat.

    El programa recibe como entrada el número de puntos a generar y el id del punto de interes.

    Para compilar el programa se debe ejecutar el siguiente comando:
    gcc linked_list_algorim.c -o linked_list_algorim_ejecutable.out -lm

    Para ejecutar el programa se debe ejecutar el siguiente comando:
    ./linked_list_algorim_ejecutable.out 

    El programa grafica los puntos generados y los vecinos del punto de interes utilizando el siguiente comando:
    splot [0:100][0:100][0:100] "posiciones.dat" u 2:3:4:(sprintf("%d", $1)) w labels point ps 3 pt 7 lc 1 offset char 1,1 t "puntos","vecinos.dat" u 2:3:4 w p ps 2 pt 7 lc 3 t "primeros vecinos","posiciones.dat" every ::0::0 u 2:3:4 w p ps 2 pt 7 lc 7 t "punto de interes"

*/

// Librerias de C
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Variables globales
#define GRID_SIZE 100
#define TOTAL_CELLS 36 // Debe ser un número que tenga raíz cuadrada entera (En el caso de un cuadrado en la generación de puntos)

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

    // Obteniendo el numero de elementos del arreglo
    printf("Ingrese el numero de puntos:\n");
    scanf("%d",&nPuntos);
    printf("Ingrese el id del punto que quiere ver:\n");
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

  // Inicializa con numeros aleatorios
  for( i=0; i<nPuntos; i++)
    {
        // Generando las posiciónes aleatorias
        points[i].x = drand48()*GRID_SIZE; 
        points[i].y = drand48()*GRID_SIZE;

        // Calculando la celda a la que pertenece el punto
        points[i].cell_x = (int)ceil(sqrt(TOTAL_CELLS)*points[i].x / GRID_SIZE);
        points[i].cell_y = (int)ceil(sqrt(TOTAL_CELLS)*points[i].y / GRID_SIZE);


        // Graba en un archivo los puntos jutnos con su id y celda asignada
        fprintf(fPuntos, "%d %lf %lf %d %d\n", i, points[i].x, points[i].y, points[i].cell_x, points[i].cell_y);
    }
  
  fclose(fPuntos);
}

void calculate_neighbours_linked_list(const int puntoConVecinos, const int nPuntos, PointCell *points)
{
    // Archivo para guardar los vecinos
    FILE *fVecinos = fopen("vecinos.dat", "w");

    // Obteniendo la celda a la que pertenece el punto de interes
    int cell_x = points[puntoConVecinos].cell_x;
    int cell_y = points[puntoConVecinos].cell_y;

    for(int i = 0; i < nPuntos; i++)
    {
        // Si el punto pertenece a la misma celda que el punto de interes o a sus celdas adyacentes
        if( abs(points[i].cell_x - cell_x) <= 1 && abs(points[i].cell_y - cell_y) <= 1 )
        {
            fprintf(fVecinos," %d %lf %lf %d %d\n", i, points[i].x, points[i].y, points[i].cell_x, points[i].cell_y);
        }
    }
}

// Nota : graficar con splot [0:100][0:100][0:100] "posiciones.dat" u 2:3:4:(sprintf("%d", $1)) w labels point ps 3 pt 7 lc 1 offset char 1,1 t "puntos","vecinos.dat" u 2:3:4 w p ps 2 pt 7 lc 3 t "primeros vecinos","posiciones.dat" every ::0::0 u 2:3:4 w p ps 2 pt 7 lc 7 t "punto de interes"