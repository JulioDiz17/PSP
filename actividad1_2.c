/* =====================================================================
   ACTIVIDAD 1.2 - PIPE (el HIJO envia un mensaje al PADRE)
   Salida: El HIJO envia algo al pipe.
           El PADRE recibe algo del pipe: Buenos dias padre.

   COMO ADAPTARLO:
   - Cambiar el mensaje -> cambia el texto Y el numero (letras + 1)
   - Al reves (PADRE envia al HIJO) -> mira el archivo 3_pipe_padre_a_hijo.c

   RECUERDA:
   - fd[1] = ESCRIBIR (write)      fd[0] = LEER (read)
   - pipe() va ANTES del fork() para que los dos compartan el tubo
   - read() se queda ESPERANDO hasta que llega algo
   - El que ENVIA cierra fd[0], el que RECIBE cierra fd[1]
   ===================================================================== */

#include <stdio.h>      // printf
#include <unistd.h>     // fork, pipe, read, write, close

int main()
{
    int fd[2];               // fd[0] = leer, fd[1] = escribir
    char buffer[80];         // aqui se guarda el texto que se recibe

    pipe(fd);                // 1. crear el tubo (ANTES del fork)

    int pid = fork();        // 2. crear el hijo

    if (pid == 0) {
        // ======== HIJO -> ENVIA ========
        close(fd[0]);                                  // no va a leer
        printf("El HIJO envia algo al pipe.\n");
        write(fd[1], "Buenos dias padre.", 19);        // 18 letras + 1 = 19
        close(fd[1]);
    } else {
        // ======== PADRE -> RECIBE ========
        close(fd[1]);                                  // no va a escribir
        read(fd[0], buffer, 19);                       // espera y guarda el texto en buffer
        printf("El PADRE recibe algo del pipe: %s\n", buffer);   // %s porque es texto
        close(fd[0]);
    }
    return 0;
}