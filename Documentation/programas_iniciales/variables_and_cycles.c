/*
    This program show the initial manage of variables and cycles in c 
    Notes:
    When you declare a variable you save in the registry the memorie path and the simbol but don't have a value, so:
    A variable have:
        - A symbol
        - Path in the memorie
        - Value 
*/

// Import standar libraries for c
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    // Declaring integer variables
    int integer_variable;
    int other_integer_variable, last_one_variable_for_example;
    
    // Size of the variables int
    size_t size_of_variable_int;
    size_of_variable_int = sizeof(integer_variable);
    printf("The size for the integer variable is: size_of_variable %lu \n", size_of_variable_int);

    // For Float variables
    float float_variable;
    size_t  size_of_variable_float;
    size_of_variable_float = sizeof(float_variable);
    printf("The size for the integer variable is: size_of_variable %lu \n", size_of_variable_float);

    // For double variables
    double double_variable;
    size_t  size_of_variable_double;
    size_of_variable_double = sizeof(double_variable);
    printf("The size for the integer variable is: size_of_variable %lu \n", size_of_variable_double);

    // Input variables
    double altura;
    printf("Put here the lenght in [m]");
    scanf("%lf", &altura);
    printf("La altura ingresada es %lf \n", altura);
    

    // Input many variables at the same time 
    int numeroDeCuerpos;
    double masaEnKg, velocidadInicial;
    printf("\n Ingrese el número de cuerpos (int), masa en [kg] velocidad inicial en m/s");
    scanf("%d %le %lg", &numeroDeCuerpos, &masaEnKg, &velocidadInicial);
    printf("numero cuerpos= %d, masa = %lf, velocidad= %lf \n", numeroDeCuerpos, masaEnKg, velocidadInicial);

    // Estructuras de repeticion
    // For

    int i;
    for (i=0; i <=10; i++) // Equal than i = i + 1 ( i++)
        {
            printf("%d\n", i);
            printf("Hello world\n");
        }
    
    // While
    // First strcuture for the while cycle

    i = 0;
    printf("\n Printing number with while");
    while (i<=10)
    {
        printf("%d\n", i);
        i++;
    }


    // Second strcuture for the while cycle
    printf("\n Printing number with do_while");
    i = 0;
    do
    {
        printf("%d\n", i);
        i++;
    } while (i<=10);
    
    return 0;

    /* 
    The difference between both structures is to evaluate the 
    conditional and execute the instructions y al contrario execute the instructions and evaluate condition 
    */
}