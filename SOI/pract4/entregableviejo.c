#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
double inicio=1;
double final=1e9;
int nhilos=8;
double resultados[8];


void *funcionsuma(void *arg) {
    int numero = *(int *)arg,contador,i;
    double sumatorio=0,num=1;
    int desde,hasta=0,nvueltas=0;
    printf("Hilo %d\n", numero);


    while(hasta<final){
        hasta=(10*numero)+(10*nhilos*nvueltas);
        desde=hasta-9;
        if(hasta<=final){
            //printf("desde:%d,hasta:%d\n",desde,hasta);
            num=desde;
            for(i=desde;i<=hasta;i++){
                    sumatorio=sumatorio+(1/(num*num));
                    num++;
                    //printf("sumatorio del hilo %d:%f\n",numero,sumatorio);
            }
            nvueltas+=1;
            resultados[numero-1]=resultados[numero-1]+sumatorio;
            sumatorio=0;
        }
    }

    printf("Hilo %d ha terminando.\n", numero);
    pthread_exit(NULL);
}

int main(int argc, char** argv){
    int i;
    double calculos;
	int num[nhilos];
	pthread_t hilo[nhilos];

    /*//pedimos el numero de hilos que vamos a crear
    printf("Indica el numero de hilos:");
    scanf("%d",&nhilos);*/

	for(i = 0; i < nhilos; i++){
        num[i] = i + 1;  // Asignar un número a cada hilo
        if (pthread_create(&hilo[i], NULL, funcionsuma, &num[i]) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        }
    }


	for(int i = 0; i < nhilos; i++){
        pthread_join(hilo[i], NULL);
    }

    for(i = 0; i < nhilos; i++){
        printf("calculo del hilo %d : %f\n",i+1,resultados[i]);
        calculos=calculos+resultados[i];
    }
    printf("calculo: %f\n",calculos);

    printf("Todos los hilos han terminado");
	return (EXIT_SUCCESS);
}
