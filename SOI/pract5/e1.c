#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <wait.h>

int var1_g = 1;
double var2_g;
char arr_g[32] = {"ARRAYGLOBAL"};

int main(void)
{
    int var1_l;
    double var2_l = 5.4;
    char arr_l[32] = {"ARRAYLOCAL"};

    char buffer[2];
    printf("Ejercicio 1 (PID = %d)\n", getpid());
    printf("  Variables globales: %14p | %14p | %14p\n", &var1_g, &var2_g, arr_g);
    printf("  Variables locales : %p | %p | %p\n", &var1_l, &var2_l, arr_l);
    scanf("%c", buffer);

    exit(0);
}
