/*
  In this code we will do a simulation of a physics problem 
*/
// Import standar libraries for c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Global variables
double gravity_aceleration = 9.8;
double x_initial_speed = 1.0;

// Define functions

// Return name_function
void print_data_in_the_file(FILE *file_simulation, double time, double y_speed, double x_position, double y_position)
{
    fprintf(file_simulation, "%14.12lf\t%14.12lf\t%14.12lf\t%14.12lf\n",
            time, y_speed, x_position, y_position);
}

double calculate_energy(double mass, double, double ); // This is to save memory for the fucntion

// Function to calculate the error
double error_energy(double initial_energy, double current_energy);

// Function to save the energy in a document
void print_error_in_the_file(FILE *energy_file_error, double time, double current_energy, double error_energy)
{
    fprintf(energy_file_error, "%14.12lf\t%14.12lf\t%14.12lf\n",
            time, current_energy, error_energy);
}

// Analytic solution
void print_analytic_solution(FILE *file_analytic_solution, double time, double x_initial_speed,
                             double x_initial_position, double y_initial_speed, double y_initial_position);


// Calculate relative error
double relative_error_and_printing(FILE *file_relative_error, double x_position, double y_position, double time, double x_initial_speed, double x_initial_position, double y_initial_speed, double y_initial_position);

int main(void)
{
    // Initial Conditions for our system
    double x_initial_position = 0.0;
    double y_initial_position = 10.0;
    double y_initial_speed = 0.0;
    double mass = 1;
    double initial_energy = mass*gravity_aceleration*y_initial_position;

    // Parameters for the simulation
    double max_time_simulation = sqrt( 2.0*y_initial_position/gravity_aceleration);
    double tiempo, dt;

    // Verify the Initial conditions in console
    printf("\n Initial Conditions for our system are:\n");
    printf("(Xo, Yo) = ( %lf, %lf) m\n", x_initial_position, y_initial_position);
    printf("(Vxo, Vyo) = ( %lf, %lf) m/s\n", x_initial_speed, y_initial_speed);
    printf("g = %lf m/s²\n", gravity_aceleration);
    printf("\nEl tiempo máximo de simulación es: %lf s\n", max_time_simulation);

    
    // Variables to follow the system
    double x_position, y_position, y_speed, energy;

    y_speed = y_initial_speed;
    x_position = x_initial_position;
    y_position = y_initial_position;
    energy = initial_energy;

    // Custom number of point for the simulation
    printf("Ingrese el número de puntos para la simulación:");
    int number_of_points;
    scanf("%d", &number_of_points);

    // Let's to look up the dt for the number of point
    dt = max_time_simulation/number_of_points;

    // ---------------------------------------------------------------------------------------------------
    // Let's to look the SWITCH structure
    switch(number_of_points)
    {
        case 20:
            // Instructions...
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n->", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 100:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n->", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 10000:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n->", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 100000:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n->", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 1000000:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n->", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 100000000:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n->", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        
        // Default case if other conditionals are not enougth
        default:
            number_of_points = 1000;
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n->", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
    }
    // -----------------------------------------------------------------------------------------------------------------------

    // Variable for the file  to save the data of simulation
    FILE *file_simulation;
    FILE *energy_file_error;
    FILE *file_analytic_solution;
    FILE *file_relative_error;


    energy_file_error = fopen("parabolico_error_energy.dat", "w");
    file_simulation = fopen("parabolico_20.dat", "w"); // .dat is an extension format random (is not important) finally is a txt file
    file_analytic_solution = fopen("parabolico_analytic.dat", "w"); // .dat is an extension format random (is not important) finally is a txt file
    file_analytic_solution = fopen("relative_error_20.dat", "w"); // .dat is an extension format random (is not important) finally is a txt file

    // Save the initial conditions
    print_data_in_the_file(file_simulation, tiempo, y_speed, x_position, y_position);
    print_error_in_the_file(energy_file_error, tiempo, energy, error_energy(initial_energy, energy));
    print_analytic_solution(file_analytic_solution, tiempo, x_initial_speed, x_initial_position, y_initial_speed, y_initial_position);
    print_relative_error(file_relative_error, tiempo, x_position, y_position, x_initial_position, x_initial_speed, y_initial_speed, y_initial_position);
    
    // Start in the first step of dt 
    for(tiempo = dt; tiempo <= max_time_simulation; tiempo = tiempo + dt)
        {   
            // Integrate for the speed in "y" axis
            y_speed = y_speed - gravity_aceleration*dt;

            // Integrate positions in the time respect the last time
            x_position = x_position + x_initial_speed*dt;
            y_position = y_position + y_speed*dt;
            energy = calculate_energy(mass, y_position, y_speed);
            // y_position can not be less  than 0, beacuse the simulation have a floor
            if( y_position >= 0.0)
            {
            // Printing in a file time
                print_data_in_the_file(file_simulation, tiempo, y_speed, x_position, y_position);
                print_error_in_the_file(energy_file_error, tiempo, energy, error_energy(initial_energy, energy));
                print_analytic_solution(file_analytic_solution, tiempo, x_initial_speed, x_initial_position, y_initial_speed, y_initial_position);
                print_relative_error(file_relative_error, tiempo, x_position, y_position, x_initial_position, x_initial_speed, y_initial_speed, y_initial_position);

            }
            
            else
            {
                break;
            }
        }

    // is important close the file to release the RAM memory and the max open file default is 16 files at the same time
    fclose(file_simulation);
    fclose(energy_file_error);
    fclose(file_analytic_solution);
    fclose(file_relative_error);

    return 0;
}

// Function to calculate the energy 
double calculate_energy(double mass, double y_position, double y_speed)
{
    double energy, speed_square;
    speed_square = pow(y_speed, 2) + x_initial_speed*x_initial_speed;// Is faster do the direc product;
    energy = mass*gravity_aceleration*y_position +
             0.5*mass*speed_square;

    return energy;
}

// Function to calculate the error
double error_energy(double initial_energy, double current_energy)
{
    double error;
    error = (current_energy - initial_energy)/current_energy;

    // Obtain the absolute value
    if( error <= 0.0)
            {
            // Printing in a file time
                error = -error;
            }
            
            else
            {
                error = error;
            }
    return error;
}

// Analytic solution
void print_analytic_solution(FILE *file_analytic_solution, double time, double x_initial_speed, double x_initial_position, double y_initial_speed, double y_initial_position)
{   
    double x_position, y_position; 

    // Calculate the position
    x_position = x_initial_position + x_initial_speed*time;
    y_position = y_initial_position - y_initial_speed*time- 0.5*gravity_aceleration*time*time;
    
    // Printing the position in a file
    fprintf(file_analytic_solution, "%14.12lf\t%14.12lf\t%14.12lf\n",
            time, x_position, y_position);
}

// Calculate relative error
double print_relative_error(FILE *file_relative_error, double time,  double x_position, double y_position, double x_initial_speed, double x_initial_position, double y_initial_speed, double y_initial_position)
{   
    double x_position_analytic, y_position_analytic; 

    // Calculate the position
    x_position_analytic = x_initial_position + x_initial_speed*time;
    y_position_analytic = y_initial_position - y_initial_speed*time- 0.5*gravity_aceleration*time*time;
    
    
    double relative_error;
    relative_error = sqrt(pow((x_position-x_position_analytic), 2) + pow((y_position-y_position_analytic), 2));

    // Obtain the absolute value
    if( relative_error <= 0.0)
            {
            // Printing in a file time
                relative_error = -relative_error;
            }
            
            else
            {
                relative_error = relative_error;
            }
    return relative_error;

    // Printing relative error
    fprintf(file_relative_error, "%14.12lf\t%14.12lf\n",
            time, relative_error);
}