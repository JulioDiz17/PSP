#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void manejador(int senal)
{
    printf("Padre recibe la senal %d\n", senal);
}

int main()
{
    signal(SIGUSR1, manejador);

    int pid = fork();

    if (pid == 0) {
        int padre = getppid();
        sleep(1);
        kill(padre, SIGUSR1);
        sleep(1);
        kill(padre, SIGUSR1);
        sleep(1);
        kill(padre, SIGUSR1);
        sleep(1);
        kill(padre, SIGKILL);
    } else {
        while (1) {
            pause();
        }
    }
    return 0;
}