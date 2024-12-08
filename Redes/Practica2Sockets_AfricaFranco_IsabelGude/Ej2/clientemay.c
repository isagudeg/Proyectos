#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

//Código realizado por África Franco e Isabel Gude del Grupo 3

int main(int argc, char** argv) {

    int socketcli;
    struct sockaddr_in direccion;
    char mensaje [1000], *a, linea[1000];
    uint16_t puerto;
    ssize_t nbytes;
    FILE *lectura, *escritura;
    int i=0;

    //Nos aseguramos de que se introducen el puerto y la IP por linea de comandos
    if (argc!=4){
        printf("Tienes que introducir el puerto y la IP del servidor por linea de comandos");
        exit (EXIT_FAILURE);
    }
    puerto = (uint16_t)strtoul(argv[3], NULL, 10);
    direccion.sin_port = htons(puerto);

    //convertimos la ip de textual a binario
    if ( inet_pton (AF_INET , argv[2] , (void *) &direccion.sin_addr.s_addr ) != 1) {
        fprintf ( stderr , "Formato de direccion incorrecto " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    direccion.sin_family=AF_INET;

    //Creamos el socket cliente
    socketcli = socket (AF_INET, SOCK_STREAM,0);
    if ( socketcli < 0){
        perror ( "No se pudo crear el socket " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Solicitamos la conexión con el sevidor
    if ( connect ( socketcli, (struct sockaddr *) &direccion , sizeof (struct sockaddr_in ) ) < 0) {
        perror ( "No se pudo asignar direccion " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Abrimos el archivo en modo lectura
    lectura = fopen (argv[1],"r");
    if (lectura==NULL){
            printf("Error al leer el archivo de entrada");
            exit(EXIT_FAILURE);
    } 

    //Transformamos el nombre del archivo a mayusculas para guardar la respuesta del servidor
    while (argv[1][i] != '\0'){
        argv[1][i] = toupper (argv[1][i]);
        i++;
    }

    //Abrimos el nuevo archivo destino en modo escritura
    escritura = fopen (argv[1],"wr");
    if (escritura==NULL){
        printf("Error al leer el archivo de salida");
        exit(EXIT_FAILURE);
    } 

    //Leemos el archivo inicial línea a línea, se lo enviamos al servidor y escribimos el mensaje devuelto en el archivo destino
    do{
        sleep (5);
        a=fgets(linea, 1000, lectura);
        if (a!=NULL){
            if ( (nbytes=send(socketcli, linea, strlen(linea),0)) < 0) {
                perror ( "No se pudo enviar el mensaje" ) ;
                exit ( EXIT_FAILURE ) ;
            }

            if ( (nbytes=recv(socketcli, mensaje, 1000,0)) < 0) {
            perror ( "No se pudo recibir el mensaje" ) ;
            exit ( EXIT_FAILURE ) ;
            }

            else if (nbytes==0){
                perror("Se ha cerrado el socket de conexión");
                exit ( EXIT_FAILURE ) ;
            }
            mensaje[nbytes]='\0';
            fprintf(escritura,"%s", mensaje);
            printf("Se ha recibido %s", mensaje);
        }
    }while (a!=NULL);
    printf("\n");
    
    //Cerramos los archivo
    fclose (lectura);
    fclose (escritura);
    
    //Cerramos el socket cliente
    if ( close (socketcli) < 0) {
        perror ( "No se pudo cerrar el socket de servidor" ) ;
        exit ( EXIT_FAILURE ) ;
    }

    return (EXIT_SUCCESS);
}