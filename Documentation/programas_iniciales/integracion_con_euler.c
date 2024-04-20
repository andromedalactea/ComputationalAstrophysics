/*
  In this code we will do a simulation of a physics problem 
*/
// Import standar libraries for c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{
    // Initial Conditions for our system
    double x_initial_position = 0.0;
    double x_initial_speed = 1.0;
    double y_initial_position = 10.0;
    double y_initial_speed = 0.0;
    

    // Parameters for the simulation
    double gravity_aceleration = 9.8;
    double max_time_simulation = sqrt( 2.0*y_initial_position/gravity_aceleration);
    
    double tiempo, dt;

    // Verify the Initial conditions in console
    printf("\n Initial Conditions for our system are:\n");
    printf("(Xo, Yo) = ( %lf, %lf) m\n", x_initial_position, y_initial_position);
    printf("(Vxo, Vyo) = ( %lf, %lf) m/s\n", x_initial_speed, y_initial_speed);
    printf("g = %lf m/s²\n", gravity_aceleration);
    printf("\nEl tiempo máximo de simulación es: %lf s\n", max_time_simulation);

    
    // Variables to follow the system
    double x_position, y_position, y_speed;

    y_speed = y_initial_speed;
    x_position = x_initial_position;
    y_position = y_initial_position;

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
            printf("Simulación con %d puntos\n", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 100:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 10000:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 100000:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        case 1000000:
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
        
        // Default case if other conditionals are not enougth
        default:
            number_of_points = 1000;
            dt = max_time_simulation/number_of_points;
            printf("Simulación con %d puntos\n", number_of_points);
            printf("Con dt = %lf \n", dt);
            break;
    }
    // -----------------------------------------------------------------------------------------------------------------------

    printf("\n%14s %14s %14s %14s\n", "tiempo", "Vy", "x", "y");

    for(tiempo = 0.0; tiempo <= max_time_simulation; tiempo = tiempo + dt)
        {   
            

            // Integrate for the speed in "y" axis
            y_speed = y_speed - gravity_aceleration*dt;

            // Integrate positions in the time respect the last time
            x_position = x_initial_position + x_initial_speed*dt;
            y_position = y_position + y_speed*dt;

            // y_position can not be less  than 0, beacuse the simulation have a floor
            if( y_position >= 0.0)
            {
            // Printing our system data in the time
            printf("%14.8lf\t%14.8lf\t%14.8lf\t%14.8lf\n",
                    tiempo, y_speed, x_position, y_position);
            }
            
            else
            {
                break;
            }
        }
    return 0;
}