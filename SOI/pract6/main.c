#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

void gestion(int sig){
    if(sig == SIGUSR1){
        printf("                                      señal1\n");
    }
}

int main(int argc, char *argv[]){

    //Comprobamos que se pasan los argumentos necesarios por linea de comandos
    if(argc!=3){
        printf("Debes incluir el nombre del archivo de entrada y de salida por linea de comandos\n");
        exit(1);
    }

    //Configuramos el gestor de señales
    signal(SIGUSR1, gestion);

    //Abrimos los archivos de entrada y salida
    int input, output;
    if((input = open(argv[1], O_RDONLY)) == -1){
        perror("Error al abrir el archivo de entrada");
        exit(EXIT_FAILURE);
    }   

    if((output = open(argv[2], O_CREAT | O_RDWR, S_IWUSR | S_IRUSR)) == -1){
        perror("Error al abrir el archivo de salida");
        exit(EXIT_FAILURE);
    }

    //Guardamos los datos del archivo de entrada
    struct stat datosEntrada, datosSalida;

    if(fstat(input, &datosEntrada) == -1){
        perror("Error al guardar los datos del archivo de entrada");
        exit(EXIT_FAILURE);
    }

    int tamano = 0; //Creamos la variable tamaño

    //Mapeamos el archivo de entrada
    char *mapaEntrada = NULL, *mapaSalida = NULL;
    if((mapaEntrada = mmap(NULL, datosEntrada.st_size, PROT_READ, MAP_SHARED, input, 0 )) == MAP_FAILED){
        perror("Error al mapear el archivo de entrada");
        exit(EXIT_FAILURE);
    }

    //Calculamos el tamaño final que tendrá el archivo de salida
    int aux = 0;
    for(int i = 0; i < datosEntrada.st_size; i++){
        if(isdigit(mapaEntrada[i])){
            aux = mapaEntrada[i] - '0';
            tamano += aux;
        }else{
            tamano++;
        }    
    }

    //Cambiamos el tamaño del archivo de salida al que acabamos de calcular
    if (truncate(argv[2], tamano) == -1) {
        perror("Error truncando el archivo");
        exit(EXIT_FAILURE);
    }

    //Guardamos los datos del archivo de salida
    if(fstat(input, &datosSalida) == -1){
        perror("Error al guardar los datos del archivo de salida");
        exit(EXIT_FAILURE);
    }

    //Mapeamos el archivo de salida
    if((mapaSalida = mmap(NULL, datosSalida.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, output, 0)) == MAP_FAILED){
        perror("Error al mapear el archivo de salida");
        exit(EXIT_FAILURE);
    }

    //Creamos el buffer de memoria compartida
    char *buffer = NULL;
    if((buffer = mmap(NULL, tamano, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0)) == MAP_FAILED){
        perror("Error al mapear el mapa de buffer");
        exit(EXIT_FAILURE);
    }

    //Creamos el hijo
    int hijo = 0;
    if((hijo = fork()) == -1){
        perror("Error al crear al hijo");
        exit(EXIT_FAILURE);
    }else if(hijo == 0){  //Proceso hijo

        //Espera la señal del padre para empezar
        pause();

        //Añade '*' por cada espacio que haya en la primera mitad buffer
        for(int i = 0; i < tamano/2; i++){
            if(buffer[i] == ' '){
                buffer[i] = '*';
            }else if(isdigit(buffer[i])){
                buffer[i] = ' ';
            }else{
                buffer[i] = buffer[i];
            }
        }

        //Espera una señal del padre
        pause();

        //Añade '*' por cada espacio que haya en la segunda mitad buffer
        for(int i = tamano/2; i < tamano; i++){
            if(buffer[i] == ' '){
                buffer[i] = '*';
            }else if(isdigit(buffer[i])){
                buffer[i] = ' ';
            }else{
                buffer[i] = buffer[i];
            }
        }

        //Finaliza el proceso hijo
        exit(1);

    }else if(hijo > 1){ //Proceso padre
        int numero, index = 0;

        //Pasa a minúsculas las letras mayusculas y escribe la cantidad de espacios necesaria por cada número
        //de la primera mitad del archivo de netrada y lo guarda en buffer
        for(int i = 0; i < tamano/2; i++){
            if(isdigit(mapaEntrada[i])){
                numero = mapaEntrada[i] - '0';
                for(int j = 0; j < numero; j++){
                    buffer[index] = ' ';
                    index++;
                }
            }else if(isupper(mapaEntrada[i])){
                buffer[index] = tolower(mapaEntrada[i]);
                index++;
            }else if(mapaEntrada[i] == ' '){
                buffer[index] = '1';
                index++;
            }else{
                buffer[index] = mapaEntrada[i];
                index++;
            }
        }

        sleep(1); //Espera a que se cree el hijo
        kill(hijo, SIGUSR1); //Mandas señal al hijo para que empiece

        //Pasa a minúsculas las letras mayusculas y escribe la cantidad de espacios necesaria por cada número
        //de la segunda mitad del archivo de netrada y lo guarda en buffer
        for(int i = tamano/2; i < tamano; i++){
            if(isdigit(mapaEntrada[i])){
                numero = mapaEntrada[i] - '0';
                for(int j = 0; j < numero; j++){
                    buffer[index] = ' ';
                    index++;
                }
            }else if(isupper(mapaEntrada[i])){
                buffer[index] = tolower(mapaEntrada[i]);
                index++;
            }else if(mapaEntrada[i] == ' '){
                buffer[index] = '1';
                index++;
            }else{
                buffer[index] = mapaEntrada[i];
                index++;
            }
        }

        sleep(1); //Espera a que el hijo tçse pause
        kill(hijo, SIGUSR1); //Avisa al hijo para que continue
        wait(NULL); //Espera a que el hijo termine

        //Copia el contenido de buffer en el mapa del archivo de salida
        memcpy(mapaSalida, buffer, tamano);

        //Cerramos el archivo de entrada
        if(munmap(mapaEntrada, strlen(mapaSalida)) == -1){
            perror("Error al cerrar el archivo de entrada");
            exit(EXIT_FAILURE);
        }

        //Cerramos el buffer de memoria compartida
        if(munmap(buffer, strlen(buffer)) == -1){
            perror("Error al cerrar el mapa de buffer");
            exit(EXIT_FAILURE);
        }

        //Cerramos los identificadores de los archivos de netrada y salida
        close(input);
        close(output);

        //Cerramos el archivo de salida
        if(munmap(mapaSalida, strlen(mapaSalida)) == -1){
            perror("Error al cerrar el archivo de salida");
            exit(EXIT_FAILURE);
        }

        exit(1);
    }
}