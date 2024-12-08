#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <pthread.h>
//#include <wait.h>

int globalvar = 5;

void thread(int *var);

int main(void)
{
    printf("Ejercicio 6 (PID = %d)\n", getpid());

    int localvar = 7;
    pthread_t threadID[2];
    char buffer[2];
    printf("Hilo principal:\n\t&globalvar = %p\n\t&localvar = %p\n", &globalvar, &localvar);
    scanf("%c", buffer);

    printf("Se crean dos hilos.\n");
    pthread_create(&threadID[0], NULL, (void *) thread, &localvar);
    pthread_create(&threadID[1], NULL, (void *) thread, &localvar);
    scanf("%c", buffer);

    printf("Se acabó.\n");
    pthread_join(threadID[0], NULL);
    pthread_join(threadID[1], NULL);

    exit(0);
}

void thread(int *var)
{
    int threadvar1 = 35;
    int *threadvar2 = (int *) malloc(sizeof(int));
    *threadvar2 = globalvar * *var;

    printf("Hilo secundario:\n\t&globalvar = %p\n\t&localvar = %p\n", &globalvar, var);
    printf("\t&threadvar1 (mem. estática) = %p\n", &threadvar1);
    printf("\t&threadvar2 (mem. dinámica) = %p\n", threadvar2);
    pthread_exit(0);
}
