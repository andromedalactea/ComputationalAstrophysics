/////////////////////
// Cabeceras //
////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<malloc.h>
#include<gsl/gsl_sf_bessel.h>

#define X 0
#define Y 1
#define Z 2

typedef struct
{
  int Npart[6];
  double mass[6];
  double time;
  double   redshift;
  int      flag_sfr;
  int      flag_feedback;
  unsigned int npartTotal[6];
  int      flag_cooling;
  int      num_files;
  double   BoxSize;
  double   Omega0;
  double   OmegaLambda;
  double   HubbleParam; 
  int flag_stellarage;
  int flag_metals;
  unsigned int npartTotalHighWord[6];
  int  flag_entropy_instead_u;
  char     fill[256 - 6*4 - 6*8 - 2*8 - 2*4 - 6*4 - 2*4 - 4*8 - 2*4 - 6*4 - 1*4];  /* fills to 256 Bytes */
} io_encabezado;

io_encabezado encabezado;

typedef struct 
{
  unsigned int id;
  float pos[3];
  float vel[3];
  float masa;
  float accel[3];
  float accelMag;
}Particulas;

Particulas *part;

double G = 43007.1;
double etha = 1e-2;
double eps = 2.0;
int nTotal;

int acceleration(void);
int imprimirSnapshot(char *nombreArchivo, double t);
int evolve(double totalTime, double dt);
int tiempoAdactativo(double *dt);

int main(int argc, char *argv[])
{

  int i, j, dummy;
  int nPartConMasa, nMin, nMax;
  double totalTime, dt;
  char *infile;
  FILE * fDatos;

  infile = argv[1];

  printf("Leyendo el archivo %s\n",infile);

  fDatos = fopen(infile,"r");

  // leyendo encabezado
  fread(&dummy, sizeof(int), 1, fDatos);
  printf("dummy = %d\n",dummy);
  fread(&encabezado, sizeof(io_encabezado), 1, fDatos);
  fread(&dummy, sizeof(int), 1, fDatos);
  printf("dummy = %d\n",dummy);  
  
 

  nTotal = 0;
  for( i=0; i<6; i++ )
    {
      printf("Partculas tipo %d = %d\n",i,encabezado.Npart[i]);
      nTotal += encabezado.Npart[i];
    }
  
  printf("%d particulas en el snapshot\n",nTotal);

  part = (Particulas *)malloc((size_t)nTotal*sizeof(Particulas));

  // leyendo posiciones
  fread(&dummy, sizeof(int), 1, fDatos);
  printf("dummy = %d\n",dummy);

  for( i=0; i<nTotal; i++ )
    fread(&part[i].pos[0], sizeof(float), 3, fDatos);

  fread(&dummy, sizeof(int), 1, fDatos);
  printf("dummy = %d\n",dummy);  

  
  // leyendo velocidades
  fread(&dummy, sizeof(int), 1, fDatos);
  printf("dummy = %d\n",dummy);

  for( i=0; i<nTotal; i++ )
    fread(&part[i].vel[0], sizeof(float), 3, fDatos);

  fread(&dummy, sizeof(int), 1, fDatos);
  printf("dummy = %d\n",dummy);  
  
  // leyendo ids
  fread(&dummy, sizeof(int), 1, fDatos);
  printf("dummy = %d\n",dummy);

  for( i=0; i<nTotal; i++ )
    fread(&part[i].id, sizeof(unsigned int), 1, fDatos);

  fread(&dummy, sizeof(int), 1, fDatos);
  printf("dummy = %d\n",dummy);  
  
  // leyendo masas
  nPartConMasa = 0;
  for(i=0; i<6; i++)
    {
      if( encabezado.Npart[i]>0 )
	      {
	  
	        printf("Npart[%d] = %d  - mass[%d] = %f\n"
		      ,i,encabezado.Npart[i],i,encabezado.mass[i]);
	  
	      if( encabezado.mass[i]>0.0 )
	        nPartConMasa = nPartConMasa + 0;
	      else
	        nPartConMasa = nPartConMasa + encabezado.npartTotal[i];
	      }
    }

  printf("particulas con masa explicita = %d\n",nPartConMasa);


  if( nPartConMasa>0  ) 
    { 
      fread(&dummy,sizeof(dummy),1,fDatos);
      printf("dummy masa                        = %.9d",dummy);
    }
  
  nMin = nMax = 0;  
  for( j=0; j<6; j++)
    {
      nMax=nMax+encabezado.npartTotal[j];

      printf("tipo %d = %d particulas [ %d , %d)\n",j,encabezado.npartTotal[j],nMin,nMax);

      if( encabezado.npartTotal[j]>0 )
	      {
	        if( encabezado.mass[j]>0.0 )
	          {
	            for( i=nMin; i<nMax; i++)
		            part[i].masa = encabezado.mass[j];
	          }
	        else
	        {
	          for( i=nMin; i<nMax; i++)
		          {
		            fread(&part[i].masa,sizeof(float),1,fDatos);
		          } 
	        }
	      nMin = nMax;
	      }
    }
 
    if( nPartConMasa>0  )  
      fread(&dummy,sizeof(dummy),1,fDatos);

  fclose(fDatos);
  
  totalTime = 1.0;
  dt = 1.0/1000.0;

  evolve(totalTime, dt);

  free(part);
  
  return 0;
}

// evolve the system using a leap-frog integrator
int evolve(double totalTime, double dt)
{

  int i, counter=0, counter2=0;
  double t =0.0;
  char nombreArchivo[1000];

  sprintf(nombreArchivo,"./output_potentials/sim_eps_galaxia_%.5d",counter);
  imprimirSnapshot(nombreArchivo, t);
  
  // calcula aceleracion sobre todas las particulas
  // acceleration();

  while( t<totalTime )
    {

      // tiempoAdactativo(&dt);

      printf("tiempo = %.10lf  dt = %.10lf\n",t,dt);

      // drift
      for( i=0; i<nTotal; i++ )
	      {
	        part[i].pos[X] = part[i].pos[X] + 0.5*dt*part[i].vel[X];
	        part[i].pos[Y] = part[i].pos[Y] + 0.5*dt*part[i].vel[Y];
	        part[i].pos[Z] = part[i].pos[Z] + 0.5*dt*part[i].vel[Z];
	      }
      
      // calcula aceleracion sobre todas las particulas
      acceleration();
      
      // kick
      for( i=0; i<nTotal; i++ )
	      {
	        part[i].vel[X] = part[i].vel[X] + dt*part[i].accel[X];
	        part[i].vel[Y] = part[i].vel[Y] + dt*part[i].accel[Y];
	        part[i].vel[Z] = part[i].vel[Z] + dt*part[i].accel[Z];
	      }
      
      // drift
      for( i=0; i<nTotal; i++ )
	        {
	          part[i].pos[X] = part[i].pos[X] + 0.5*dt*part[i].vel[X];
	          part[i].pos[Y] = part[i].pos[Y] + 0.5*dt*part[i].vel[Y];
	          part[i].pos[Z] = part[i].pos[Z] + 0.5*dt*part[i].vel[Z];
        	}
      
      t += dt;
      counter++;
      
      //if( counter%100 == 0 )
      //{
      //  counter2++;
      // sprintf(nombreArchivo,"sim_eps_galaxia_%.3d",counter2);
	  sprintf(nombreArchivo,"./output_potentials/sim_eps_galaxia_%.5d",counter);
	  imprimirSnapshot(nombreArchivo, t);
	  //}

    }

  return 0;
}

int acceleration(void)
{

  int i, j;
  double dr[3]; 
  double r, R, r3;
  double eps2;

  eps2 = eps*eps;

  double m = 1.0; // masa para partículas de prueba
  double Mh, rh;
  double Mb, rb;
  double y, Sigma0, Md, Rd, lambda0, z0, I0, I1, K0, K1, nu;
  double axh, axd, axb;
  double ayh, ayd, ayb;
  double azh, azd, azb;
  
  Mh = 70.19;
  rh = 23.22;
  Mb = 2.39;
  rb = 0.68;
  Md = 5.59;
  Rd = 3.4;
  Sigma0 = Md/(2*M_PI*Rd*Rd);
  lambda0 = 0.0001;
  z0 = 0.2;
  nu = 75.0;
  
  for( i=0; i<nTotal; i++ )
    {
      
      r = sqrt( part[i].pos[X]*part[i].pos[X]
		    + part[i].pos[Y]*part[i].pos[Y]
		    + part[i].pos[Z]*part[i].pos[Z] );
      
      // aceleración del halo
      
      axh = - ( (G * Mh) / (m * r * (r+rh)*(r+rh) ) ) * part[i].pos[X];
      ayh = - ( (G * Mh) / (m * r * (r+rh)*(r+rh) ) ) * part[i].pos[Y];
      azh = - ( (G * Mh) / (m * r * (r+rh)*(r+rh) ) ) * part[i].pos[Z];
      
      // aceleración del disco
      if( (i>=encabezado.Npart[0]+encabezado.Npart[1]) && (i<encabezado.Npart[0]+encabezado.Npart[1]+encabezado.Npart[2]) )
	{
	  
	  R = sqrt( part[i].pos[X]*part[i].pos[X]
		    + part[i].pos[Y]*part[i].pos[Y] );
	  
	  y = R/(2.0*Rd);
	  
	  if (R < 100.0 )
	    {
	      I0 = gsl_sf_bessel_I0(y);
	      I1 = gsl_sf_bessel_I1(y);
	      K0 = gsl_sf_bessel_K0(y);
	      K1 = gsl_sf_bessel_K1(y);
	      
	      axd =  ( (M_PI * G * Sigma0)/m ) * ( -(2.0/R)*I1*K0 + (1.0/Rd)*(-I0*K0+I1*K1) ) * part[i].pos[X];
	      ayd =  ( (M_PI * G * Sigma0)/m ) * ( -(2.0/R)*I1*K0 + (1.0/Rd)*(-I0*K0+I1*K1) ) * part[i].pos[Y];
	      
	    }
	  else
	    {
	      axd = part[i].accel[X];
	      ayd = part[i].accel[Y];
	    }
	  
	  azd = - nu * nu * part[i].pos[Z];
	  //part[i].accel[Z] = - 4 * M_PI * lambda0 * z0 * tanh(part[i].pos[Z]/z0);
	  
	}
      
      // aceleración del bulbo
      axb = - ( (G * Mb) / (m * r * (r+rb)*(r+rb) ) ) * part[i].pos[X];
      ayb = - ( (G * Mb) / (m * r * (r+rb)*(r+rb) ) ) * part[i].pos[Y];
      azb = - ( (G * Mb) / (m * r * (r+rb)*(r+rb) ) ) * part[i].pos[Z];
      
      // aceleración total

      /*
      part[i].accel[X] = axh + axd + axb;
      part[i].accel[Y] = ayh + ayd + ayb;
      part[i].accel[Z] = azh + azd + azb; 
      */

      /*
      if( (i>=encabezado.Npart[0]+encabezado.Npart[1]) && (i<encabezado.Npart[0]+encabezado.Npart[1]+encabezado.Npart[2]) )
	{
	  part[i].accel[X] = axh + axd + axb;
	  part[i].accel[Y] = ayh + ayd + ayb;
	  part[i].accel[Z] = azh + azd + azb; 
	}
      else
	{
	  part[i].accel[X] = axh + axb;
	  part[i].accel[Y] = ayh + ayb;
	  part[i].accel[Z] = azh + azb; 
	}
      */
      
      if( (i>=encabezado.Npart[0]) && (i<encabezado.Npart[0]+encabezado.Npart[1]) )
	{
	  part[i].accel[X] = axh;
	  part[i].accel[Y] = ayh;
	  part[i].accel[Z] = azh;
	}
      if( (i>=encabezado.Npart[0]+encabezado.Npart[1]) && (i<encabezado.Npart[0]+encabezado.Npart[1]+encabezado.Npart[2]) )
	{
	  part[i].accel[X] = axd;
	  part[i].accel[Y] = ayd;
	  part[i].accel[Z] = azd; 
	}
      if( (i>=encabezado.Npart[0]+encabezado.Npart[1]+encabezado.Npart[2]) && (i<encabezado.Npart[0]+encabezado.Npart[1]+encabezado.Npart[2]+encabezado.Npart[3]) )
	{
	  part[i].accel[X] = axb;
	  part[i].accel[Y] = ayb;
	  part[i].accel[Z] = azb; 
	}

      
      part[i].accelMag = sqrt( part[i].accel[X]*part[i].accel[X] +
			       part[i].accel[Y]*part[i].accel[Y]+
			       part[i].accel[Z]*part[i].accel[Z] );

    }

  return 0;
}

int imprimirSnapshot(char *nombreArchivo, double t)
{
  int i, dummy;
  FILE *fSnaps=fopen(nombreArchivo,"w");

  encabezado.time = t;

  dummy = 256;
  
  // imprimo encabezado
  fwrite(&dummy, sizeof(int), 1, fSnaps);
  fwrite(&encabezado, sizeof(io_encabezado), 1, fSnaps);
  fwrite(&dummy, sizeof(int), 1, fSnaps);

  // imprimo posiciones
  dummy = nTotal*3*sizeof(float);
  fwrite(&dummy, sizeof(int), 1, fSnaps);
  for( i=0; i<nTotal; i++ )
    fwrite(&part[i].pos[0], sizeof(float), 3, fSnaps);
  fwrite(&dummy, sizeof(int), 1, fSnaps);

  // imprimo velocidades
  dummy = nTotal*3*sizeof(float);
  fwrite(&dummy, sizeof(int), 1, fSnaps);
  for( i=0; i<nTotal; i++ )
    fwrite(&part[i].vel[0], sizeof(float), 3, fSnaps);
  fwrite(&dummy, sizeof(int), 1, fSnaps);
  
  // imprimo ids
  dummy = nTotal*sizeof(int);
  fwrite(&dummy, sizeof(int), 1, fSnaps);
  for( i=0; i<nTotal; i++ )
    fwrite(&part[i].id, sizeof(int), 1, fSnaps);
  fwrite(&dummy, sizeof(int), 1, fSnaps);

  // imprimo masas
  dummy = nTotal*sizeof(float);
  fwrite(&dummy, sizeof(int), 1, fSnaps);
  for( i=0; i<nTotal; i++ )
    fwrite(&part[i].masa, sizeof(float), 1, fSnaps);
  fwrite(&dummy, sizeof(int), 1, fSnaps);
  
  fclose(fSnaps);
  
  return 0;
}

int tiempoAdactativo(double *dt)
{

  int i;
  double dtAux, accel;

  *dt = etha/sqrt( part[0].accelMag );

  for( i=1; i<nTotal; i++ )
    {

      dtAux =  etha/sqrt( part[i].accelMag );
     
      if( dtAux<*dt )
	{
	  *dt = dtAux;
	  accel = part[i].accelMag;
	}

    } 

  printf("accel = %.10lf  dt = %.10lf\n",accel,*dt);

  return 0;
}

// compilar con:

//  gcc -Wall -I/home/lquiroga/local/include/ simulador_n_cuerpos_potenciales.c -L/home/lquiroga/local/lib -lgsl -lgslcblas -lm -o simulador_n_cuerpos_potenciales.out
