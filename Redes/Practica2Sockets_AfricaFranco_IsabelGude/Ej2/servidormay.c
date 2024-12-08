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

    int socketserv, socketcon;
    struct sockaddr_in direccion, ippuertocliente;
    socklen_t tamanho;
    char mensaje[1000]="No es nulo";
    size_t nbytes;
    uint16_t puerto;
    int i=0;

    //Nos aseguramos de que se introducen el puerto por linea de comandos
    if (argc!=2){
        printf("Tienes que introducir el puerto por linea de comandos");
        exit (EXIT_FAILURE);
    }
    puerto = (uint16_t)strtoul(argv[1], NULL, 10);

    //Rellenamos la estructura dirección
    direccion.sin_port = htons(puerto);
    direccion.sin_family=AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;

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

    while (1){

        //Aceptamos la conexión con el cliente
        tamanho = sizeof(ippuertocliente);   
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

        //Recivimos del cliente las lineas una a una, las convertimos a mayúsculas y se las devolvemos
        while( (nbytes=recv(socketcon,mensaje,1000,0)) > 0 ){
            i=0;
            
            mensaje[nbytes]='\0';
            
            printf("Se ha recibido %s", mensaje);

            while (mensaje[i] != '\0'){
                mensaje[i] = toupper (mensaje[i]);
                i++;
            }

            if ( (nbytes=send(socketcon, mensaje, strlen(mensaje),0)) < 0) {
                perror ( "No se pudo enviar el mensaje" ) ;
                exit ( EXIT_FAILURE ) ;
            }
        }
        printf("\n");  
        if (nbytes< 0) {
            perror ( "No se pudo recibir el mensaje" ) ;
            exit ( EXIT_FAILURE ) ;
        }
    }

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