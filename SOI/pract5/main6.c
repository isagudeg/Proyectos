#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/wait.h>
#include <pthread.h>

//Variable global
int intglobal=5;

//Función de los hilos
void *funcionHilos(void *arg) {
    //Variables en el hilo
    int intlocalhilo=2;
    int *intmalloc=malloc(sizeof(int));

    //Imprimimos las direcciones de memoria de las distintas variables
    printf("HILO SECUNDARIO:\n");
    printf("\tvariable global: %p\n\tvariable recibida como parametro: %p\n\tvariable local (mem. estática): %p\n\tvariable local con malloc (mem. dinámica): %p\n",&intglobal,arg,&intlocalhilo,intmalloc);
    
    //Actualizamos la variable local como el producto de la variable global y el parámetro recibido y la imprimimos
    intlocalhilo = intglobal * (*(int *)arg);
    printf("    valor recalculado de la variable local: %d\n\n", intlocalhilo);

    //Liberamos la memoria dinámica
    free(intmalloc);
    return NULL;
}


int main(int argc, char** argv){
    //Variables locales
    char buffer;
    int intlocal=10;
    pthread_t hilo1, hilo2;

    //Imprimimos PID y variables  del main
    printf("PID proceso main: %d\n",getpid());
    printf("MAIN:\n");
    printf("\tvariable global int: %p\n",&intglobal);
    printf("\tvariable local int: %p\n",&intlocal);
    
    scanf("%c",&buffer);
    printf("Creamos los hilos.\n");

    //creaoms los hilos
    pthread_create(&hilo1, NULL, funcionHilos, &intlocal);
    pthread_create(&hilo2, NULL, funcionHilos, &intlocal);
    scanf("%c",&buffer);

    //terminan los hilos
    printf("Finalizan los hilos.\n");
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    scanf("%c",&buffer);

	return (EXIT_SUCCESS);
}
