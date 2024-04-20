/*
  Este codigo ilustra el uso de funciones de C
  para manipular caracteres y cadenas de caracteres
*/

// Librerias de C
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> // Libreria de manipulacion de caracteres
#include<string.h> // Libreria de manipulacion de cadenas de caracteres

// funcion principal
int main(void)
{
  int i;
  // Aca declaramos e inicializamos caracteres y cadenas de caracteres

  //==================================================================
  // NOTA: En C, comillas simples ' ' son usadas para caractes, y dobles " "
  // requieren alocacion de memoria como las cadenas de caracteres

  printf("Definning and printting a character:\n\n");  
  char c;

  c = 'a'; // inicializa c
  
  putchar(c); // imprime el valor de c
  putchar('\n');
  putc(c, stdout); // imprime el valor de c
  putc('\n', stdout);
  putchar(65); // imprime el valor dado por el codigo ascii
  putchar(10);
  putc(65, stdout);
  putc(10, stdout);

  // Obteniendo un caracter desde el teclado usando getchar() and getc(stdin)
  printf("\n\n");
  printf("Obtener un caracter desde el teclado con getchar:\n");

  printf("Entre un caracter:\n");
  c = getchar();
  printf("tu caracter fue %c\n",c); // otra forma de imprimir caracteres 

  // En C, las cadenas son arreglos de caracteres que finalizan con el caracter nulo '\0'
  // para marcar la terminacion, la cadena es un puntero al primer caracter que la conforma

  // Una cadena se puede declarar usando la notacion de arreglo o de apuntador a char
  printf("\n\n");
  printf("La cadena puede ser definida como un arreglo 'char nombre[] = \"Luis\"'\n");
  printf("o como un apuntador a  'char *nombrePtr = \"Luis\"'\n");
  char nombre[] = "Luis";
  char *nombrePtr = "Luis";

  printf("\nComo arreglo nombre = %s, como apuntador nombrePtr = %s\n", nombre, nombrePtr);  
  
  // Otra forma de definir e inicializar las cadenas es "char nombre2[] = {'L','u','i','s','\0'}"
  printf("\nOtra forma de definir e inicializar las cadenas es 'char nombre2[] = {'L','u','i','s','\\0'}' \n");
  char nombre2[] = {'L','u','i','s','\0'}; // inicializa caracter a caracter
  printf("\nnombre2 = %s\n\n",nombre2);  

  // dos formas de acceder a las componentes de la cadena
  printf("Es posible acceder a las componentes de la cadena con  nombre[i] o *(nombrePtr + i), como con un arreglo: \n\n"); 
  printf("nombre[0] = %c o nombrePtr = %c\n",nombre[0],*(nombrePtr+0));
  printf("nombre[1] = %c o nombrePtr = %c\n",nombre[1],*(nombrePtr+1));
  printf("nombre[2] = %c o nombrePtr = %c\n",nombre[2],*(nombrePtr+2));
  printf("nombre[3] = %c o nombrePtr = %c\n",nombre[3],*(nombrePtr+3));
  printf("nombre[4] = %c o nombrePtr = %c\n",nombre[4],*(nombrePtr+4));


  // Recordemos la manipulacion de memoria de arreglos
  printf("\nRecordemos la manipulacion de memoria de arreglos:\n\n");
  printf("nombre = %p nombre[0] = %p nombre[1] = %p\n\n",nombre,&nombre[0],&nombre[1]);

  char nombre3[5]="Luis",*nombre3Ptr="Luis"; // Se debe tener una componente adicional para el caracter nulo
  
  printf("%s %s\n",nombre3,nombre3Ptr);
  printf("nombre3[0] = %c or nombre3Ptr = %c\n",nombre3[0],*(nombre3Ptr+0));
  printf("nombre3[1] = %c or nombre3Ptr = %c\n",nombre3[1],*(nombre3Ptr+1));
  printf("nombre3[2] = %c or nombre3Ptr = %c\n",nombre3[2],*(nombre3Ptr+2));
  printf("nombre3[3] = %c or nombre3Ptr = %c\n",nombre3[3],*(nombre3Ptr+3));
  printf("nombre3[4] = %c or nombre3Ptr = %c\n",nombre3[4],*(nombre3Ptr+4));
  
  printf("\nLa direccion de memoria de nombre3: %p y de nombre3Ptr : %p\n\n",nombre3,nombre3Ptr);
  

  *nombre3=0;
  nombre3Ptr=NULL;

  printf("\nLa direccion de memoria de nombre3: %p y de nombre3Ptr : %p\n\n",nombre3,nombre3Ptr);
    
  printf("\nAhora nombre almacena: %s y nombre3Ptr : %s\n\n",nombre3,nombre3Ptr);
  

  //=========================================================
    
  // Aca se ilustra el cuidado con el uso de de los operadores ++ y --
  //  cuendo se usan como el incremento de contadores en arreglos
    
  //==============================================================
  printf("Tenga cuidado con ++ and --\n\n");
 
  char nombre4[5]="Luis";
  int nt, nt1, nt2;
  nt = nt1 = nt2 = 0;

  printf("nt = %d \t nt1 = %d \t nt2 = %d\n",nt,nt1,nt2);
  printf("nt++ : %d \t ++nt2 : %d \t nt1 = nt1+1 : %d\n",nt++,++nt2,nt1 = nt1+1); 
  printf("nt++ : %d \t ++nt2 : %d \t nt1 = nt1+1 : %d\n",nt++,++nt2,nt1 = nt1+1);
  printf("nt++ : %d \t ++nt2 : %d \t nt1 = nt1+1 : %d\n\n",nt++,++nt2,nt1 = nt1+1);

  printf("nt = %d \t nt1 = %d \t nt2 = %d\n",nt,nt1,nt2);
  printf("nt-- : %d \t --nt2 : %d \t nt1 = nt1-1 : %d\n",nt--,--nt2,nt1 = nt1-1);
  printf("nt-- : %d \t --nt2 : %d \t nt1 = nt1-1 : %d\n",nt--,--nt2,nt1 = nt1-1);
  printf("nt-- : %d \t --nt2 : %d \t nt1 = nt1-1 : %d\n\n",nt--,--nt2,nt1 = nt1-1);

  nt = 0;

  printf("nombre4 = %s and nt = %d\n",nombre4,nt);
  printf("nombre4[nt++] = %c\n",nombre4[nt++]); 
  printf("nombre4[nt++] = %c\n",nombre4[nt++]); 
  printf("nombre4[nt++] = %c\n",nombre4[nt++]); 
  printf("nombre4[nt++] = %c\n",nombre4[nt++]); 
  printf("nombre4[nt++] = %c\n",nombre4[nt++]); 

  nt = 4;

  printf("nombre4 = %s and nt = %d\n",nombre4,nt);
  printf("nombre4[nt--] = %c\n",nombre4[nt--]);
  printf("nombre4[nt--] = %c\n",nombre4[nt--]);
  printf("nombre4[nt--] = %c\n",nombre4[nt--]);
  printf("nombre4[nt--] = %c\n",nombre4[nt--]);
  printf("nombre4[nt--] = %c\n",nombre4[nt--]);

  //====================================================
  
  // Este es el uso de scanf con cadenas
  
  //====================================================
  printf("\n\n");
  char palabra[1000]; // declara una cadena 

  printf("Entre una palabra:\n");

  // como palabra es un apuntador a una cadena, scanf no necesita el operador &
  // scanf leera hasta encontrar un espacio, nueva linea, o el indicador de final de archivo
  // La longitud maxima de la cadena es 999 reservando espacio para el caracter '\0'

  scanf("%s",palabra); // almaneca la cadena del usuario en al variable palabra
  printf("tu palabra es '%s'\n",palabra);

  //==================================================== 
  
  // Esto es una muestra de la libreria de manipulacion de caracteres <ctype.h> 
  
  //====================================================

  printf("\nEsta funcion manipula caracteres\n\n");

  printf("int isdigit(int c) returna 0 si c no es un digito (0 to 9) y cualquier entero si lo es.\n");
  printf("isdigit('a') = %d - isdigit('8') = %d\n\n",isdigit('a'),isdigit('8'));
 
  printf("int isalpha(int c) returna 0 if c no es una letra y cualquier entero si lo es.\n");
  printf("isalpha('9') = %d - isalpha('a') = %d\n\n",isalpha('9'),isalpha('a'));

  printf("int isalnum(int c) returna 0 if c no es un letra o un numero y cualquier entero si lo es.\n");
  printf("isalnum('a') = %d - isalnum('#') = %d\n\n",isalnum('a'),isalnum('#'));

  printf("int isspace(int c) returna 0 if c no es un caracter de secuencia de escape ('\\n','\\t',' ',etc) y cualquier entero si lo es.\n");
  printf("isspace('a') = %d - isspace('\\n') = %d\n\n",isspace('a'),isspace('\n'));
  
  // Se pueden hacer cosas como esta:
    printf( "%s\n%s%s\n%s%s\n\n", "De acuerdo a isdigit:",
	  isdigit('8') ? "8 es un " : "8 no es un ", "digito",
	  isdigit( '#' ) ? "# es un " : "# no es un ", "digito");
  
  printf("Puedes buscar otras funciones si estas interesado!!\n\n");
 
  //====================================================

  /*
    Aca mostramos la libreria de manipulacion de cadenas de caracteres <stdlib.h>
  */
  //====================================================

  // La funcion atof convierte un string en un double 

  double real;
  int entero;
  long int lentero;
  unsigned long ulentero;
  char numero1[100]="964.0";
  
  real = atof(numero1);

  printf("%s%s%s%lf\n\n","string : ",numero1," convertido a  double : ",real*2.0);
  
  char numero2[100]="964";
  
  entero = atoi(numero2);

  printf("%s%s%s%d\n\n","string : ",numero2," convertido a entero : ",entero*2);

  char numero3[100]="96496969696969696";

  entero = atoi(numero3);
  lentero = atol(numero3);

  printf("%s%s%s%d\n\n","string : ",numero3," convertido a entero : ",entero);
  printf("%s%s%s%ld\n\n","string : ",numero3," convertido to entero long : ",lentero);


  char *string = "964.0 es un numero real";
  printf("%s\n",string);
  // La funcion strtod(char *string,char **stringPtr) lee el numero en string y lo convierte a double,
  // despues mueve el apuntador al inicio del string remanente
  real = strtod(string,&string);
  printf("%s\n",string);  

  printf("%s%lf%s%s\n","Ahora, el numero real es : ",real," y el string es :", string);
  exit(0);    
  
  char *string1 = "964 es un entero", *remanentePtr;

  lentero = strtol(string1,&remanentePtr,0);

  // la funcion strtol(char *string,char **remanentePtr, int base) lee el numero y lo convierte a long int,
  // despues mueve el apuntador del string al inicio al apuntador a remanentePtr, base define la base para hacer la conversion
  // 0: base octal, 10: base decimal, 16: base hexagecimal 
  printf("%s%ld%s%s\n","Ahora, el numero entero es : ",lentero," y el string es :", remanentePtr);

  ulentero = strtoul(string1,&remanentePtr,0);

  // la funcion strtol(char *string,char **remanentePtr, int base) lee el numero y lo convierte a unsigned long int,
  // despues mueve el apuntador del string al inicio al apuntador a remanentePtr, base define la base para hacer la conversion
  // 0: base octal, 10: base decimal, 16: base hexagecimal 
  
  printf("%s%lu%s%s\n","Ahora, el numero entero es : ",ulentero," y el  string es :", remanentePtr);

  printf("\n\n");
  
    // Aca ilustramos el uso de getchar y puts para crear un string e imprimirlo
  char oracion[100];

  i = 0;

  c = getchar(); // este getchar es para tomar el \n del ultimo dato ingresado por teclado

  puts("escribe una oracion:\n"); // imprime "escribe una oracion:"
  
  while( (c = getchar()) != '\n') // esto llena oracion con los valores que se van almacenando en c
    oracion[i++] = c;

  oracion[i] = '\0'; // agrega un \0 para finalizar el string

  puts(oracion); // imprime la variable oracion

  puts("escribe una oracion:\n");

  gets(oracion); // obtiene un string desde el teclado OJO : NO USAR NUNCA ESTA FUNCION

  puts(oracion);

  printf("\n\n");

  // sprintf crea un string con el formato de printf
  sprintf(oracion,"hola%dhola%.2lf%s",123,1.5,"chao");
  puts(oracion);
   
  // Se pueden crear secuencias de nombres
  for( i=0; i<3; i++)
    {
      sprintf(oracion,"archivo_%.3d.dat",i);
      puts(oracion);
    }
  
  // sscanf hace lo mismo que scanf, pero el input es desde un string (oracion1 en este caso)
  // no desde el teclado
  printf("\n\n");
  char oracion1[100];
  sprintf(oracion1,"964 964.0");

  printf("%s\n",oracion1);

  sscanf(oracion1,"%d %lf",&entero,&real);

  printf("%s\n",oracion1);
  printf("%d \t %lf \n",2*entero,2*real);

  putchar('\n');

  // Las siguientes funciones necesitan la libreria string.h
  // contiene, entre otras cosas, las funciones de manipulacion de memoria
  // para usar con cadenas de caracteres

  // strcpy copia string2 a string3 
  char string2[]="esto es un string",string3[100],string4[100];

  strcpy(string3,string2);

  puts(string3);

  putchar('\n');

  // strncpy copia los primeros n (en este caso 10) caracteres de string3 a string4,
  // debe asegurar que string4 contenga el caracter NULL al final
  strncpy(string4,string3,10);
  string4[10] = '\0';

  puts(string4);

  putchar('\n');
 
  // strcat adiciona string4 a string3
  sprintf(string4,"segundo string");
  strcat(string3,string4);

  puts(string3);

  putchar('\n');
  

  // strncat adiciona los primeros n (en este caso 7) caracteres of string4 to string2
  sprintf(string4,"segundo string");
  strncat(string2,string4,7);

  puts(string2);

  putchar('\n');

  // int strcmp(char *s1,char *s2) compara el string s1 con s2 de acuerdo al codigo Ascii,
  // si s1=s2 returna 0
  // si s1>s2 retorna un entero positivo 
  // si s2>s1 retorna un entero negativo

  char *palabra1="luis";
  char *palabra2="luis";
  char *palabra3="luit";
  char *palabra4="lius";

  int comparacion;

  comparacion = strcmp(palabra1,palabra2);

  printf("comparando %s con %s \n",palabra1,palabra2);
  printf("comparacion = %d, los strings son iguales\n\n",comparacion);

  comparacion = strcmp(palabra1,palabra4);

  printf("comparando %s con %s \n",palabra1,palabra4);  
  printf("comparacion = %d, los strings no son iguales\n\n",comparacion);

  comparacion = strcmp(palabra1,palabra3);
  
  printf("comparando %s con %s \n",palabra1,palabra3);
  printf("comparacion = %d, %s < %s\n\n",comparacion,palabra1,palabra3);

  comparacion = strcmp(palabra3,palabra1);
 
  printf("comparando %s con %s \n",palabra3,palabra1);
  printf("comparacion = %d, %s > %s\n\n",comparacion,palabra3,palabra1);

  printf("\ncomparando solo los primeros n caracteres:\n\n");
 
  // int strncmp(char *s1,char *s2,size_t) compara los primeros n caracteres de string s1 con s2 de acuerdo al codigo Ascii,
  // si s1=s2 returna 0
  // si s1>s2 retorna un entero positivo 
  // si s2<s1 retorna un entero negativo

  char *palabras1="luiss";
  char *palabras2="luiss";
  char *palabras3="luits";
  char *palabras4="liuss";

  comparacion = strncmp(palabras1,palabras2,4);

  printf("comparando %s con %s \n",palabra1,palabra2);
  printf("comparacion = %d, los strings son iguales\n\n",comparacion);

  comparacion = strncmp(palabras1,palabras4,4);

  printf("comparando %s con %s \n",palabra1,palabra4);  
  printf("comparacion = %d, los strings no son iguales\n\n",comparacion);

  comparacion = strncmp(palabras1,palabras3,4);
  
  printf("comparando %s con %s \n",palabra1,palabra3);
  printf("comparacion = %d, %s < %s\n\n",comparacion,palabra1,palabra3);

  comparacion = strncmp(palabras3,palabras1,4);

  printf("comparando %s con %s \n",palabra3,palabra1);
  printf("comparacion = %d, %s > %s\n\n",comparacion,palabra3,palabra1);

  printf("=========================================\n");
  printf("Otras funciones pueden ser consultadas !!\n");
  printf("=========================================\n\n");

  //====================================================

  return 0; 

}
