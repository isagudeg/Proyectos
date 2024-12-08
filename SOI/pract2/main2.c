#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Variable global
int global_var = 100;

int main() {
	
	// Variables locales
    	int local_var = 200;

	// Variable dinámica
    	int *dynamic_var = (int *)malloc(sizeof(int));
    	*dynamic_var = 300;

	pid_t pid=fork();

	if(pid==0){
		printf("Proceso hijo: %d\n", getpid());
		printf("getppid, id padre del hijo: %d\n", getppid());
		printf("getuid, uid del ususario en hijo: %d\n", getuid());
		printf("geteuid, uid efectivo en hijo: %d\n", geteuid());
		printf("getgid, grupo del usuario eb hijo: %d\n", getgid());
		/*char *path = getenv("PATH");
    
    		if (path != NULL) {
        		printf("El valor de la variable PATH es: %s\n", path);
    		} 
		else {
        		printf("La variable de entorno PATH no está definida.\n");
    		}*/
	
		 // Mostrar direcciones de memoria en el proceso hijo
       		printf("\nDirecciones en el hijo:\n");
        	printf("  Dirección de variable global hijo: %p\n", (void*)&global_var);	
		printf("  Dirección de variable local hijo: %p\n", (void*)&local_var);
        	printf("  Dirección de variable dinámica hijo: %p\n", (void*)dynamic_var);

		
		// Cambiando valores en el proceso hijo
        	global_var = 101;
        	local_var = 201;
        	*dynamic_var = 301;

        	printf("\nValores modificados en el hijo:\n");
        	printf("  Valor de la variable global hijo: %d\n", global_var);	
		printf("  Valor de la variable local hijo: %d\n", local_var);
        	printf("  Valor de la variable dinámica hijo: %d\n", *dynamic_var);

		
	}
	
	else if(pid>0){
		printf("Proceso padre%d\n", getpid());
		printf("getppid, id padre del padre: %d\n", getppid());
		printf("getuid, uid del ususario en padre: %d\n", getuid());
		printf("geteuid, uid efectivo en padre: %d\n", geteuid());
		printf("getgid, grupo del usuario en padre: %d\n", getgid());
		char *shell = getenv("SHELL");
    
    		if (shell != NULL) {
        		printf("El valor de la variable SHELL es: %s\n", shell);
    		} 
		else {
        		printf("La variable de entorno SHELL no está definida.\n");
    		}


		// Mostrar direcciones de memoria en el proceso padre
        	printf("\nDirecciones en el padre:\n");
        	printf("  Dirección de variable global padre: %p\n", (void*)&global_var);
        	printf("  Dirección de variable local padre: %p\n", (void*)&local_var);
        	printf("  Dirección de variable dinámica padre: %p\n", (void*)dynamic_var);

        	// Esperar que el proceso hijo termine
        	wait(NULL);

        	printf("\nValores en el padre (tras cambios en el hijo):\n");
        	printf("  Valor de la variable global: %d\n", global_var);
        	printf("  Valor de la variable local: %d\n", local_var);
        	printf("  Valor de la variable dinámica: %d\n", *dynamic_var);


	}
	 // Liberar la memoria dinámica
    	free(dynamic_var);


    return(EXIT_SUCCESS);
}
