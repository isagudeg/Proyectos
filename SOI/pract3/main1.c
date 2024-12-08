#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int pid,valor;


	pid=getpid();
	printf("%d",pid);
	printf("VALOR: \n");
	scanf("%d",&valor);

	return (EXIT_SUCCESS);
}