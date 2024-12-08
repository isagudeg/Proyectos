#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>



int main(int argc, char** argv){
    struct stat info;
    int longitud;

    if(argc!=2){
        printf("Debes incluir el nombre del archivo por klinea de comandos");
        exit(1);
    }
    
    int archivo = open(argv[1], O_RDONLY);
    if (archivo == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

    if (fstat(archivo, &info) == -1) {
        perror("Error al obtener información del archivo");
        close(archivo);
        return 1;
    }

    longitud=info.st_size;

    char *mapeado = mmap(NULL, longitud, PROT_READ | PROT_EXEC, MAP_PRIVATE, archivo, 0);
    if (mapeado == MAP_FAILED) {
        perror("Error al mapear el archivo");
        close(archivo);
        return 1;
    }

    for(int i=0; i<longitud; i++){
        printf("%c",mapeado[i]);
    }

    munmap(mapeado, longitud);
    close(archivo);


	return (EXIT_SUCCESS);
}
