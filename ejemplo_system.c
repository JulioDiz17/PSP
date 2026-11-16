/* =====================================================================
   SYSTEM - ejecutar comandos de Linux desde C
   - system("comando") ejecuta el comando y LUEGO VUELVE a tu programa
   - Devuelve 0 si va bien. 32512 = comando no encontrado
   - El programa ESPERA a que acabe el comando (cierra gedit para seguir)
   ===================================================================== */

#include <stdio.h>      // printf
#include <stdlib.h>     // system

int main()
{
    printf("Ejemplo de uso de system():");

    printf("\n\tListado del directorio actual y envio a un fichero: ");
    printf("%d", system("ls > ficsalida"));        // guarda el ls en el fichero ficsalida

    printf("\n\tAbrimos con el gedit el fichero... ");
    printf("%d", system("gedit ficsalida"));       // abre gedit (cerrarlo para continuar)

    printf("\n\tEste comando es erroneo: %d", system("ged"));   // no existe -> 32512
    printf("\nFin de programa....\n");
    return 0;
}