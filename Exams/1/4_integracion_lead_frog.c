// Para el metodo lead forg debo de encontrar unos valores 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Variables globales, condiciones iniciales de nuestro sistema
double gravity_acceleration = 9.8;
double x_initial_position = 0.0;
double x_initial_speed = 1.0;
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
    double initial_energy = mass*gravity_acceleration*y_initial_position; //

    // Parámetros para la simulación
    double max_time_simulation = sqrt(2.0 * y_initial_position / gravity_acceleration); // Tiempo máximo de simulación
    printf("\n El tiempo máximo de simulación es: %lf s\n", max_time_simulation);
    double time, dt; // variables para el tiempo de seguimiento del sistema y el paso de tiempo

    // Variables para seguir el sistema
    double x_position, y_position, x_speed, y_speed, error_energy;;

    // Velocidad inicial a medio paso (Necesaria para la integración de Lead-Frog)
    double y_speed_half_prev;

    
    // Array con número de puntos para la simulación
    int number_points_array[] = {50, 100, 300, 1000}; 

    // Numero de elementos en el array
    int length = sizeof(number_points_array) / sizeof(number_points_array[0]);

    // Archivo para guardar los datos del error de energía por cada integrador
    FILE *error_energy_file_lead_frog;
    FILE *error_energy_file_euler;

    // Iterate over the array using a for loop
    for (int i = 0; i < length; i++) {
        // Paso de timepo para la simulación segun el número de puntos actual
        dt = max_time_simulation / number_points_array[i];
        
        // Abriendo el archivo para guardar los datos del error de energía
        sprintf(name_file, "error_energy_file_lead_frog_%d.dat", number_points_array[i]);
        error_energy_file_lead_frog = fopen(name_file, "w");

        sprintf(name_file, "error_energy_file_euler_%d.dat", number_points_array[i]);
        error_energy_file_euler = fopen(name_file, "w");

        // ##################################################
        // Integración con el método de Lead-Frog
        // ##################################################
        // Inicializando nuestras variables con las condiciones iniciales
        time = 0.0;
        x_speed = x_initial_speed;
        x_position = x_initial_position;
        y_position = y_initial_position;
        
        // Agregando al archivo el error inicial en la energía 
        fprintf(error_energy_file_lead_frog, "%14.12lf\t%14.12lf\n", time, error_energy);
    
        for(double time = dt; time <= max_time_simulation; time += dt) {
            // Actualizar la velocidad a medio paso
            y_speed_half_prev = y_speed -  gravity_acceleration * (dt * 0.5);

            // Actualizar la velocidad con el medio paso previo
            y_speed = y_speed_half_prev - gravity_acceleration * (dt * 0.5);

            // Actualizar posición
            x_position += x_speed * dt;
            y_position += y_speed_half_prev * dt;

            // Encontrar el error en la energía
            error_energy = error_actual_energia(initial_energy, mass, y_position, y_speed);
            
            // Asegurarse de que y_position no sea menor que 0, ya que la simulación tiene un suelo
            if(y_position < 0.0) {
                break; // Detener la simulación si el objeto golpea el suelo
            }

            // Impriendo el error de la energía en el archivo según el tiempo
            fprintf(error_energy_file_lead_frog, "%14.12lf\t%14.12lf\n", time, error_energy);
        }


        // --------------------------------------------------
        // Reinicializando las variables con las condiciones iniciales
        // Ahora integremos con el metodo de Euler
        time = 0.0;
        y_speed = y_initial_speed;
        x_position = x_initial_position;
        y_position = y_initial_position;

        // Agregando al archivo el error inicial en la energía 
        fprintf(error_energy_file_euler, "%14.12lf\t%14.12lf\n", time, error_energy);
    
        for(double time = dt; time <= max_time_simulation; time = time + dt){   
                
            // Integrando para la velocidad en el tiempo actual
            y_speed = y_speed - gravity_acceleration*dt;

            // Integrando las posiciones respecto al ultimo tiempo
            x_position = x_initial_position + x_initial_speed*dt;
            y_position = y_position + y_speed*dt;

            // Asegurarse de que y_position no sea menor que 0, ya que la simulación tiene un suelo
            if(y_position < 0.0) {
                break; // Detener la simulación si el objeto golpea el suelo
            }

            error_energy = error_actual_energia(initial_energy, mass, y_position, y_speed);
            // Impriendo el error de la energía en el archivo según el tiempo
            fprintf(error_energy_file_euler, "%14.12lf\t%14.12lf\n", time, error_energy);
            
        }
        // Cerrando el archivo para guardar los datos del error de energía
        fclose(error_energy_file_lead_frog);
        fclose(error_energy_file_euler);
    }
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
        double energy, speed_square, error_energy;
        speed_square = pow(y_speed, 2) + x_initial_speed*x_initial_speed;// Is faster do the direc product;
        energy = mass*gravity_acceleration*y_position +
                0.5*mass*speed_square;

        error_energy = fabs((energy - initial_energy)/energy);
        return error_energy;
    }
