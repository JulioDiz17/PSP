/* =====================================================================
   VARIACION - SENALES AL REVES (el PADRE manda 3 SIGUSR1 al HIJO y luego SIGKILL)
   Salida: Hijo recibe la senal 10   (x3)

   DIFERENCIAS con el 6:
   - Ahora el que ESPERA es el HIJO (if) y el que ENVIA es el PADRE (else)
   - El padre usa como destino el "pid" que le devolvio fork() (es el PID del hijo)
   - Al final el padre hace wait(NULL) para que el hijo muerto no quede "zombie"
   ===================================================================== */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void manejador(int senal)
{
    printf("Hijo recibe la senal %d\n", senal);
}

int main()
{
    signal(SIGUSR1, manejador);        // ANTES del fork (asi el hijo ya esta preparado)

    int pid = fork();

    if (pid == 0) {
        // ======== HIJO -> ESPERA SENALES ========
        while (1) {
            pause();
        }
    } else {
        // ======== PADRE -> ENVIA SENALES ========
        for (int i = 0; i < 3; i++) {
            sleep(1);
            kill(pid, SIGUSR1);        // pid = PID del hijo
        }
        sleep(1);
        kill(pid, SIGKILL);            // mata al hijo
        wait(NULL);                    // recoge al hijo muerto
        printf("Padre: he matado a mi hijo\n");
    }
    return 0;
}