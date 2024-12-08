#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
//#include <wait.h>

#define N 1024

int main(void)
{
    char buffer[4];
    char *var1, *var2;

    printf("Ejercicio 3 (PID = %d)\n", getpid());
    //////////////////////////////////////////////////////////////////////////////////////
    printf("Prueba 1 (malloc y alloca)...\n");
    var1 = (char *) malloc(sizeof(char) * N);
    var2 = (char *) alloca(sizeof(char) * N);
    if (var1 && var2) {
        printf("var1 = %p-%p\n", var1, var1 + N);
        printf("var2 = %p-%p\n", var2, var2 + N);
    }
    else exit(1);
    scanf("%c", buffer);

    printf("Prueba 2 (realloc y malloc, incremento)...\n");
    var1 = (char *) realloc(var1, sizeof(char) * N * 8);
    var2 = (char *) malloc(sizeof(char) * N * 8);
    if (var1 && var2) {
        printf("var1 = %p-%p\n", var1, var1 + N * 8);
        printf("var2 = %p-%p\n", var2, var2 + N * 8);
    }
    else exit(1);
    scanf("%c", buffer);

    printf("Prueba 3 (realloc, incremento)...\n");
    var2 = (char *) realloc(var2, sizeof(char) * (N * 128 + 281));
    if (var1 && var2) {
        printf("var1 = %p-%p\n", var1, var1 + N * 128 + 281);
        printf("var2 = %p-%p\n", var2, var2 + N * 128 + 281);
    }
    else exit(1);
    scanf("%c", buffer);

    printf("Prueba 4 (mallopt y realloc)...\n");
    mallopt(M_MMAP_THRESHOLD, N * 512);
    free(var2);
    var2 = (char *) malloc(sizeof(char) * (N * 128 + 281));
    if (var1 && var2) {
        printf("var1 = %p-%p\n", var1, var1 + N * 128 + 281);
        printf("var2 = %p-%p\n", var2, var2 + N * 128 + 281);
    }
    else exit(1);
    scanf("%c", buffer);

    double *vard = (double *) malloc(sizeof(double) * 1000);
    printf("Prueba 5 (malloc de double)...\n");
    if (vard) {
        printf("vard = %p-%p, tamaño = %ld\n", vard, vard + N * 128 + 281, sizeof(vard));
    }
    vard += 8;
    free(vard);
    if (vard) {
        printf("vard = %p-%p, tamaño = %ld\n", vard, vard - 8 + N * 128 + 281, sizeof(vard));
    }
    else exit(1);
    scanf("%c", buffer);
    //////////////////////////////////////////////////////////////////////////////////////

    exit(0);
}
