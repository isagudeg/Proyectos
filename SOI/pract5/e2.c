#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <wait.h>

int var1_g = 1;
double var2_g;
char arr_g[32] = {"ARRAYGLOBAL"};

void func1(int num);

void func2(int num);

int main(void)
{
    int num1 = 1;
    int num2 = 2;
    char buffer[2];

    printf("Ejercicio 2 (PID = %d)\n", getpid());
    printf("Función 1: %p\n", func1);
    printf("Función 2: %p\n", func2);
    func1(num1);
    func2(num2);

    scanf("%c", buffer);

    exit(0);
}

void func1(int num)
{
    int var;

    printf("  Variables de func1:\n");
    printf("    Argumento: %14p\n", &num);
    printf("    Local:     %14p\n", &var);
}

void func2(int num)
{
    int var;

    printf("  Variables de func2:\n");
    printf("    Argumento: %14p\n", &num);
    printf("    Local:     %14p\n", &var);
}
