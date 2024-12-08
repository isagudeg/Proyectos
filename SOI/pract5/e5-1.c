#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h> //Compilar con -ldl (ignorar warning con -static)
#include <math.h>  //Compilar con -lm
#include <string.h>

typedef double (*math_func_t)(double); //Puntero a funciones (de math.h en este caso)

int main(void)
{
    printf("Ejercicio 6 (PID = %d).\n", getpid());
    printf("Inspeccionando mapa de memoria (/proc/%d/maps)...\n", getpid());

    FILE *f = fopen("/proc/self/maps", "r"); //Lee su propio mapa de memoria
    char line[256];
    unsigned short dinamica = 0;
    math_func_t sin_func;
    void *handle = NULL;

    while (fgets(line, sizeof(line), f)) { //Mira si libm ha sido enlazada dinámicamente
        if (strstr(line, "libm.so") != NULL) {
            dinamica = 1;
            break;
        }
    }
    fclose(f);

    if (dinamica) {
        printf("Librería libm enlazada dinámicamente.\n");
        //Con RTLD_LAZY los símbolos se resuelven solo al momento de llamarlos
        handle = dlopen("libm.so", RTLD_LAZY); //Puntero a la librería
        sin_func = (math_func_t) dlsym(handle, "sin"); //Puntero al símbolo sin
    }
    else {
        printf("Librería libm enlazada estáticamente.\n");
        sin_func = (math_func_t) sin;
    }

    printf("Dirección de sin(): %p\n", (void *) sin_func);

    printf("sin(0)     = %lf\n", sin_func(0));
    printf("sin(pi/6)  = %lf\n", sin_func(M_PI/6));
    printf("sin(pi/4)  = %lf\n", sin_func(M_PI/4));
    printf("sin(pi/3)  = %lf\n", sin_func(M_PI/3));
    printf("sin(pi/2)  = %lf\n", sin_func(M_PI/2));
    printf("sin(2pi/3) = %lf\n", sin_func(2*M_PI/3));
    printf("sin(3pi/4) = %lf\n", sin_func(3*M_PI/4));
    printf("sin(5pi/6) = %lf\n", sin_func(5*M_PI/6));
    printf("sin(pi)    = %lf\n", sin_func(M_PI));
    printf("sin(3pi/2) = %lf\n", sin_func(3*M_PI/2));
    printf("sin(2pi)   = %lf\n", sin_func(2*M_PI));

    printf("Enter para salir...\n");
    getchar();

    if (handle != NULL)
        dlclose(handle);

    exit(0);
}

