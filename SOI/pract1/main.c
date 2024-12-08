#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // para sleep

#define INCREMENTO_MEMORIA 1024 * 1024 // 1 MB por iteración

int main() {
    size_t total_memoria = 0;
    char *memoria_asignada;

    for (int i = 1;; i++) {
        // Aumentar la cantidad de memoria asignada en cada iteración
        total_memoria += INCREMENTO_MEMORIA;

        // Asignar más memoria
        memoria_asignada = (char *)malloc(total_memoria);
        
        if (memoria_asignada == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria.\n");
            return 1;
        }

        // Escribir datos en la memoria asignada
        for (size_t j = 0; j < total_memoria; j++) {
            memoria_asignada[j] = (char)(j % 256);  // Rellenar con datos arbitrarios
        }

        // Informar la cantidad total de memoria asignada
        printf("Iteración %d: Memoria asignada = %lu MB\n", i, total_memoria / (1024 * 1024));

        // Pausar el programa por 1 segundo antes de la siguiente iteración
        sleep(1);
    }

    return 0;
}
