#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];          // fd[0] = leer, fd[1] = escribir
    char mensaje[] = "Buenos dias padre.";
    char buffer[80];

    pipe(fd);           // crear el pipe ANTES del fork

    int pid = fork();

    if (pid == 0) {
        // HIJO: escribe en el pipe
        close(fd[0]);
        printf("El HIJO envia algo al pipe.\n");
        write(fd[1], mensaje, strlen(mensaje) + 1);
        close(fd[1]);
    } else {
        // PADRE: lee del pipe
        close(fd[1]);
        wait(NULL);
        read(fd[0], buffer, sizeof(buffer));
        printf("El PADRE recibe algo del pipe: %s\n", buffer);
        close(fd[0]);
    }
    return 0;
}
