#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

//Código realizado por África Franco e Isabel Gude del Grupo 3

int main(int argc, char** argv) {

    int socketcli;
    struct sockaddr_in direccion;
    char mensaje [1000];
    uint16_t puerto;
    ssize_t nbytes;

    //Nos aseguramos de que se introducen la IP y el puerto por linea de comandos
    if (argc!=3){ 
        printf("Tienes que introducir la IP y el puerto del servidor por linea de comandos");
        exit (EXIT_FAILURE);
    }


    puerto = (uint16_t)strtoul(argv[2], NULL, 10); 
    direccion.sin_port = htons(puerto); //pasamos el puerto a orden de red

    //convertimos la ip de textual a binario
    if ( inet_pton (AF_INET , argv[1] , (void *) &direccion.sin_addr.s_addr ) != 1) {
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

    //Recibimos el mensaje del servidor
    if ( (nbytes=recv(socketcli, mensaje, 1000, 0)) < 0) {
        perror ( "No se pudo recibir el mensaje" ) ;
        exit ( EXIT_FAILURE ) ;
    }
    else if (nbytes==0){
        perror("Se ha cerrado el socket de conexión");
        exit ( EXIT_FAILURE ) ;
    }
    mensaje[nbytes]='\0';
    printf("Se ha recibido -%s- con %zd bytes\n", mensaje, nbytes);

    //Cerramos el socket cliente
    if ( close (socketcli) < 0) {
        perror ( "No se pudo cerrar el socket de servidor" ) ;
        exit ( EXIT_FAILURE ) ;
    }

    return (EXIT_SUCCESS);
}