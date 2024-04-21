/*

Ultima modificacion :

Este programa lee un archivo de parametros que 
contine comentarios y nombres de las variables

compile con : gcc 1_programa_basico_en_c_11.c -o 1_programa_basico_en_c_11.out

Ejecute con : ./1_programa_basico_en_c_11.out <archivo de parametos a leer> <simbolo de determina un comentario>

Entrada : nombre archivo de parametros (string), caracter que simboliza un comentario 

Salida : Lectura del archivo de parametros en pantalla

    */
 
// librerias de C
#include <stdio.h>
#include <stdlib.h>  // Corregido de stlib.h a stdlib.h
#include <string.h>

 
// variables globales
int nLineasArchivo;
int tamanoString = 1000;
 
struct Parametros
{
    char Infile[200];
    char Outfile[200];
    int Ncuerpos;
    double tIntegracion;
}parametros;  // Se agrego un ; faltante
 
// rutinas y funciones
int contador_de_lineas(char *infile);
int lee_linea_archivos(char *infile, char L[nLineasArchivo][tamanoString], char comentario, int ignorar[nLineasArchivo]);
int extrae_valores_parametros(char L[nLineasArchivo][tamanoString], char comentario, int ignorar[nLineasArchivo]);
 
// Funcion principal
int main(int argc, char *argv[]) // Se agrego los corchetes faltates asociados al arreglo  de argumentos
{
    // Recibe por linea de comandos el nombre del archivo de parametros
    char *infile, *simboloComentario, comentario;
    infile = argv[1];
    simboloComentario = argv[2];
    
    printf("Esta es la filade argv: %s\n", argv[0]);
    printf("Leyendo archivo : %s\n", infile);
    printf("Comentarios definidos por : %s\n", simboloComentario);
    comentario = simboloComentario[0];
    printf("Comentarios : %c\n", comentario); // Se cambio el especificador de formato de %s a %c

    // Calculo el numero de lineas que contiene el archivo
    nLineasArchivo = contador_de_lineas(infile); // Se espera el archivo no su dirección de momeria como parámetro
    printf("el archivo contiene %d lineas\n\n", nLineasArchivo);
    
    char lineas[nLineasArchivo][tamanoString]; // matriz de lineas
    int ignorar[nLineasArchivo]; // vector que controla si una linea es ignorada
    
    // lee todas las lineas del archivo de parametros
    lee_linea_archivos(infile, lineas, comentario, ignorar);
    
    // extrae los valores de los parametros desde las lineas leidas
    extrae_valores_parametros( lineas, comentario, ignorar);
    
    // Imprime los parametros
    printf("\n\nParametros :\n");
    printf("======================\n");
    printf("parametros.Infile = %s\n",parametros.Infile);
    printf("parametros.Outfile = %s\n",parametros.Outfile);
    printf("parametros.Ncuerpos = %d\n",parametros.Ncuerpos);
    printf("parametros.tIntegracion = %lf\n",parametros.tIntegracion);
    printf("======================\n");
    return 0;
} // fin funcion principal 
 
// Esta funcion returna de lineas que tiene un archivo
// contando la cantidad de saltos de linea almacenados en el archivo
// hasta que encuentra el final del archivo. 
int contador_de_lineas(char *infile)
{

    int nLineas = 0;
    char c;
    FILE *pf;
    
    if( (pf=fopen(infile,"r")) == NULL )
        {
    printf("no puedo abrir archivo %s\n",infile);
    exit(0);
        }
    
    while( (c=getc(pf)) != EOF )
    if( c=='\n' )
        ++nLineas;
    
    fclose(pf);
    return nLineas;

}

// Esta funcion lee todas las lineas del archivo de parametros y la almacena 
// en la matriz de linea, cada una es un string.
int lee_linea_archivos(char *infile, char L[nLineasArchivo][tamanoString], char comentario, int ignorar[nLineasArchivo])
{
    int i, j;
    char c; // Se cambio el tipo de dato de string a char 
    FILE *fInfile = fopen(infile,"rb"); 

    printf("Archivo leido:\n");
    printf("===============================\n");
    for( i=0; i<nLineasArchivo; i++ ) // se agregaron dos ; faltantes
        {

            j = ignorar[i] = 0;
        // detecta lineas en blanco y debe ignorarse
        if( (c = fgetc(fInfile)) == '\n'  )     
                {
                ignorar[i] = 1;
                L[i][j] = c; // se cambio la forma de acceder a un puntero de punteros
                printf(" - ignorar %d\n", ignorar[i]);
                continue;
            }
        else     
            {       
                L[i][j++] = c;        
                // se debe ignorar las lineas que inicien con el simbolo de comentario y el EOF       
                if( (c == comentario) || (c == EOF) ) // se cambio el operador or por ||
                ignorar[i] = 1;

                while( (c = fgetc(fInfile)) != '\n' ) // Se usan comillas simples ya que es un caracter y no una cadena de caracteres
                    L[i][j++] = c;
            }
            L[i][j] = '\0';
            printf("%s - ignorar %d\n", L[i], ignorar[i]);  // Aqui los especificadores de formato estan erroneos debe de ser primero un string de la cadena de caracteres y luego un entero 
        }
    printf("===============================\n");

    fclose(fInfile);
    return 0;
}

// Esta funcion extrae los valores de los parametros desde las lineas leidas
int extrae_valores_parametros( char L[nLineasArchivo][tamanoString], char comentario, int ignorar[nLineasArchivo])
{
    int i, j, totalParametros = 4;
    int nParametro; // nParametro se debe de poder modificar entonces se borro conts
    char string1[300], string2[300], string3[300];
    char nombreParametros[totalParametros][200];
    void *apuntadorParametro[totalParametros];
    int tipoParametro[totalParametros];

    // Macros, esto lo veremos despues
    #define INT 1
    #define DOUBLE 2 // Aqui hay tres errores juntos y es que las macros no van con ; al final
    #define STRING 3 // ya que este punto y coma también se vería como parte del valor de la macro

    // asocia los nombres de los parametros con las variables que los va a almacenar
    nParametro = 0; // Se cambio == quye es un operador de comparación por uno de asignación =

    strcpy(nombreParametros[nParametro], "Infile");
    apuntadorParametro[nParametro] = &parametros.Infile;
    tipoParametro[nParametro++] = STRING;

    strcpy(nombreParametros[nParametro], "Outfile");
    apuntadorParametro[nParametro] = &parametros.Outfile;
    tipoParametro[nParametro++] = STRING;

    strcpy(nombreParametros[nParametro], "Ncuerpos");
    apuntadorParametro[nParametro] = &parametros.Ncuerpos;
    tipoParametro[nParametro++] = INT;

    strcpy(nombreParametros[nParametro], "tIntegracion");
    apuntadorParametro[nParametro] = &parametros.tIntegracion;
    tipoParametro[nParametro++] = DOUBLE;

    printf("\n\nLineas leidas a tramos\n");
    printf("=============================\n");
    for( i=0; i<nLineasArchivo; i++ )
        {
            if( ignorar[i] == 0 )
        { 
            sscanf(L[i],"%s%s%s", string1, string2, string3); // Habian más especificadores de formato que numero de variables asociadas
            printf("string1= %s - string2= %s - string3= %s\n", string1, string2, string3);
            
        // encuentra el parametro en la lista de parametros
        for( j=0; j<totalParametros; j++ )
            if( strcmp(string1, nombreParametros[j]) == 0) // En el condicional se debe de hacer una comparación en vez de una asignación
                break;
        
        // asigna el parametro a la variable correspondiente
        switch ( tipoParametro[j] ) 
          {   
            case INT:     
                *((int *) apuntadorParametro[j]) = atoi(string2); // Se debe de usar atoi en vez de atof ya que se esta llevando a un entero y no un flotante
                break;
            case DOUBLE:
                *((double *) apuntadorParametro[j]) = atof(string2);
                break;
            case STRING:
                strcpy(apuntadorParametro[j], string2);
            }
        }   
    }
    printf("=============================\n");
    return 0;
}