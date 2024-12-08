#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>



int main(int argc, char** argv){
    struct stat info;
    int longitud;
    char buffer;

    if(argc!=2){
        printf("Debes incluir el nombre del archivo por klinea de comandos");
        exit(1);
    }
    
    printf("PID: %d\n",getpid());
    printf("Archivo sin abrir\n");
    scanf("%c",&buffer);

    int archivo = open(argv[1], O_RDWR);
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

    char *mapeado = mmap(NULL, longitud, PROT_READ | PROT_WRITE, MAP_SHARED, archivo, 0);
    if (mapeado == MAP_FAILED) {
        perror("Error al mapear el archivo");
        close(archivo);
        return 1;
    }

    printf("Archivo mapeado\n");
    scanf("%c",&buffer);

    munmap(mapeado, longitud);
    close(archivo);


	return (EXIT_SUCCESS);
}
