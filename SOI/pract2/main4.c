#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t child1, child2;
    	int status;

    	// Crear primer hijo (el que se convertirá en zombie)
    	child1 = fork();

    	if (child1 < 0) {
        	perror("Error en fork");
        	exit(1);
    	}

    	if (child1 == 0) {
        	// Proceso hijo 1
        	printf("Soy el primer hijo (PID: %d), pronto seré un zombie.\n", getpid());
        	exit(5);  // Termina rápidamente con el código de salida 5
    	} 

    	// Crear segundo hijo (el que quedará activo más tiempo y se convertirá en huérfano)
    	child2 = fork();

    	if (child2 < 0) {
        	perror("Error en fork");
        	exit(1);
    	}

    	if (child2 == 0) {
        	// Proceso hijo 2
        	printf("Soy el segundo hijo (PID: %d), permaneceré activo por un tiempo.\n", getpid());
        	sleep(10);  // Simula trabajo antes de quedar huérfano
        	printf("El segundo hijo (PID: %d) ha terminado.\n", getpid());
        	exit(0);
    	}

    	// Proceso padre
    	printf("Soy el padre (PID: %d), voy a esperar un poco antes de hacer wait().\n", getpid());
    	sleep(2);  // Simula un retardo para que el primer hijo quede en estado zombie

    	// Hacer wait para recoger el estado del primer hijo
    	pid_t zombie_pid = wait(&status);
    	if (WIFEXITED(status)) {
        	printf("El padre (PID: %d) ha reanudado la ejecución. El primer hijo (PID: %d) terminó con código de salida: %d\n", getpid(), zombie_pid, WEXITSTATUS(status));
    	}

    	// Esperar un poco más para permitir que el segundo hijo quede huérfano
    	sleep(10);  // Simula trabajo mientras el segundo hijo aún está activo

    	printf("El padre (PID: %d) ha terminado.\n", getpid());

    	return(EXIT_SUCCESS);
}
