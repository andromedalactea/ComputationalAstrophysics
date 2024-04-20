// C Libraries 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Global variable
double limDistancia = 100.0;

// Prototype Functions
int initialize_positions(const int, double *, double *, double *);
int calculate_distance(const int nPuntos, double x[], double y[], double z[], int sort_index[]);
int calculate_first_neighboards_bouble(const int nPuntos, double distance[], int sort_index[]);


// Main Function
int main(void)
{
    int nPuntos;

    // Extract the number of elements of the array
    printf("Write here the number of points:\n");
    scanf("%d", &nPuntos);

    // Define Arrays
    double x[nPuntos], y[nPuntos], z[nPuntos];
    int sort_index[nPuntos];

    // Initialize the postions array
    initialize_positions(nPuntos, x, y, z);
    
}
                

int initialize_positions(const int nPuntos, double x[], double y[], double z[])
{
    int i;

    FILE *fPuntos = fopen("positions.dat", "w");
            x[i] = drand48()*limDistancia;

    // Initialize with random numbers
    for( i=0; i < nPuntos; i++)
        {
            // Generate random numbers
            x[i] = drand48()*limDistancia;
            y[i] = drand48()*limDistancia;
            z[i] = drand48()*limDistancia;

            // Save the points in the file
            fprintf(fPuntos, "%d %lf %lf %lf\n", i, x[i], y[i], z[i]);
        }
    fclose(fPuntos);

    return 0;
}