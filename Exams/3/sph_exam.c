/*
Este programa simula el movimiento de un fluido utilizando el método de partículas
Smoothed Particle Hydrodynamics (SPH). La simulación considera una aceleración
gravitacional implícita que causa que las partículas del fluido caigan y se distribuyan
en el fondo del dominio de simulación. El código está escrito en C y sigue los pasos
estándar del método SPH, incluyendo la inicialización de condiciones, la búsqueda de vecinos con Linked list,
la integración de las ecuaciones de movimiento y la actualización de las propiedades de las partículas.

Ejecute y compile el código con el siguiente comando:
gcc sph_exam.c -o sph_exam_ejecutable.out -lm ; time ./sph_exam_ejecutable.out 4000

Recuerde crear la carpeta output antes de ejecutar el código, además de tener el
archivo de gráficos gnuplot dentro de esta
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<malloc.h>

#define X 0
#define Y 1
#define kappa 2.0 // Kernel factor
#define gravity -1.5 // Gravity acceleration for the fluid particles

// Structure for the particles
typedef struct
{
  int id; // Particle id
  double pos[2]; // Position of the particle
  double vel[2]; // Velocity of the particle
  double accel[2]; // Acceleration of the particle
  double mass; // Mass of the particle
  double rho; // Density of the particle
  double h; // Smoothing length of the particle
  double p; 
  double c;
  double du;
  double u;
  int *nn; // Neighbors of the particle
  int nNeighbors; // Number of neighbors
  double *dx; // Distance in x for the neighbors of the particle 
  double *dy; // Distance in y for the neighbors of the particle
  double *r; // Distance for the neighbors of the particle
  double *W; // Kernel for the neighbors of the particle
  double *dWx; // Derivative of the kernel in x for the neighbors of the particle
  double *dWy; // Derivative of the kernel in y for the neighbors of the particle
  int type; // Type of the particle (1 for fluid, -1 for boundary)

  int cell[2]; // Cell for the particle in the grid
}Particles;

Particles *part, *auxPart;

int nFluid, nPart;

void ics(int nx, int ny, double dx, double dy, double Lx, double Ly, int nCellsX, int nCellsY);
double W(double r, double h);
double dW(double r, double dx, double h);
void testKernel(void);
void NN(int i);
void test_NN(void);
void density(void);

void eos(void);
void navierStokes(void);
void viscosity(double dx);
void boundaryInteraction(double dx);
void meanVelocity(void);
void acceleration(double dx);
void drift(double dt);
void kick(double dt);
void printState(char *outfile);

int main(int argc, char *argv[])
{

  int i, nx, ny, counter;
  
  double Lx, Ly, dx, dy;
  double dt = 5e-5;
  double t, tTotal = atoi(argv[1])*dt;
  char outfiles[500];

  printf("voy a correr durante %d pasos, un tiempo total de %lf s\n",atoi(argv[1]),tTotal);
    
  nx = 40;
  ny = 40;
  Lx = 1e-3;
  Ly = 1e-3;

  dx = Lx/nx;
  dy = Ly/ny;
  
  nFluid = nx*ny;
  
  part = (Particles *)malloc((size_t)nFluid*sizeof(Particles));
  if( part==NULL )
    {
      printf("Error alocando part\n");
      exit(0);
    }
  // Calculate the number of cells for the grid
  int nCellsX = (int)ceil(2*Lx/(kappa*dx));
  int nCellsY = (int)ceil(2*Ly/(kappa*dy));

  printf("nCellsX = %d, nCellsY = %d\n",nCellsX,nCellsY);
  // Create the initial conditions
  ics( nx, ny, dx, dy, Lx, Ly, nCellsX, nCellsY);

  // Testing kernel function
  testKernel();

  counter = 0;
  t = 0;
  
  // Printting system initial state
  sprintf(outfiles,"./output/state_%.4d",counter);
  printState(outfiles);
  
  // Main loop
  while( t<=tTotal )
    {
      // Calculate the cell for each particle
      for( i=0; i<nFluid; i++ )
        {
          part[i].cell[X] = (int)ceil(nCellsX*part[i].pos[X]/(2*Lx));
          part[i].cell[Y] = (int)ceil(nCellsY*part[i].pos[Y]/(2*Ly));
        }
    
      
      // Searching near neighbors for all fuid particles
      for( i=0; i<nFluid; i++ )
	      NN(i);
      
      // Testing near neighbors searching
      if(counter==0)
	      test_NN();
      
      // Computing density
      density();
            
      // Drift in leap-frog integration
      drift(dt);

      // Computing acceleration
      acceleration(dx);  

      // Kick in leap-frog integration
      kick(dt);
      
      // Drift in leap-frog integration
      drift(dt);
	
      t = t + dt;
      counter++;

      // Printting system state
      sprintf(outfiles,"./output/state_%.4d",counter);
      printState(outfiles);

      printf("step = %d \n",counter);
      
    }
  
  free(part);
  
  return 0;
}

void ics(int nx, int ny, double dx, double dy, double Lx, double Ly, int nCellsX, int nCellsY)
{
  int i, j, counter;
  
  FILE *fFluidIcs, *fbBorder, *frBorder, *ftBorder, *flBorder;
  fFluidIcs = fopen("fluid_ics.output","w");
    
  // ics for fluid particles
  counter = 0;
  for( j=0; j<ny; j++)
    {
      for( i=0; i<nx; i++)
	      {
	        part[counter].id = counter;
	        part[counter].pos[X] = i*dx+dx/2.0;
	        part[counter].pos[Y] = j*dy+dy/2.0;
          part[counter].vel[X] = 0.0;
          part[counter].vel[Y] = 0.0;
          part[counter].accel[X] = 0.0;
          part[counter].accel[Y] = - gravity;
          part[counter].rho = 1000;
          part[counter].h = dx;
          part[counter].mass = part[counter].rho*dx*dy;
          part[counter].p = 0.0;
          part[counter].c = 0.0;
          part[counter].du = 0.0;
          part[counter].u = 357.1; 
          part[counter].nn = NULL;
          part[counter].nNeighbors = 0;
          part[counter].dx = NULL;
          part[counter].dy = NULL;
          part[counter].r = NULL;
          part[counter].W = NULL;
          part[counter].dWx = NULL;
          part[counter].dWy = NULL;
          part[counter].type = 1;

          // Define cell for the particle
          part[counter].cell[X] = (int)ceil(nCellsX*part[counter].pos[X]/(2*Lx));
          part[counter].cell[Y] = (int)ceil(nCellsY*part[counter].pos[Y]/(2*Ly));
	    counter++;
	    }
    }
  

  // ics for boundary particles

  // speed in boundary
  double vBoundary = 1.5e-2; 
  
  int npVirtI = 8*(nx+ ny);
  int npV = npVirtI/4;
  
  printf("npV = %d\n",npV);
  // bottom border, 161 points

  fbBorder = fopen("bottom_border.output","w");

  //Boundary particles are add to estructure particles set
  nPart = nFluid;
  
  auxPart = NULL;
  
  auxPart = (Particles *)realloc(part, (size_t)(nPart+npV+1)*sizeof(Particles));
  if(auxPart==NULL)
    {
      printf("error en auxPart\n");
      exit(0);
    }
  else
    {
      part = auxPart;
      auxPart = NULL;
    }
  
  counter = nPart;
    
  for( i=0; i<=npV; i++)
    {
      part[counter].id = counter;
      part[counter].pos[X] = i*dx/2.0;
      part[counter].pos[Y] = 0.0;
      part[counter].vel[X] = 0.0;
      //part[counter].vel[X] = -vBoundary;
      part[counter].vel[Y] = 0.0;
      part[counter].accel[X] = 0.0;
      part[counter].accel[Y] = 0.0;
      part[counter].rho = 1000;
      part[counter].h = dx;
      part[counter].mass = part[counter].rho*dx*dy;
      part[counter].p = 0.0;
      part[counter].c = 0.0;
      part[counter].du = 0.0;
      part[counter].u = 357.1;
      part[counter].nn = NULL;
      part[counter].nNeighbors = 0;
      part[counter].dx = NULL;
      part[counter].dy = NULL;
      part[counter].r = NULL;
      part[counter].W = NULL;
      part[counter].dWx = NULL;
      part[counter].dWy = NULL;
      part[counter].type = -1;

      // Define cell for the particle
      part[counter].cell[X] = (int)ceil(nCellsX*part[counter].pos[X]/(2*Lx));
      part[counter].cell[Y] = (int)ceil(nCellsY*part[counter].pos[Y]/(2*Ly));

      counter++;
    }

   for( i=nPart; i<nPart+npV+1; i++)
    {
      fprintf(fbBorder,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(fbBorder);
  
  // right border, 159 points

  frBorder = fopen("right_border.output","w");

  //Boundary particles are add to estructure particles set
  nPart = counter;
  
  auxPart = NULL;
    
  auxPart = (Particles *)realloc(part,(size_t)(nPart+npV-1)*sizeof(Particles));
  if(auxPart==NULL)
    {
      printf("error en auxPart\n");
      exit(0);
    }
  else
    {
      part = auxPart;
      auxPart = NULL;
    }
    
  for( i=0; i<npV-1; i++)
    {
      part[counter].id = counter;
      part[counter].pos[X] = 2*Lx;
      part[counter].pos[Y] = dy/2.0 + i*dy/2.0;
      part[counter].vel[X] = 0.0;
      part[counter].vel[Y] = 0.0;
      //part[counter].vel[Y] = -vBoundary;
      part[counter].accel[X] = 0.0;
      part[counter].accel[Y] = 0.0;
      part[counter].rho = 1000;
      part[counter].h = dx;
      part[counter].mass = part[counter].rho*dx*dy;
      part[counter].p = 0.0;
      part[counter].c = 0.0;
      part[counter].du = 0.0;
      part[counter].u = 357.1;
      part[counter].nn = NULL;
      part[counter].nNeighbors = 0;
      part[counter].dx = NULL;
      part[counter].dy = NULL;
      part[counter].r = NULL;
      part[counter].W = NULL;
      part[counter].dWx = NULL;
      part[counter].dWy = NULL;
      part[counter].type = -1;

      // Define cell for the particle
      part[counter].cell[X] = (int)ceil(nCellsX*part[counter].pos[X]/(2*Lx));
      part[counter].cell[Y] = (int)ceil(nCellsY*part[counter].pos[Y]/(2*Ly));

      counter++;
    }
  
    for( i=nPart; i<nPart+npV-1; i++)
    {
      fprintf(frBorder,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(frBorder);
  
  // top border, 161 points

  ftBorder = fopen("top_border.output","w");


  //Boundary particles are add to estructure particles set
  nPart = counter;
  
  auxPart = NULL;
  
  auxPart = (Particles *)realloc(part,(size_t)(nPart+npV+1)*sizeof(Particles));
  if(auxPart==NULL)
    {
      printf("error en auxPart\n");
      exit(0);
    }
  else
    {
      part = auxPart;
      auxPart = NULL;
    }
      
  for( i=0; i<=npV; i++)
    {
      part[counter].id = counter;
      part[counter].pos[X] = i*dx/2.0;
      part[counter].pos[Y] = 2*Ly;
      part[counter].vel[X] = vBoundary;
      part[counter].vel[Y] = 0.0;
      part[counter].accel[X] = 0.0;
      part[counter].accel[Y] = 0.0;
      part[counter].rho = 1000;
      part[counter].h = dx;
      part[counter].mass = part[counter].rho*dx*dy;
      part[counter].p = 0.0;
      part[counter].c = 0.0;
      part[counter].du = 0.0;
      part[counter].u = 357.1;
      part[counter].nn = NULL;
      part[counter].nNeighbors = 0;
      part[counter].dx = NULL;
      part[counter].dy = NULL;
      part[counter].r = NULL;
      part[counter].W = NULL;
      part[counter].dWx = NULL;
      part[counter].dWy = NULL;
      part[counter].type = -1;

      // Define cell for the particle
      part[counter].cell[X] = (int)ceil(nCellsX*part[counter].pos[X]/(2*Lx));
      part[counter].cell[Y] = (int)ceil(nCellsY*part[counter].pos[Y]/(2*Ly));

      counter++;
    }

  for( i=nPart; i<nPart+npV+1; i++)
    {
      fprintf(ftBorder,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(ftBorder);
  
  // left border, 159 points

  flBorder = fopen("left_border.output","w");
  

  // Boundary particles are add to estructure particles set
  nPart = counter;
  
  auxPart = NULL;
    
  auxPart = (Particles *)realloc(part,(size_t)(nPart+npV-1)*sizeof(Particles));
  if(auxPart==NULL)
    {
      printf("error en auxPart\n");
      exit(0);
    }
  else
    {
      part = auxPart;
      auxPart = NULL;
    }
  
  for( i=0; i<npV-1; i++)
    {
      part[counter].id = counter;
      part[counter].pos[X] = 0.0;
      part[counter].pos[Y] = dy/2.0 + i*dy/2.0;
      part[counter].vel[X] = 0.0;
      part[counter].vel[Y] = 0.0;
      // part[counter].vel[Y] = vBoundary;
      part[counter].accel[X] = 0.0;
      part[counter].accel[Y] = 0.0;
      part[counter].rho = 1000;
      part[counter].h = dx;
      part[counter].mass = part[counter].rho*dx*dy;
      part[counter].p = 0.0;
      part[counter].c = 0.0;
      part[counter].du = 0.0;
      part[counter].u = 357.1;
      part[counter].nn = NULL;
      part[counter].nNeighbors = 0;
      part[counter].dx = NULL;
      part[counter].dy = NULL;
      part[counter].r = NULL;
      part[counter].W = NULL;
      part[counter].dWx = NULL;
      part[counter].dWy = NULL;
      part[counter].type = -1;

      // Define cell for the particle
      part[counter].cell[X] = (int)ceil(nCellsX*part[counter].pos[X]/(2*Lx));
      part[counter].cell[Y] = (int)ceil(nCellsY*part[counter].pos[Y]/(2*Ly));

      counter++;
    }

   for( i=nPart; i<nPart+npV-1; i++)
    {
      fprintf(flBorder,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(flBorder);
  
  // print all particles
  nPart = counter;
 
  for( i=0; i<nPart; i++)
    {
      fprintf(fFluidIcs,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }

  fclose(fFluidIcs);

  
}

double W(double r, double h)
{
  double R = r/h;
  
  double alpha = 15.0/(7.0*M_PI*h*h);
  
  if( (R >= 0.0) && (R < 1.0) )
    return alpha*((2.0/3.0) - R*R + 0.5*R*R*R);
  
  if( (R >= 1.0) && (R <= 2.0) )
    return alpha*((1.0/6.0)*(2.0-R)*(2.0-R)*(2.0-R));

  if( R>2.0)
    return 0.0;
  
  return 0.0;
}

double dW(double r, double dx, double h)
{
  
  double R = r/h;
  
  double alpha = 15.0/(7.0*M_PI*h*h);
  
  if( (R >= 0.0) && (R < 1.0) )
    return alpha*(-2.0 + 1.5*R)*dx/(h*h);
  
  if( (R >= 1.0) && (R <= 2.0) )
    return alpha*(-0.5*(2.0-R)*(2.0-R))*dx/(h*h*R);

  if( R>2.0)
    return 0.0;
  
  return 0.0;
}

void testKernel(void)
{
  double r, w, dw;

  FILE *fKernelTest;
  fKernelTest = fopen("kernel_test.output","w");
  
  for( r=-3.0; r<=3.0; r = r + 0.1)
    {
      w = W( fabs(r), 1.0);
      dw = dW( fabs(r), r/sqrt(3.0), 1.0);

      fprintf(fKernelTest,"%16.10lf %16.10lf %16.10lf\n",r,w,dw);
    }
  fclose(fKernelTest);
  
}

// Searching the near neighbors 
void NN(int i)
{
  double xij, yij, rij, hij;
  double *auxDouble;
  int j, *auxInt, nNeighbors;
   
  free(part[i].nn);
  free(part[i].dx);
  free(part[i].dy);
  free(part[i].r);
  free(part[i].W);
  free(part[i].dWx);
  free(part[i].dWy);
  
  part[i].nn = NULL;
  part[i].dx = NULL;
  part[i].dy = NULL;
  part[i].r = NULL;
  part[i].W = NULL;
  part[i].dWx = NULL;
  part[i].dWy = NULL;
  
  nNeighbors = 0;
  
  for( j=0; j<nPart; j++ )
    {  
      if( i!=j )
	      {
          // Conditional to verify if the particle is on the neighborhood
          if( abs(part[i].cell[X] - part[j].cell[X] ) <= 1 && abs(part[i].cell[Y] - part[j].cell[Y] ) <= 1 )
            {
              xij = part[i].pos[X] - part[j].pos[X];
              yij = part[i].pos[Y] - part[j].pos[Y];
              rij = sqrt( xij*xij + yij*yij );
              hij = 0.5*(part[i].h+part[j].h);

              // Show the particles and your cells
              if( rij <= kappa*hij + 1e-10  )
                {
                  nNeighbors++;

                  // add neighbor id
                  auxInt = NULL;
                  auxInt = (int *)realloc(part[i].nn,(size_t)(nNeighbors)*sizeof(int));
                  part[i].nn = auxInt;
                  auxInt = NULL;
                    
                  // add neighbor dx
                  auxDouble = NULL;
                  auxDouble = (double *)realloc(part[i].dx,(size_t)(nNeighbors)*sizeof(double));
                  part[i].dx = auxDouble;
                  auxDouble = NULL;

                  // add neighbor dy
                  auxDouble = NULL;
                  auxDouble = (double *)realloc(part[i].dy,(size_t)(nNeighbors)*sizeof(double));
                  part[i].dy = auxDouble;
                  auxDouble = NULL;

                  // add neighbor r
                  auxDouble = NULL;
                  auxDouble = (double *)realloc(part[i].r,(size_t)(nNeighbors)*sizeof(double));
                  part[i].r = auxDouble;
                  auxDouble = NULL;
            
                  // add neighbor W
                  auxDouble = NULL;
                  auxDouble = (double *)realloc(part[i].W,(size_t)(nNeighbors)*sizeof(double));
                  part[i].W = auxDouble;
                  auxDouble = NULL;

                  // add neighbor dWx
                  auxDouble = NULL;
                  auxDouble = (double *)realloc(part[i].dWx,(size_t)(nNeighbors)*sizeof(double));
                  part[i].dWx = auxDouble;
                  auxDouble = NULL;
            
                  // add neighbor dWy
                  auxDouble = NULL;
                  auxDouble = (double *)realloc(part[i].dWy,(size_t)(nNeighbors)*sizeof(double));
                  part[i].dWy = auxDouble;
                  auxDouble = NULL;
            
                  part[i].nn[nNeighbors-1] = j;
                  part[i].dx[nNeighbors-1] = xij;
                  part[i].dy[nNeighbors-1] = yij;
                  part[i].r[nNeighbors-1] = rij;
                  part[i].W[nNeighbors-1] = W( rij, hij ); 
                  part[i].dWx[nNeighbors-1] = dW( rij, xij, hij);
                  part[i].dWy[nNeighbors-1] = dW( rij, yij, hij);
            
                }  
            }
        }
    }
  part[i].nNeighbors = nNeighbors;
}

void test_NN(void)
{
  int i,j,k;

   FILE *fTestNN;
   fTestNN = fopen("NN_test.output","w");
   srand(time(NULL));
   
   for( k=0; k<20; k++)
    {
      i = rand() % nFluid;
      
      printf("testing for particle %d\n",i);
      printf("with %d neighbors\n",part[i].nNeighbors);
       
      fprintf(fTestNN,"%16d %16.10lf %16.10lf\n",
	      part[i].id,
	      part[i].pos[X],
	      part[i].pos[Y]);
      
      for( j=0; j<part[i].nNeighbors; j++ )
	      fprintf(fTestNN,"%16d %16.10lf %16.10lf\n",
		    part[i].nn[j],
		    part[part[i].nn[j]].pos[X],
		    part[part[i].nn[j]].pos[Y]);
      fprintf(fTestNN,"\n");
    }
  fclose(fTestNN);
    
}

void density(void)
{
  int i, j;
  double wii, norm;
  
  for( i=0; i<nFluid; i++ )
    {
      // Self density
      wii = W( 0.0, part[i].h );
      
      // Computing density
      part[i].rho = part[i].mass*wii;
      for( j=0; j<part[i].nNeighbors; j++ )
	      part[i].rho = part[i].rho + part[part[i].nn[j]].mass*part[i].W[j];

      // Normalizing the density
      norm = (part[i].mass/part[i].rho)*wii;
      for( j=0; j<part[i].nNeighbors; j++ )
	      norm = norm + (part[part[i].nn[j]].mass/part[part[i].nn[j]].rho)*part[i].W[j];
      
      part[i].rho = part[i].rho/norm;
    }
  
  printf("density computed\n");

}

void eos(void)
{
  int i;
  
  for( i=0; i<nPart; i++ )
    {
      part[i].c = 0.01;
      part[i].p = part[i].c*part[i].c*part[i].rho; 
    }
}

void navierStokes(void)
{

  int i, j, k;
  double pij, vdw;
  // Computing sound speed and pression
  eos();

  // Computing acceleration
  for( i=0; i<nFluid; i++ )
    {
      
      part[i].accel[X] = 0.0;
      part[i].accel[Y] = gravity;
      part[i].du = 0.0;

      for( k=0; k<part[i].nNeighbors; k++ )
	      {
	        j = part[i].nn[k];
	  
	        pij = ( part[i].p/(part[i].rho*part[i].rho) )
	          + ( part[j].p/(part[j].rho*part[j].rho) );
	        part[i].accel[X] = part[i].accel[X] - part[j].mass*pij*part[i].dWx[k];
	        part[i].accel[Y] = part[i].accel[Y] - part[j].mass*pij*part[i].dWy[k];
	  
	        vdw = (part[i].vel[X]-part[j].vel[X])*part[i].dWx[k]
	            + (part[i].vel[Y]-part[j].vel[Y])*part[i].dWy[k];
	        part[i].du = part[i].du + 0.5*part[j].mass*pij*vdw;
	  
	      } //W = integral( f*dr ) = integral( f*dr*(dt/dt) ) = integral( f*v*dt )

    }
  
  printf("acceleration computed\n");
}

void viscosity(double dx)
{
  
  int i, j, k;

  double xij, yij, vxij, vyij, vijrij, vdw;
  double hij, cij, phiij, rhoij, Piij;
  double alphapi = 1.0;
  double betapi = 1.0;
  double eps = dx;
  double eps2 = 0.01*eps*eps;

  for( i=0; i<nFluid; i++ )
    {
      for( k=0; k<part[i].nNeighbors ; k++ )
	      {
	  
	        j = part[i].nn[k];
	  
	        xij = part[i].pos[X] - part[j].pos[X];
	        yij = part[i].pos[Y] - part[j].pos[Y];
	        vxij = part[i].vel[X] - part[j].vel[X];
	        vyij = part[i].vel[Y] - part[j].vel[Y];
	        vijrij = vxij*xij + vyij*yij;
	  
	        if( vijrij < 0.0 )
	          {
	            hij = 0.5*(part[i].h+part[j].h);
	            phiij = (hij*vijrij)/( xij*xij + yij*yij + eps2);
	            cij = 0.5*(part[i].c+part[j].c);
	            rhoij = 0.5*(part[i].rho+part[j].rho);
	      
	            Piij = ( -alphapi*cij*phiij + betapi*phiij*phiij )/( rhoij );

	            part[i].accel[X] = part[i].accel[X] - part[j].mass*Piij*part[i].dWx[k];
	            part[i].accel[Y] = part[i].accel[Y] - part[j].mass*Piij*part[i].dWy[k];

	            vdw = (part[i].vel[X]-part[j].vel[X])*part[i].dWx[k]
		            + (part[i].vel[Y]-part[j].vel[Y])*part[i].dWy[k];
	            part[i].du = part[i].du + 0.5*part[j].mass*Piij*vdw;
	      
	          }
	  
	      }
    }
  printf("viscosity computed\n");
}

void boundaryInteraction(double dx)
{

  int i, j;
  int n1 = 12, n2 = 4;
  double r0 = dx/2.0, D = 0.01;
  double xij, yij, rij, PBxij, PByij;

  for( i=0; i<nFluid; i++ )
    {
      for( j=0; j<part[i].nNeighbors; j++ )
	      {
	        if( part[part[i].nn[j]].type==-1 )
	          {
	            xij = part[i].pos[X] - part[part[i].nn[j]].pos[X];
	            yij = part[i].pos[Y] - part[part[i].nn[j]].pos[Y];
	            rij = sqrt( xij*xij + yij*yij );
	      
	            if( rij<r0 )
		            {
		              PBxij = D*( pow((r0/rij),n1) - pow((r0/rij),n2) )*(xij/(rij*rij));
		              PByij = D*( pow((r0/rij),n1) - pow((r0/rij),n2) )*(yij/(rij*rij));
		  
		              part[i].accel[X] = part[i].accel[X] + PBxij;
		              part[i].accel[Y] = part[i].accel[Y] + PByij;
		  
		            }
	           }
	        }
      }
  printf("interaction with boundary computed\n");
}

void meanVelocity(void)
{

  int i, j;
  double epsilon = 0.3;
  double vxMean, vyMean;
  double vxij, vyij, rhoij;

  for( i=0; i<nFluid; i++ )
    {
      
      vxMean = 0.0;
      vyMean = 0.0;
      
      for( j=0; j<part[i].nNeighbors; j++ )
	{
	  vxij = part[i].vel[X] - part[part[i].nn[j]].vel[X];
	  vyij = part[i].vel[Y] - part[part[i].nn[j]].vel[Y];
	  rhoij = 0.5*(part[i].rho+part[part[i].nn[j]].rho);
	  vxMean = vxMean + (part[part[i].nn[j]].mass/rhoij)*vxij*part[i].W[j];
	  vyMean = vyMean + (part[part[i].nn[j]].mass/rhoij)*vyij*part[i].W[j];
	}

      part[i].vel[X] = part[i].vel[X] - epsilon*vxMean;
      part[i].vel[Y] = part[i].vel[Y] - epsilon*vyMean;
   
    }
}

void acceleration(double dx)
{

  // Computing acceleration and change of energy
  navierStokes();
  
  // Computing viscosity contribution
  viscosity(dx);
  
  // Computing interaction with boundary
  boundaryInteraction(dx);

  // Correction to mean velocity
  meanVelocity();

  printf("acceleration computed\n");
  
}

void drift(double dt)
{

  int i;
  
  for( i=0; i<nFluid; i++ )
    {
      part[i].pos[X] = part[i].pos[X] + 0.5*dt*part[i].vel[X];
      part[i].pos[Y] = part[i].pos[Y] + 0.5*dt*part[i].vel[Y];
      part[i].u = part[i].u + 0.5*dt*part[i].du;
    }
}

void kick(double dt)
{
  
  int i;
  
  for( i=0; i<nFluid; i++ )
    {
      part[i].vel[X] = part[i].vel[X] + dt*part[i].accel[X];
      part[i].vel[Y] = part[i].vel[Y] + dt*part[i].accel[Y];
    }
}

void printState(char *outfile)
{

  int i;

  FILE *fState;
  fState = fopen(outfile,"w");
 
  for( i=0; i<nPart; i++)
    {
      fprintf(fState,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(fState);

}
