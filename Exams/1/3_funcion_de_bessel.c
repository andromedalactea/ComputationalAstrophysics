/*
El algoritmo comienza con un valor de epsilon igual a 1.0. Luego,
entra en un bucle que reduce epsilon a la mitad en cada iteración.
En cada paso, el algoritmo verifica si el valor actual de epsilon,
cuando se suma a 1.0, resulta en un valor diferente a 1.0.
Si al sumar la mitad del epsilon actual a 1.0 el resultado sigue siendo 1.0,
significa que epsilon aún no es lo suficientemente pequeño como para ser
considerado el épsilon de la máquina. El bucle continúa hasta que se encuentra
el valor más pequeño de epsilon que, al sumarse a 1.0, produce un valor detectable
como diferente de 1.0.
*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>

long double factorial(int n);


int main() {
    // Veamos las variables que vamos a utilizar
    int alpha; // Este es el orden de la función de bessel
    double x; // Este define el rango de valores para los cuales vamos a calcular la función de bessel
    int k; // Este es el iterador de la sumatoria
    char nombreArchivo[100]; // Este es el nombre del archivo que vamos a ir guardando con cada iteración 
    
    // Archivos para guardar los datos
    FILE *funcion_de_bessel;
    
    // Veamos el valor de las funciones de bessel en diferentes ordenes
    for (alpha = 0; alpha <= 2; alpha++){
        
        sprintf(nombreArchivo, "funcion_de_bessel_orden_%d.dat", alpha);
        funcion_de_bessel = fopen(nombreArchivo, "w"); // Abre el archivo para escritura

        for (x = 0; x <= 20; x += 0.01){

            long double j_x = 0;

            for (k = 0; k <= 150; k++){
                j_x += pow(-1, k) * pow(x / 2, 2 * k + alpha) / (factorial(k) * factorial(k + alpha));
            }
            fprintf(funcion_de_bessel, "%g %Lf\n", x, j_x);
        }
        fclose(funcion_de_bessel); // Cierra el archivo

    }
return 0;
}

// Función para calcular el factorial de un número entero
long double factorial(int n){
    long double fact = 1;
    for (int i = 1; i <= n; i++){
        fact = fact * i;
    }
    return fact;
}
