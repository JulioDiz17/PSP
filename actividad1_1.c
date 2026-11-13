#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	
	int variable = 6;
	printf("Valor inicial de la variable: %d\n", variable);

	int pid = fork();
	
	if(pid == 0){
		
		variable = variable - 5;
		printf("Variable en Proceso Hijo: %d\n", variable);
	
	} else {
		wait(NULL);
		variable = variable + 5;
		printf("Variable en Proceso padre: %d\n", variable);
	}
	return 0;
}
