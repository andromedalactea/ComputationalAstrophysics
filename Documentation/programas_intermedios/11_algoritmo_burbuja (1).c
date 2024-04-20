
/*

Este codigo implementa el algoritmo de la burbuja para encontrar
los primeros n vecinos a cada punto en una distribucion de puntos
aleatoria
 */

// Librerias de C
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Variables globales
double limDistancia = 100.0;

// prototipos de funciones
int inicializa_posiciones(const int ,double *, double *, double *);
int calcula_distancia(const int nPuntos, double x[], double y[], double z[], int indices_ordenados[]);
int calcula_primeros_vecinos_burbuja(const int nPuntos, double distancia[], int indices_ordenados[]);

// Funcion principal
int main(void)
{

  int nPuntos;
  
  // Obteniendo el numero de elementos del arreglo
  printf("Ingrese el numero de puntos:\n");
  scanf("%d",&nPuntos);

  // definiendo los arreglos
  double x[nPuntos], y[nPuntos], z[nPuntos];
  int indices_ordenados[nPuntos];

  // inicializa los arreglos de posicion
  inicializa_posiciones(nPuntos, x, y, z);
  // calcula distancia y los primeros n vecinos
  calcula_distancia(nPuntos, x, y, z, indices_ordenados);

  return 0;
} // fin de la funcion principal

// Esta funcion inicializa las coordenadas x, y e z de cada punto usando 
// numeros aleatorios obtenidos con drand48 entre 0 y limDistancia
int inicializa_posiciones(const int nPuntos, double x[], double y[], double z[])
{
  int i;

  FILE *fPuntos = fopen("posiciones.dat","w");

  // inicializa con numeros aleatorios
  for( i=0; i<nPuntos; i++)
    {
      x[i] = drand48()*limDistancia;
      y[i] = drand48()*limDistancia;
      z[i] = drand48()*limDistancia;
      // graba en un archivo los puntos
      fprintf(fPuntos,"%d %lf %lf %lf\n",i,x[i],y[i],z[i]);
    }
  
  fclose(fPuntos);

  return 0;
}
/*
Esta funcion calcula las distancias punto a punto del sistema
y hace un llamado a la funcion que hace el ordenamiento de burbuja
para ordenar la distancia de menor a mayor respecto al origen
*/

int calcula_distancia(const int nPuntos, double x[], double y[], double z[], int indices_ordenados[])
{
  int i;
  double distancia[nPuntos], distancia_original[nPuntos];

  // Calcula la distancia al origen
  printf("Inicial\n");
  for( i=0; i<nPuntos; i++ )
    {
      distancia_original[i] = distancia[i] = sqrt( x[i]*x[i]+ y[i]*y[i] + z[i]*z[i] );
      printf("%d %lf\n",i,distancia[i]);
    }

  // Ordena las distancias con algoritmo de burbuja
  calcula_primeros_vecinos_burbuja(nPuntos, distancia,indices_ordenados);
  

  // Imprime la distancia ordenada de menor a mayor
  printf("\nfinal\n");
  for( i=0; i<nPuntos; i++ )
    printf("%d %d %10.4lf %10.4lf %10.4lf\n",
    i,
	   indices_ordenados[i],
	   distancia[i],distancia_original[i],
	   distancia_original[indices_ordenados[i]]);

  return 0;
}

// Esta funcion ordena de mayor a menor las distancia de un conjunto de puntos al origen 
int calcula_primeros_vecinos_burbuja(const int nPuntos, double distancia[], int indices_ordenados[])
{
  int i, j, almacena_indice;
  double almacena_distancia;
  
  // Inicializa los indices
  for( i=0; i<nPuntos; i++ )
    indices_ordenados[i] = i;
  
  for( i=0; i<nPuntos; i++ ) // ciclo que controla el numero de veces que se recorre el vector
    for( j=0; j<nPuntos-1; j++ ) // ciclo que recorre el arreglo
      {
    	// Compara los elementos adyasentes y los intercambia
    	// Si el primero es mayor que el segundo
	      if( distancia[j] > distancia[j+1]  )
	        {
	          // Ordenamiento burbuja
	          almacena_distancia = distancia[j];
	          distancia[j]  = distancia[j+1];
	          distancia[j+1] = almacena_distancia;
	    
	          // Ordena indices
	          almacena_indice = indices_ordenados[j];
	          indices_ordenados[j] = indices_ordenados[j+1];
	          indices_ordenados[j+1] = almacena_indice;        
	        }
      }
  
  return 0;
}

// Nota : graficar con plot "posiciones.dat" u 2:3:(sprintf("%d", $1)) w labels point ps 2 pt 7 offset char 1,1
// o splot "posiciones.dat" u 2:3:4:(sprintf("%d", $1)) w labels point ps 2 pt 7 offset char 1,1
