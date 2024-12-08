#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int intglobal=5;
char charglobal[]="hola";
int arrayglobal[]={1,2,3};
float floatglobalvacio;

int main(int argc, char** argv){
    int intlocal=10;
    char charlocal[]="adios";
    int arraylocal[]={2,4,6};
    float floatlocalvacio;
    char buffer;

    printf("PID: %d\n",getpid());
    printf("  Variable intglobal: %p\n  Variable charglobal: %p\n  Variable arrayglobal: %p\n  Variable floatglobalvacio: %p\n",&intglobal,charglobal,arrayglobal,&floatglobalvacio);
    printf("  Variable intlocal: %p\n  Variable charlocal: %p\n  Variable arraylocal: %p\n  Variable floatlocalvacio: %p\n",&intlocal,charlocal,arraylocal,&floatlocalvacio);
    scanf("%c",&buffer);
	return (EXIT_SUCCESS);
}
