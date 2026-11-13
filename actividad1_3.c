#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Esto se ejecuta cada vez que el padre recibe SIGUSR1
void manejador(int senal)
{
    printf("Padre recibe la senal %d\n", senal);
    fflush(stdout);
}

int main()
{
    signal(SIGUSR1, manejador);   // el padre dice que hacer con SIGUSR1

    int pid = fork();

    if (pid == 0) {
        // HIJO
        int padre = getppid();    // PID del padre
        sleep(1);
        kill(padre, SIGUSR1);     // senal 1
        sleep(1);
        kill(padre, SIGUSR1);     // senal 2
        sleep(1);
        kill(padre, SIGUSR1);     // senal 3
        sleep(1);
        kill(padre, SIGKILL);     // mata al padre
    } else {
        // PADRE: espera senales sin hacer nada
        while (1) {
            pause();
        }
    }
    return 0;
}
