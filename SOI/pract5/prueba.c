#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    char charlocal[]="hola";
    char buffer;

    printf("Soy otro código con PID: %d\n",getpid());
    printf("Variable charlocal: %p\n",charlocal);
    scanf("%c",&buffer);
    return (EXIT_SUCCESS);
}
