#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contarCifrasSignificativas(double numero) {
    char buffer[50];
    // Convertir el número a notación científica en una cadena
    sprintf(buffer, "%.15e", numero);

    // Encuentra la posición del exponente 'e'
    char* ePos = strchr(buffer, 'e');

    // La cantidad de cifras significativas es la longitud de la cadena
    // hasta 'e', excluyendo el punto decimal.
    int cifras = 0;
    for(char* ptr = buffer; ptr < ePos; ptr++) {
        if (*ptr >= '0' && *ptr <= '9') {
            cifras++;
        }
    }

    // Ajustar para excluir ceros a la izquierda en números menores que 1
    if (numero < 1) {
        char* firstNonZero = strpbrk(buffer, "123456789");
        if (firstNonZero != NULL) {
            cifras -= (firstNonZero - buffer) - 2; // Excluir '0.' del conteo
        }
    }

    return cifras;
}

int main() {
    double numero = 0.0006;
    int cifrasSignificativas = contarCifrasSignificativas(numero);
    printf("El número %g tiene %d cifras significativas.\n", numero, cifrasSignificativas);

    numero = 123.45;
    cifrasSignificativas = contarCifrasSignificativas(numero);
    printf("El número %g tiene %d cifras significativas.\n", numero, cifrasSignificativas);

    return 0;
}
