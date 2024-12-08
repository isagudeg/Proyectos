#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void f1(int numero1){
    int numero2=2;
    printf("Función 1:\n  parámetro recibido: %p\n  variable int creada: %p\n", &numero1,&numero2);
}
void f2(int numero3){
    int numero4=4;
    printf("Función 2:\n  parámetro recibido: %p\n  variable int creada: %p\n", &numero3,&numero4);
}



int main(int argc, char** argv){
    int numero1=1,numero3=3;
    char buffer;

    printf("PID: %d\n",getpid());
    printf("Función 1: %p, función 2: %p\n",f1,f2);
    f1(numero1);
    f2(numero3);

    scanf("%c",&buffer);

	return (EXIT_SUCCESS);
}
