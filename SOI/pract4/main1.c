#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int var1 = 1;


void *funcionhilo1(void *arg) {
    int num = *(int *)arg;
    //int *num = (int *)arg;
    printf("hilo1, var2: %d\n", num);
	num=3;
	printf("hilo1, var2: %d\n", num);
    return NULL;
}
void *funcionhilo2(void *arg) {
    int *num = (int *)arg;
    printf("hilo2, var2: %d\n", *num);
    return NULL;
}
void *funcionhilo3(void *arg) {
    int *num = (int *)arg;
    printf("hilo3, var1: %d\n", *num);
    return NULL;
}

int main(int argc, char** argv){
	int var2=2, num1,num2,num3;
	pthread_t hilo1,hilo2,hilo3;

	num1 = pthread_create(&hilo1, NULL, funcionhilo1, &var2);
    if (num1 != 0) {
        perror("Error al crar el hilo 1");
        exit(1);
    }

	pthread_join(hilo1, NULL);

	num2 = pthread_create(&hilo2, NULL, funcionhilo2, &var2);
    if (num2 != 0) {
        perror("Error al crar el hilo 2");
        exit(1);
    }

	pthread_join(hilo2, NULL);

    num3 = pthread_create(&hilo3, NULL, funcionhilo3, &var1);
    if (num3 != 0) {
        perror("Error al crar el hilo 3");
        exit(1);
    }

	pthread_join(hilo3, NULL);
    printf("padre, var1: %d\n", var1);
    printf("padre, var2: %d\n", var2);


	

	return (EXIT_SUCCESS);
}
