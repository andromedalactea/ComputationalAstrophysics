/*
Este programa calcula las funciones de Bessel de primera especie de orden
alpha (J_alpha) para un rango de valores x.

El cálculo se realiza mediante la fórmula de la serie de Taylor de las funciones de Bessel,
sumando términos hasta el 150, para asegurar la convergencia.

Se generan archivos de datos para los órdenes alpha de 0 a 2,
en los cuales se almacena el valor de x y el correspondiente valor de J_alpha(x).
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

long double factorial(int n); // Prototipo de la función factorial

int main() {
    // Inicialización de variables
    int alpha; // Orden de la función de Bessel
    double x; // Valor de la variable de la función de Bessel
    long double k; // Iterador de la sumatoria
    char nombreArchivo[100]; // Nombre del archivo de salida para los datos de la función de Bessel
    
    // Bucle para calcular las funciones de Bessel de diferentes órdenes
    for (alpha = 0; alpha <= 2; alpha++) {
        // Formatea el nombre del archivo de salida con el orden de la función de Bessel
        sprintf(nombreArchivo, "funcion_de_bessel_orden_%d.dat", alpha);
        // Abre el archivo de salida en modo de escritura
        FILE *funcion_de_bessel = fopen(nombreArchivo, "w");

        // Calcula la función de Bessel para un rango de valores x
        for (x = 0; x <= 20; x += 0.01) {
            long double j_x = 0; // Variable para almacenar la suma de la serie

            // Bucle para sumar los términos de la serie de Taylor
            for (k = 0; k <= 150; k++) {
                // Calcula el término k-ésimo y lo suma al total
                j_x += pow(-1, k) * pow(x / 2, 2 * k + alpha) / (factorial(k) * factorial(k + alpha));
            }
            // Escribe los resultados en el archivo de salida
            fprintf(funcion_de_bessel, "%g %Lf\n", x, j_x);
        }
        
        fclose(funcion_de_bessel);
    }
    return 0;
}

// Función que calcula el factorial de un número entero n
long double factorial(int n) {
    /*
    Calcula el factorial de un número entero n de forma iterativa.

    Parámetros:
    n: Número entero del cual se quiere calcular el factorial.

    Retorna:
    El factorial del número n.
    */

    long double fact = 1; // Variable para el resultado del factorial
    
    // Bucle para calcular el factorial de forma iterativa
    for (int i = 1; i <= n; i++) {
        fact *= i; // Multiplica el número actual por el contador
    }
    return fact; // Retorna el resultado del factorial
}