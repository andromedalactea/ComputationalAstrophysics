// Program to show the use of standar Libraries for c

// Import standar libraries for c
#include<stdio.h>
#include<stdlib.h>

// Main function
int main(void)
{
    // Printing in console
    printf("Welcome to c:\nHello\nWorld\n");

    // How much files i can open with c (Is posible change this number if is require)
    printf("The max number of files open is: %d\n",FOPEN_MAX);
         
    return 0;
}