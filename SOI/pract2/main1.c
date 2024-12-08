#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t pid=fork();

	if(pid==0){
		printf("Proceso hijo: %d\n", getpid());
		printf("getppid, id padre del hijo: %d\n", getppid());
		printf("getuid, uid del ususario en hijo: %d\n", getuid());
		printf("geteuid, uid efectivo en hijo: %d\n", geteuid());
		printf("getgid, grupo del usuario eb hijo: %d\n", getgid());
		char *path = getenv("PATH");
    
    		if (path != NULL) {
        		printf("El valor de la variable PATH es: %s\n", path);
    		} 
		else {
        		printf("La variable de entorno PATH no está definida.\n");
    		}
		
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
	}


    return(EXIT_SUCCESS);
}
