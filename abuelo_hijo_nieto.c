#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd1[2], fd2[2];
    int n;

    pipe(fd1);
    pipe(fd2);

    if (fork() == 0) {
        if (fork() == 0) {
            // NIETO
            read(fd2[0], &n, sizeof(n));
            printf("%d * 2 = %d\n", n, n * 2);
            n = n * 2;
            write(fd1[1], &n, sizeof(n));
        } else {
            // HIJO
            read(fd1[0], &n, sizeof(n));
            printf("%d + 5 = %d\n", n, n + 5);
            n = n + 5;
            write(fd2[1], &n, sizeof(n));

            read(fd1[0], &n, sizeof(n));
            printf("%d - 3 = %d\n", n, n - 3);
            n = n - 3;
            write(fd2[1], &n, sizeof(n));
        }
    } else {
        // ABUELO
        n = 10;
        write(fd1[1], &n, sizeof(n));
        wait(NULL);
        read(fd2[0], &n, sizeof(n));
        printf("Resultado final: %d\n", n);
    }
    return 0;
}