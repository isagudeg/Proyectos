#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void gestion(int);

int main(int argc, char** argv){
	int cont=0,valor;

	//configuramos el gestor de señales para la señal SIGINT (Ctrl+C)
	if (signal(SIGINT, gestion) == SIG_ERR){
		printf("Error al crear gestor 1\n");	
	}

	//bucle infinito que espera señales
	while(1){
		pause(); //esperamos a recibir una señal
		if(cont>=2){ //comprobamos si la señal SIGINT ha sido recibida 3 veces
			printf("Volver al comportamiento habitual: \n");
			scanf("%d",&valor);
			if(valor==1){ //si valor es 1 se restaura el comportamiento de SIGINT
				signal(SIGINT, SIG_DFL);
			}
		}
	cont++;
	}
	
	return (EXIT_SUCCESS);
}
static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
	switch (numero_de_senhal) {
		case SIGINT: /*Entra señal SIGINT*/
		printf("Se ha recibido Ctrl C. Soy %d\n",getpid()); 
		break;
	}
	return; 
}
