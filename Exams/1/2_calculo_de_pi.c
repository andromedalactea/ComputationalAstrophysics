/*
La primera parte del programa calcula una aproximación de π.
Este cálculo se basa en la serie de Leibniz, que es una serie infinita
donde π se puede aproximar como 4 veces la suma de una serie de
fracciones con términos alternantes positivos y negativos.
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{
    // Inicializamos las variables necesarias para el cálculo
    int n = 0; // Número de términos de la sumatoria necesarios
    double pi_real = 3.141592653589793238; // Valor conocido de pi con alta precisión
    double pi_numerico_4 = 0; // Valor de pi que se calculará numéricamente (será pi/4)
    double error = pi_real - 4 * pi_numerico_4; // Cálculo inicial del error entre el valor real y el valor numérico de pi
    
    // Realizamos la sumatoria de la serie de Leibniz hasta que el error sea menor a 10^-10
    while (error > pow(10, -10))
    {
        // Sumamos el término actual de la serie a pi_numerico_4
        pi_numerico_4 += pow(-1, n) / (2 * n + 1);

        // Recalculamos el error con el nuevo valor de pi_numerico_4
        error = fabs(pi_real - 4 * pi_numerico_4);

        // Incrementamos el contador de términos
        n += 1;
    }

    printf("El número de términos necesarios para conseguir el valor de pi con un error menor a 10^-10 es: %d\n", n);

    // Reusando el código para calcular la precisión del computador
    // Inicializamos epsilon con un valor de 1.0
    double epsilon = 1.0;

    // Reducimos epsilon hasta encontrar el valor más pequeño que, al sumarle 1, no se perciba la diferencia
    while ((double)(1.0 + (epsilon / 2.0)) != 1.0) {
        epsilon /= 2.0;
    }

    printf("\nLa precisión que puede conseguir mi computador es: %g\n", epsilon);

    printf("\nEl número máximo de cifras significativas con las que mi computador puede calcular pi es 16\n");

    return 0;
}
