/* =====================================================================
   VARIACION - ENVIAR UN NUMERO, IDA Y VUELTA (2 pipes)
   El PADRE manda 10 al HIJO, el HIJO lo multiplica por 2 y se lo devuelve.
   Salida: Hijo recibe 10 y devuelve 20
           Padre recibe 20

   RECUERDA:
   - Numeros: write(fd[1], &n, sizeof(n))  y  read(fd[0], &n, sizeof(n))  -> CON &
   - Textos:  write(fd[1], "texto", letras+1)  -> SIN &
   - Para ida y vuelta hacen falta 2 pipes (uno por cada sentido)
   ===================================================================== */

#include <stdio.h>
#include <unistd.h>

int main()
{
    int ida[2];       // PADRE -> HIJO
    int vuelta[2];    // HIJO  -> PADRE
    int n;

    pipe(ida);        // los dos ANTES del fork
    pipe(vuelta);

    int pid = fork();

    if (pid == 0) {
        // ======== HIJO ========
        read(ida[0], &n, sizeof(n));          // recibe 10
        printf("Hijo recibe %d y devuelve %d\n", n, n * 2);
        n = n * 2;                            // 20
        write(vuelta[1], &n, sizeof(n));      // devuelve 20
    } else {
        // ======== PADRE ========
        n = 10;
        write(ida[1], &n, sizeof(n));         // manda 10
        read(vuelta[0], &n, sizeof(n));       // espera la respuesta
        printf("Padre recibe %d\n", n);
    }
    return 0;
}