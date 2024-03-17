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

#include <stdio.h>

int main() {
    // Inicializamos epsilon con un valor de 1.0. 
    double epsilon = 1.0;

   // acercándonos gradualmente al épsilon de la máquina.
    while ((double)(1.0 + (epsilon / 2.0)) != 1.0) {
        epsilon /= 2.0;
    }

    // Imprime el valor de epsilon encontrado.
    printf("Épsilon de la máquina (double): %g\n", epsilon);
    return 0;
}
