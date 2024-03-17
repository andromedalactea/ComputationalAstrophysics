/**
 * Este programa simula el movimiento de un objeto en caída libre utilizando el método de integración de Lead-Frog y el método de Euler.
 * Calcula el error en la energía del sistema en cada paso de tiempo y guarda los resultados en archivos de datos.
 * También calcula la solución analítica para comparar con los resultados de los métodos de integración.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Variables globales, condiciones iniciales de nuestro sistema
double gravity_acceleration = 9.8;
double x_initial_position = 0.0;
double x_initial_speed = 2.0;
double y_initial_position = 10.0;
double y_initial_speed = 0.0;
double mass = 1.0;

// Prototipo de la función para calcular el error en la energía
double error_actual_energia(double initial_energy, double mass, double y_position, double y_speed);

// Definiendo la lógica principal de nuestro programa
int main(void) {
    // Varibale que contiene el nombre del archivo
    char name_file[100];

    // Encontremos la energía inicial para poder medir el desempeño de los integradores
    float speed_square, initial_energy;
    speed_square = y_initial_speed*y_initial_speed + x_initial_speed*x_initial_speed;// Es más rápido hacer el producto directo;
    initial_energy = mass*gravity_acceleration*y_initial_position +
                     0.5*mass*speed_square;
                     
    // Parámetros para la simulación
    double max_time_simulation = sqrt(2.0 * y_initial_position / gravity_acceleration); // Tiempo máximo de simulación
    printf("\n El tiempo máximo de simulación es: %lf s\n", max_time_simulation);
    double time, dt; // variables para el tiempo de seguimiento del sistema y el paso de tiempo

    // Variables para seguir el sistema
    double x_position, y_position, x_speed, y_speed;
    long double error_energy;
    
    // Velocidad inicial a medio paso (Necesaria para la integración de Lead-Frog)
    double y_speed_half_prev;

    
    // Array con número de puntos para la simulación
    int number_points_array[] = {10, 20, 50, 100, 300, 1000}; 

    // Numero de elementos en el array
    int length = sizeof(number_points_array) / sizeof(number_points_array[0]);

    // Archivo para guardar los datos del error de energía por cada integrador
    FILE *error_energy_file_lead_frog;
    FILE *error_energy_file_euler;
    FILE *movimiento_lead_frog;
    FILE *movimiento_euler;

    // Iterate over the array using a for loop
    for (int i = 0; i < length; i++) {
        // Paso de timepo para la simulación segun el número de puntos actual
        dt = max_time_simulation / number_points_array[i];

        // Abriendo los archivos para guardar los datos del error de energía
        sprintf(name_file, "error_energy_file_lead_frog_%d.dat", number_points_array[i]);
        error_energy_file_lead_frog = fopen(name_file, "w");

        sprintf(name_file, "error_energy_file_euler_%d.dat", number_points_array[i]);
        error_energy_file_euler = fopen(name_file, "w");

        // Abriendo los archivos para guardar los datos del movimiento por ambos métodos
        sprintf(name_file, "movimiento_lead_frog_%d.dat", number_points_array[i]);
        movimiento_lead_frog = fopen(name_file, "w");

        sprintf(name_file, "movimiento_euler_%d.dat", number_points_array[i]);
        movimiento_euler = fopen(name_file, "w");
        
        // ##################################################
        // Integración con el método de Lead-Frog
        // ##################################################
        
        // Inicializando nuestras variables con las condiciones iniciales   
        time = 0.0;
        x_speed = x_initial_speed;
        y_speed = y_initial_speed; 
        x_position = x_initial_position;
        y_position = y_initial_position;

        // Inicializar la velocidad a medio paso basado en las condiciones iniciales.
        y_speed_half_prev = y_speed - 0.5 * gravity_acceleration * dt;

        // Calcula inicial en la energía
        error_energy = error_actual_energia(initial_energy, mass, y_position, y_speed);
        
        // Agregando al archivo el error inicial en la energía 
        fprintf(error_energy_file_euler, "%14.12lf\t%Lg\n", time, error_energy);

        // Agregando las posiciones iniciales al archivo
        fprintf(movimiento_lead_frog, "%14.12lf\t%14.12lf\n", x_position, y_position);

        // Loop de tiempo comienza con el primer paso completo
        for (time = dt; time <= max_time_simulation; time += dt) {
            // Actualizar posición con velocidad a medio paso
            x_position += x_initial_speed * dt;
            y_position += y_speed_half_prev * dt;

            // Asegurarse de que y_position no sea menor que 0, ya que la simulación tiene un suelo
            if (y_position < 0.0) {
                break; // Detener la simulación si el objeto golpea el suelo
            }

            // Actualizar velocidad completa basada en la posición actualizada
            y_speed = y_speed_half_prev - 0.5 * gravity_acceleration * dt;

            // Preparar velocidad a medio paso para el siguiente ciclo
            y_speed_half_prev = y_speed - 0.5 * gravity_acceleration * dt;

            // Encontrar el error en la energía
            error_energy = error_actual_energia(initial_energy, mass, y_position, y_speed);

            // Impriendo el error de la energía en el archivo según el tiempo
            fprintf(error_energy_file_lead_frog, "%14.12lf\t%Lg\n", time, error_energy);
            fprintf(movimiento_lead_frog, "%14.12lf\t%14.12lf\n", x_position, y_position);
       
        }

        // ##################################################
        // Integración con el método de Euler
        // ##################################################
        

        // --------------------------------------------------
        // Reinicializando las variables con las condiciones iniciales
        time = 0.0;
        y_speed = y_initial_speed;
        x_position = x_initial_position;
        y_position = y_initial_position;

        // Calcula inicial en la energía
        error_energy = error_actual_energia(initial_energy, mass, y_position, y_speed);

        // Agregando al archivo el error inicial en la energía 
        fprintf(error_energy_file_euler, "%14.12lf\t%Lg\n", time, error_energy);

        // Agregando las posiciones iniciales al archivo
        fprintf(movimiento_euler, "%14.12lf\t%14.12lf\n", x_position, y_position);

        for(double time = dt; time <= max_time_simulation; time = time + dt){   
                
            // Integrando para la velocidad en el tiempo actual
            y_speed = y_speed - gravity_acceleration*dt;

            // Integrando las posiciones respecto al ultimo tiempo
            x_position = x_position + x_initial_speed*dt;
            y_position = y_position + y_speed*dt;

            // Asegurarse de que y_position no sea menor que 0, ya que la simulación tiene un suelo
            if(y_position < 0.0) {
                break; // Detener la simulación si el objeto golpea el suelo
            }
            // Encontrar el error en la energía
            error_energy = error_actual_energia(initial_energy, mass, y_position, y_speed);

            // Impriendo el error de la energía en el archivo según el tiempo
            fprintf(error_energy_file_euler, "%14.12lf\t%Lg\n", time, error_energy);

            // Impriendo el movimiento en el archivo según el tiempo
            fprintf(movimiento_euler, "%14.12lf\t%14.12lf\n", x_position, y_position);    
        }
        // Cerrando el archivo para guardar los datos del error de energía
        fclose(error_energy_file_lead_frog);
        fclose(error_energy_file_euler);
    }
    // ##################################################
    // Solución analítica para comparar con las soluciones numéricas
    // ##################################################

    // Abriendo el archivo para guardar los datos de la solución analítica
    FILE *file_analytic_solution;
    file_analytic_solution = fopen("solucion_analitica.dat", "w");

    // Inicializando nuestras variables con las condiciones iniciales  
    time = 0.0;
    x_speed = x_initial_speed;
    y_speed = y_initial_speed; 
    x_position = x_initial_position;
    y_position = y_initial_position;

    // Toma el ultimo dt para la solución analítica que fue el más alto
    for (time = 0; time <= max_time_simulation; time += dt) {
        double x_position, y_position; 

        // Calculate the position
        x_position = x_initial_position + x_initial_speed*time;
        y_position = y_initial_position - y_initial_speed*time- 0.5*gravity_acceleration*time*time;
        
        // Printing the position in a file
        fprintf(file_analytic_solution, "%14.12lf\t%14.12lf\n",
                 x_position, y_position);
    }

    // Cerrando el archivo para guardar los datos de la solución analítica
    fclose(file_analytic_solution);

    return 0;
}

// Función para calcular el error en la energía
double error_actual_energia(double initial_energy, double mass, double y_position, double y_speed)
    /*
    Esta función calcula el error en la energía del sistema en un tiempo dado.

    Parámetros:
    initial_energy: La energía inicial del sistema
    mass: La masa del objeto
    y_position: La posición en y del objeto actual
    y_speed: La velocidad en y del objeto actual

    Retorna:
    error_energy: El error en la energía del sistema en el tiempo actual
    */
    {   
        // Variables para el cálculo de la energía y su error
        double energy, speed_square;
        long double error_energy;

        // Calcula la energía actual del sistema
        speed_square = y_speed*y_speed + x_initial_speed*x_initial_speed;// Es más rápido hacer el producto directo;
        energy = mass*gravity_acceleration*y_position +
                0.5*mass*speed_square;

        // Calcula el error en la energía
        error_energy = fabs((energy - initial_energy)/initial_energy);
        return error_energy;
    } 
