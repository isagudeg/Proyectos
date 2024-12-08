#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char** argv) {
    int socketemi;
    struct sockaddr_in direccionemi, direccionrecep;
    char mensaje[]="HOLA CARACOLAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    socklen_t tamanho= sizeof(struct sockaddr_in);
    uint16_t puerto;
    ssize_t nbytes;

    //Nos aseguramos de que se introducen el puerto del emisor, y la IP y el puerto del receptor por linea de comandos
    if (argc<4){ 
        printf("Tienes que introducir el puerto del emisor, y la IP y el puerto del receptor por linea de comandos");
        exit (EXIT_FAILURE);
    }

    //Completa la dirección del receptor
    puerto = (uint16_t)strtoul(argv[3], NULL, 10); 
    direccionrecep.sin_port = htons(puerto); //pasamos el puerto a orden de red
    direccionrecep.sin_family=AF_INET;
    //convertimos la ip del receptor de textual a binario
    if ( inet_pton (AF_INET , argv[2] , (void *) &direccionrecep.sin_addr.s_addr ) != 1) {
        fprintf ( stderr , "Formato de direccion incorrecto en la direccion del receptor " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Creamos el socket emisor
    socketemi = socket (AF_INET,SOCK_DGRAM,0);
    if ( socketemi < 0){
        perror ( "No se pudo crear el socket " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Completa la dirección del emisor
    puerto = (uint16_t)strtoul(argv[1], NULL, 10); 
    direccionemi.sin_port = htons(puerto); //pasamos el puerto a orden de red
    direccionemi.sin_family=AF_INET;
    direccionemi.sin_addr.s_addr=htonl(INADDR_ANY);

    //Le asignamos la dirección al socket emisor
    if ( bind ( socketemi , (struct sockaddr *) &direccionemi , tamanho ) < 0) {
        perror ( "No se pudo asignar direccion " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Enviamos un mensaje al receptor
    if ( (nbytes=sendto(socketemi, mensaje, sizeof(mensaje),0,(struct sockaddr *)&direccionrecep,tamanho)) < 0) {
        perror ( "No se pudo enviar el mensaje al receptor" ) ;
        exit ( EXIT_FAILURE ) ;
    }
    printf("Número de bytes enviados %zd\n", nbytes);//Imprimimos el numero de bytes enviados

    //Cerramos el socket de emision
    close(socketemi);

    return (EXIT_SUCCESS);
}