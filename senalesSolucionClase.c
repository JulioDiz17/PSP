#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void gestion_padre(int senal)
{
signal(SIGUSR1, gestion_padre);
printf("Padre recibe senal..%d\n", senal);
}

void gestion_hijo(int senal)
{
signal(SIGUSR1, gestion_hijo);
printf("Hijo recibe senal..%d\n", senal);
}

int main(void)
{
pid_t pid_padre, pid_hijo;

pid_padre = getpid();
pid_hijo = fork();

switch (pid_hijo) {
    case -1:
        printf("Error al crear el proceso hijo...\n");
        exit(-1);
    case 0:
        signal(SIGUSR1, gestion_hijo);
        while (1) {
            sleep(1);
            kill(pid_padre, SIGUSR1);
            pause();
        }
    default:
        signal(SIGUSR1, gestion_padre);
        while (1) {
            pause();
            sleep(1);
            kill(pid_hijo, SIGUSR1);
        }
}
return 0;

