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
	if (signal(SIGUSR2, gestion) == SIG_ERR){
		printf("Error al crear gestor 2\n");
	}
	padre=getpid();
	if ((hijo = fork()) == 0) { /*Trabajo del hijo*/
		kill(padre,SIGUSR1); /*Envia señal al padre*/
		for (int i=1;i>0;i++){
			i++;
			printf("esperando\n");
			sleep(1);
		} /*Espera una señal del padre indefinidamente*/
	}
	else { 
		sleep(1);
		kill(hijo,SIGUSR2);
		sleep(2);
		kill(hijo,SIGTERM);
		/*** Completa el código del padre para enviar las señales SIGUSR2 y SIGTERM al hijo,
		y espera a que acabe con wait ***/
	}

	return (EXIT_SUCCESS);
}

	static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
		switch (numero_de_senhal) {
			case SIGUSR1: /*Entra señal SIGUSR1*/
			printf("Señal tipo 1 recibida. Soy %d\n",getpid()); 
			break;
			case SIGUSR2:
			printf("Señal tipo 2 recibida. Soy %d\n",getpid()); 
			break;
		}
		return; 
	}
