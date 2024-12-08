#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    char buffer;
    int padre=0,hijo;

    //Guardamos el PID del proceso padre
    padre=getpid();
    printf("PID proceso padre: %d\n",padre);

    scanf("%c",&buffer);

    //Creamos el `proceso hijo
    if((hijo = fork()) == -1){
		printf("Error al crear el hijo 1");
	}
	else if(hijo == 0){ //PROCESO HIJO
		printf("Soy el hijo 1, con PID %d. \n", getpid());

        scanf("%c",&buffer);

        //Reservamos la memoria dinámica
        int *numeros = (int *)malloc(15 * sizeof(int));
        if(numeros==NULL){
            perror("Error en la reserva de memoria");
        }
        printf("Variable reservada numero: inicio-> %p, fin-> %p\n",&(*numeros), &numeros[15]);

        scanf("%c",&buffer);

        //Cambiamls la imagen del proceso con execv (El código de prueba.c está en la entrega incluido)
        char *args[] = {"./prueba", NULL};
        if (execv("./prueba", args) == -1) {
            perror("Error al ejecutar execv");
        }
        scanf("%c",&buffer);
        //Mensaje de comprobación, nunca se imprime porque una vez cambiada la imagen el proceso ya no regresa al código anterior
        printf("He vuelto\n");

    }else{ //PROCESO PADRE
        scanf("%c",&buffer);
        wait(NULL); // Espera a que el hijo termine
        printf("SOY EL PADRE de nuevo");
    }

	return (EXIT_SUCCESS);
}
