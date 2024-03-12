// Import standar libraries for c
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int main(void)
{
    // Inicializamos las variables necesarias para el calculo
    int n = 0; // Número de terminos de la sumatoria necesarios
    double pi_real = 3.141592653589793238 ; // Valor de pi real
    double pi_numerico_4 = 0; // Este valor de pi va a ir incrementando con la sumatoria
    double error = pi_real - 4 * pi_numerico_4; // Este valor va a ser el error entre el valor real y el valor numérico de pi
    
    // Hagamos la sumatoria de pi con un ciclo hasta que el error sea menor a 10^-10
    
    while (error > pow(10, -10))
    {
        pi_numerico_4 += pow(-1,n) / (2*n + 1);
        error = fabs(pi_real - 4 * pi_numerico_4);
        n += 1;

        // printf("\n%g\n", error);
    }

    printf("El numero de terminos necesarios para conseguir el valor de pi con un error menor a 10^-10 es: %d\n", n);


    // Reusando el codigo del literal anterior 
    double epsilon = 1.0;

    while ((double)(1.0 + (epsilon / 2.0)) != 1.0) {
        epsilon /= 2.0;
    }

    printf("\nLa precisión que puede conseguir mi computador es: %g\n", epsilon);
    printf("\nEl número máximo de cifras significativas con las que mi comutador puede calcular pi es 16\n");

    return 0;
}