#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void *funcionhilo1(void *arg) {
    printf("Soy el hilo 1\n");
    sleep(5);
    printf("Hilo 1 va a finalizar con exit\n");
    exit(0);
}
void *funcionhilo2(void *arg) {
    printf("Soy el hilo 2\n");
    sleep(10);
    printf("Hilo 2 va a finalizar\n");
    pthread_exit(NULL);
}
void *funcionhilo3(void *arg) {
    printf("Soy el hilo 3\n");
    sleep(10);
    printf("Hilo 3 va a finalizar\n");
    pthread_exit(NULL);
}

int main(int argc, char** argv){
	int num1,num2,num3;
	pthread_t hilo1,hilo2,hilo3;

	num1 = pthread_create(&hilo1, NULL, funcionhilo1, NULL);
    if (num1 != 0) {
        perror("Error al crar el hilo 1");
        exit(1);
    }


	num2 = pthread_create(&hilo2, NULL, funcionhilo2, NULL);
    if (num2 != 0) {
        perror("Error al crar el hilo 2");
        exit(1);
    }


    num3 = pthread_create(&hilo3, NULL, funcionhilo3, NULL);
    if (num3 != 0) {
        perror("Error al crar el hilo 3");
        exit(1);
    }
    
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
	pthread_join(hilo3, NULL);


	

	return (EXIT_SUCCESS);
}