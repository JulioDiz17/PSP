#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Ejemplo de uso de system():");

    printf("\n\tListado del directorio actual y envio a un fichero: ");
    printf("%d", system("ls > ficsalida"));      // ejecuta un comando de Linux

    printf("\n\tAbrimos con el gedit el fichero... ");
    printf("%d", system("gedit ficsalida"));

    printf("\n\tEste comando es erroneo: %d", system("ged"));  // no existe -> da error
    printf("\nFin de programa....\n");
    return 0;
}
