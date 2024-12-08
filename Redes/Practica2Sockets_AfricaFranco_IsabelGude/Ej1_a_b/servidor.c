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

    int socketserv, socketcon;
    struct sockaddr_in direccion, ippuertocliente;
    socklen_t tamanho;
    char mensaje[1000]="Hola caracola";
    size_t nbytes;
    uint16_t puerto;

    //Nos aseguramos de que se introducen el puerto por linea de comandos
    if (argc!=2){
        printf("Tienes que introducir el puerto por linea de comandos");
        exit (EXIT_FAILURE);
    }
    puerto = (uint16_t)strtoul(argv[1], NULL, 10);
    direccion.sin_port = htons(puerto);

    //Convertimos la ip de textual a binario
    if ( inet_pton (AF_INET , "127.0.0.1" , (void *) &direccion.sin_addr.s_addr ) != 1) {
        fprintf ( stderr , "Formato de direccion incorrecto " ) ;
        exit ( EXIT_FAILURE ) ;
    }
    direccion.sin_family=AF_INET;

    //Creamos el socket servidor
    socketserv = socket (AF_INET, SOCK_STREAM,0);
    if ( socketserv < 0){
        perror ( "No se pudo crear el socket " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Le asignamos una dirección al socket servidor
    if ( bind ( socketserv , (struct sockaddr *) &direccion , sizeof (struct sockaddr_in ) ) < 0) {
        perror ( "No se pudo asignar direccion " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Ponemos el servidor a escuchar
    if (listen(socketserv, 99) < 0){
        perror ("Servidor no está escuchando");
        exit ( EXIT_FAILURE );
    }

    //Aceptamos la conexión con el cliente
    if ( ( socketcon = accept ( socketserv , (struct sockaddr *) &ippuertocliente , &tamanho) ) < 0) {
        perror ( "No se pudo aceptar la conexion" ) ;
        exit ( EXIT_FAILURE ) ;
    }
    else{
        //Pasamos la IP del cliente de binario a textual para poder imprimirla
        char miiptext [INET_ADDRSTRLEN ] ;
        if ( inet_ntop (AF_INET , (const void *) &ippuertocliente.sin_addr.s_addr , miiptext , INET_ADDRSTRLEN) != NULL) {
            printf ( "Dirección IP del cliente: %s \n" , miiptext ) ;
        }
        printf("Puerto del cliente: %u\n", ippuertocliente.sin_port);
    }   

    //Enviamos un mensaje a el cliente
    if ( (nbytes=send(socketcon, mensaje, strlen(mensaje),0)) < 0) {
        perror ( "No se pudo enviar el mensaje" ) ;
        exit ( EXIT_FAILURE ) ;
    }
    printf ("Número de bytes enviados %zd\n", nbytes);

    //Cerramos el socket de conexión 
    if ( close (socketcon) < 0) {
        perror ( "No se pudo cerrar el socket de conexión" ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Cerramos el socket servidor
    if ( close (socketserv) < 0) {
        perror ( "No se pudo cerrar el socket de servidor" ) ;
        exit ( EXIT_FAILURE ) ;
    }

    return (EXIT_SUCCESS);
}