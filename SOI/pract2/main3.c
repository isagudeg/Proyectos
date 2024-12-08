#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
	
	FILE *newfile;
	newfile= fopen("pruebaej3.txt","wr");
	if(newfile==NULL){
		printf("erroe");
		exit(1);
	}

	fprintf(newfile, "Escrito por el proceso padre antes del fork\n");

	pid_t pid=fork();

	if(pid==0){
		printf("Soy el proceso hijo, escribiendo en el archivo.\n");
		fprintf(newfile, "Escrito por el proceso hijo\n");
	}
	
	else if(pid>0){
		printf("Soy el proceso padre, escribiendo en el archivo.\n");
        	fprintf(newfile, "Escrito por el proceso padre\n");

        	// Esperar que el hijo termine
        	wait(NULL);

	}

	fclose(newfile);
    return(EXIT_SUCCESS);
}
