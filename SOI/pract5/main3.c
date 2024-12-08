#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

int main(int argc, char** argv){
    char buffer;
    int *numeros1 = (int *)malloc(100000 * sizeof(int));
    if(numeros1==NULL){
        perror("Error en la reserva de memoria");
    }
    //mallopt(M_MAP_THRESHOLD,100001*sizeof(int));
    int *numeros2 = (int *)malloc(100000 * sizeof(int));
    if(numeros2==NULL){
        perror("Error en la reserva de memoria");
    }
    printf("PID: %d\n",getpid());
    printf("  Variable reservada numero 1: inicio-> %p, fin-> %p\n  Variable reservada numero 2: inicio-> %p, fin-> %p\n",&(*numeros1), &numeros1[100000],&(*numeros2), &numeros2[100000]);
    scanf("%c",&buffer);
    

    free(numeros1);
    free(numeros2);


	return (EXIT_SUCCESS);
}
