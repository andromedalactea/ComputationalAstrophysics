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
int puntoConVecinos;
double limDistancia = 100.0;

// Prototipos de funciones
int inicializa_posiciones(const int ,double *, double *, double *);
int calcula_distancia(const int nPuntos, double x[], double y[], double z[], const int nVecinos, int indices_ordenados[][nVecinos]);
int calcula_primeros_vecinos_burbuja(const int nPuntos, double distancia[], const int nVecinos, int indices_ordenados[][nVecinos], int indices[], int punto);

// Funcion principal
int main(void)
{
  int i,j;
  int nPuntos, nVecinos;
  
  // Obteniendo el numero de elementos del arreglo
  printf("Ingrese el numero de puntos:\n");
  scanf("%d",&nPuntos);
  printf("Ingrese el numero de vecinos:\n");
  scanf("%d",&nVecinos);
  printf("Ingrese el id del punto que quiere ver:\n");
  scanf("%d",&puntoConVecinos);

  // Definiendo los arreglos
  double x[nPuntos], y[nPuntos], z[nPuntos];
  int indices_ordenados[nPuntos][nVecinos];

  // Inicializa los arreglos de posicion
  inicializa_posiciones(nPuntos, x, y, z);
  
  // calcula distancia y los primeros n vecinos
  calcula_distancia(nPuntos, x, y, z, nVecinos, indices_ordenados);

  // imprime matriz de primeros vecinos y vecinos en archivo
  FILE *fMatrizVecinos = fopen("matriz_vecinos.dat", "w");
  for( i = 0; i < nPuntos; i++ )
    {
      fprintf(fMatrizVecinos, "%d : ", i);
      
      for( j=0; j < nVecinos; j++ )
	      fprintf(fMatrizVecinos,"%d ",indices_ordenados[i][j]);
      
      fprintf(fMatrizVecinos,"\n");
    }
  fclose(fMatrizVecinos);  
  
  FILE *fVecinos = fopen("vecinos.dat", "w");
  for( i=0; i<nVecinos; i++ )
    fprintf(fVecinos," %d %lf %lf %lf\n",
	    indices_ordenados[puntoConVecinos][i],
	    x[indices_ordenados[puntoConVecinos][i]],
	    y[indices_ordenados[puntoConVecinos][i]],
	    z[indices_ordenados[puntoConVecinos][i]]);
  fclose(fVecinos);  
  
  
  return 0;
} // Fin de la funcion principal

// Esta funcion inicializa las coordenadas x, y e z de cada punto usando 
// Numeros aleatorios obtenidos con drand48 entre 0 y limDistancia
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

// Esta funcion calcula las distancias punto a punto del sistema
// y hace un llamado a la funcion que hace el ordenamiento de burbuja
// para ordenar la distancia de menor a mayor respecto al punto 
// etiquetado como puntoConVecinos 
int calcula_distancia(const int nPuntos, double x[], double y[], double z[], const int nVecinos, int indices_ordenados[][nVecinos])
{
  int i, j, indices[nPuntos];
  double distancia[nPuntos];
  
  // Calcula la distancia a cada punto
  for( i=0; i<nPuntos; i++ )
    {
      for( j=0; j<nPuntos; j++ )
	{
	  if( i!=j )
	    {
	      distancia[j] = sqrt( (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j]) );
	    }
	  else
	    distancia[j] = 0.0;
	  
	}
      // Imprime las distancias a puntoConVecinos
      if( i == puntoConVecinos )
	{
	  printf("inicial\n");
	  for( j=0; j<nPuntos; j++ )
	    printf("%d %lf\n",j,distancia[j]);
	}
      
      // Ordena las distancias con algoritmo de burbuja
      calcula_primeros_vecinos_burbuja(nPuntos, distancia, nVecinos, indices_ordenados, indices, i);  

      if( i==puntoConVecinos )
	{
	  // Imprime la distancia ordenada de menor a mayor a puntoConVecinos
	  printf("\nfinal\n");
	  for( j=0; j<nPuntos; j++ )
	    printf("%d %lf\n",indices[j],distancia[j]);
	  // Imprime la etiqueta de los primeros n vecinos a puntoConVecinos
	  printf("\nprimeros vecinos al punto %d:\n",puntoConVecinos);
	  for( j=0; j<nVecinos; j++ )
	    printf("%d ",indices_ordenados[puntoConVecinos][j]);
	  printf("\n");
	}
      
    }
  
  return 0;
}

// Esta funcion ordena de mayor a menor un vector de distancias
// y almacena los indices de los primeros n vecinos en una matriz de vecinos
int calcula_primeros_vecinos_burbuja(const int nPuntos, double distancia[], const int nVecinos, int indices_ordenados[][nVecinos], int indices[], int punto)
{
  int i, j, almacena_indice;
  double almacena_distancia;
  
  // Inicializa los indices
  for( i=0; i<nPuntos; i++ )
    indices[i] = i;
  
  for( i=0; i<nPuntos; i++ ) // Ciclo que controla el numero de veces que se recorre el vector
    for( j=0; j<nPuntos-1; j++ ) // Ciclo que recorre el arreglo
      {
	// Compara los elementos adyasentes y los intercambia
	// Si el primero es mayor que el segundo
	if( distancia[j] > distancia[j+1]  )
	  {
	    // Ordenamiento burbuja
	    almacena_distancia = distancia[j];
	    distancia[j] = distancia[j+1];
	    distancia[j+1] = almacena_distancia;
	    
	    // Ordena indices
	    almacena_indice = indices[j];
	    indices[j] = indices[j+1];
	    indices[j+1] = almacena_indice;        
	  }
      }
  
  // Llena matriz de vecinos
  for( i=0; i<nVecinos; i++ ) 
    indices_ordenados[punto][i] = indices[i+1];

  return 0;
}

// Nota : graficar con splot [0:100][0:100][0:100] "posiciones.dat" u 2:3:4:(sprintf("%d", $1)) w labels point ps 3 pt 7 lc 1 offset char 1,1 t "puntos","vecinos.dat" u 2:3:4 w p ps 2 pt 7 lc 3 t "primeros vecinos","posiciones.dat" every ::0::0 u 2:3:4 w p ps 2 pt 7 lc 7 t "punto de interes"