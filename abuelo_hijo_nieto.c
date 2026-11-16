/* =====================================================================
   ABUELO - HIJO - NIETO (2 pipes)
   Camino del numero:
       ABUELO --fd1--> HIJO --fd2--> NIETO
       ABUELO <--fd2-- HIJO <--fd1-- NIETO
   10 + 5 = 15  |  15 * 2 = 30  |  30 - 3 = 27

   COMO ADAPTARLO:
   - Cambiar numeros u operaciones -> solo las lineas "n = n + 5", "n * 2", "n - 3"
     y el "n = 10" del abuelo.

   RECUERDA:
   - El 2o fork esta DENTRO del if del hijo -> solo el hijo crea al nieto
   - Cada proceso hace: LEER -> CALCULAR -> ESCRIBIR
   - El wait(NULL) del ABUELO es OBLIGATORIO: sin el, el abuelo podria
     robar el 15 de fd2 que es para el nieto
   ===================================================================== */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd1[2];   // le llega al HIJO:  ABUELO -> HIJO  y  NIETO -> HIJO
    int fd2[2];   // sale del HIJO:     HIJO -> NIETO   y  HIJO -> ABUELO
    int n;

    pipe(fd1);    // los pipes ANTES de los fork
    pipe(fd2);

    if (fork() == 0) {
        // ---------- a partir de aqui: HIJO ----------
        if (fork() == 0) {
            // ======== NIETO ========
            read(fd2[0], &n, sizeof(n));          // recibe 15 del hijo
            printf("%d * 2 = %d\n", n, n * 2);
            n = n * 2;                            // 30
            write(fd1[1], &n, sizeof(n));         // manda 30 al hijo
        } else {
            // ======== HIJO ========
            read(fd1[0], &n, sizeof(n));          // recibe 10 del abuelo
            printf("%d + 5 = %d\n", n, n + 5);
            n = n + 5;                            // 15
            write(fd2[1], &n, sizeof(n));         // manda 15 al nieto

            read(fd1[0], &n, sizeof(n));          // recibe 30 del nieto
            printf("%d - 3 = %d\n", n, n - 3);
            n = n - 3;                            // 27
            write(fd2[1], &n, sizeof(n));         // manda 27 al abuelo
        }
    } else {
        // ======== ABUELO ========
        n = 10;
        write(fd1[1], &n, sizeof(n));             // manda 10 al hijo
        wait(NULL);                               // espera a que el hijo termine (OBLIGATORIO)
        read(fd2[0], &n, sizeof(n));              // recibe 27
        printf("Resultado final: %d\n", n);
    }
    return 0;
}