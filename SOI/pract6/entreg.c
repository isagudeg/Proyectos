#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <ctype.h>
#include <string.h>

static void gestion(int);



int main(int argc, char** argv){
    struct stat info;
    int longitud;
    int padre, hijo;
    char* buffer = NULL;

    /*if(argc!=3){
        printf("Debes incluir el nombre del archivo de entrada y de salida por linea de comandos\n");
        exit(1);
    }*/
    
    padre=getpid();
    printf("PID proceso padre: %d\n",padre);
    printf("Archivo sin abrir\n");

    if (signal(SIGUSR1, gestion) == SIG_ERR){
		printf("Error al crear gestor 1\n");
	}

    //int archivo = open(argv[1], O_RDONLY);
    int archivo = open("hola.txt", O_RDONLY);
    if (archivo == -1) {
        perror("Error al abrir el archivo\n");
        return 1;
    }

    if (fstat(archivo, &info) == -1) {
        perror("Error al obtener información del archivo\n");
        close(archivo);
        return 1;
    }

    longitud=info.st_size;

    char *mapeado = mmap(NULL, longitud, PROT_READ, MAP_SHARED, archivo, 0);
    if (mapeado == MAP_FAILED) {
        perror("Error al mapear el archivo\n");
        close(archivo);
        return 1;
    }

    if((hijo = fork()) == -1){
		printf("Error al crear el hijo\n");
	}
	else if(hijo == 0){ //PROCESO HIJO
        wait(NULL);
        printf("Hola soy el hijo\n");
        printf("error\n");
        int tambuffer=sizeof(buffer);
        printf("%d", tambuffer);
        for(int i=0; i<tambuffer;i++){
            if(buffer[i]==' '){
                buffer[i]= '*';
            }
        }
        wait(NULL);
        for(int i=tambuffer; i<sizeof(buffer);i++){
            if(buffer[i]==' '){
                buffer[i]= '*';
            }
        }
        kill(padre,SIGUSR1);

    }
    else if(hijo!=0){ //PROCESO PADRE
        printf("Hola soy el padre\n");
        for(int i=0; i<longitud; i++){
            if(!isdigit(mapeado[i])){
                buffer+=tolower(mapeado[i]);
            }
            else{
                for(int j=0; j<atoi(mapeado[i]);j++){
                    buffer += ' ';
                }
            }
            if(i==longitud/2){
                kill(hijo,SIGUSR1);
            }
        }
        kill(hijo,SIGUSR1);
        wait(NULL);

        //int archivo2 = open(argv[2], O_CREAT,S_IWUSR);
        int archivo2 = open("adios.txt", O_CREAT,S_IWUSR);
        if (archivo2 == -1) {
            perror("Error al abrir el archivo\n");
            return 1;
        }
        if (ftruncate(archivo2, strlen(buffer)) == -1) {
            perror("Error al cambiar el tamaño del archivo");
            close(archivo2);
            return 1;
        }

        char *mapeado2 = mmap(NULL, longitud, PROT_READ, MAP_SHARED, archivo2, 0);
        if (mapeado2 == MAP_FAILED) {
            perror("Error al mapear el archivo\n");
            close(archivo2);
            return 1;
        }

        memcpy(archivo2, buffer, strlen(buffer));

        close(archivo2);

    }


    munmap(mapeado, longitud);
    close(archivo);


	return (EXIT_SUCCESS);
}

static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
	switch (numero_de_senhal) {
		case SIGUSR1: /*Entra señal SIGUSR1*/
		printf("Señal 1 enviada. Soy %d\n",getpid()); 
		break;
	}
	return; 
}
