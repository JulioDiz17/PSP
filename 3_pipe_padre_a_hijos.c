/* =====================================================================
   VARIACION - PIPE AL REVES (el PADRE envia un mensaje al HIJO)
   Salida: El PADRE envia algo al pipe.
           El HIJO recibe algo del pipe: Buenos dias hijo.

   La UNICA diferencia con el 2: se intercambia quien hace write y quien read.
   - El que ENVIA (ahora el padre, en el else) -> write(fd[1], ...)
   - El que RECIBE (ahora el hijo, en el if)   -> read(fd[0], ...)
   OJO: el printf no decide quien es quien. Lo decide estar en el if o en el else.
   ===================================================================== */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];               // fd[0] = leer, fd[1] = escribir
    char buffer[80];

    pipe(fd);                // ANTES del fork

    int pid = fork();

    if (pid == 0) {
        // ======== HIJO -> RECIBE ========
        close(fd[1]);                                  // no va a escribir
        read(fd[0], buffer, 18);                       // espera al padre
        printf("El HIJO recibe algo del pipe: %s\n", buffer);
        close(fd[0]);
    } else {
        // ======== PADRE -> ENVIA ========
        close(fd[0]);                                  // no va a leer
        printf("El PADRE envia algo al pipe.\n");
        write(fd[1], "Buenos dias hijo.", 18);         // 17 letras + 1 = 18
        close(fd[1]);
        wait(NULL);                                    // espera a que el hijo acabe
    }
    return 0;
}