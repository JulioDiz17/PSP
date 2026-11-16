/* =====================================================================
   ACTIVIDAD 1.1 - FORK
   Que hace: crea un hijo. Variable = 6. Hijo resta 5, padre suma 5.
   Salida:   Valor inicial: 6 / Hijo: 1 / Padre: 11

   COMO ADAPTARLO:
   - Cambiar el valor inicial  -> linea "int variable = 6;"
   - Cambiar la operacion      -> lineas "variable = variable - 5" / "+ 5"
   - Mostrar los PID           -> getpid() (mi PID), getppid() (PID de mi padre)

   RECUERDA:
   - fork() devuelve 0 al HIJO y el PID del hijo al PADRE
   - Cada proceso tiene SU COPIA de las variables (no se ven entre ellos)
   - Compilar: gcc 1_fork.c    Ejecutar: ./a.out
   ===================================================================== */

#include <stdio.h>      // printf
#include <unistd.h>     // fork, getpid, getppid
#include <sys/wait.h>   // wait

int main()
{
    int variable = 6;                                      // valor inicial
    printf("Valor inicial de la variable: %d\n", variable);

    int pid = fork();                                      // AQUI SE DUPLICA: desde aqui hay 2 procesos

    if (pid == 0) {
        // ======== HIJO (fork le devolvio 0) ========
        variable = variable - 5;                           // el hijo cambia SU copia
        printf("Variable en Proceso Hijo: %d\n", variable);
    } else {
        // ======== PADRE (fork le devolvio el PID del hijo) ========
        wait(NULL);                                        // espera a que el hijo termine
        variable = variable + 5;                           // el padre cambia SU copia (sigue valiendo 6)
        printf("Variable en Proceso Padre: %d\n", variable);
    }
    return 0;
}