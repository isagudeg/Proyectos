#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void gestion(int);

int main(int argc, char** argv){
	int padre,hijo;

	if (signal(SIGUSR1, gestion) == SIG_ERR){
		printf("Error al crear gestor 1\n");
	}
	padre=getpid();
	if ((hijo = fork()) == 0) { /*Trabajo del hijo*/
		printf("Soy el hijo y voy a ejecutar la llamada al sistema pause.\n");
		pause();
		printf("Programa reanudado.\n");
	}
	else {
		sleep(4);
		kill(hijo,SIGUSR1);
	}
	return (EXIT_SUCCESS);
}
static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
	switch (numero_de_senhal) {
		case SIGUSR1: /*Entra señal SIGUSR1*/
		printf("Señal enviada. Se reanudará el programa hijo.\n"); 
		break;
	}
	return; 
}
