#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define MAX 100 //Tamaño maximo del mensaje


int main(int argc, char** argv) {

    int socketserv;
    struct sockaddr_in direccionser, direccioncli;
    socklen_t tamanho= sizeof(struct sockaddr_in);
    char mensaje[1000]="No es nulo";
    size_t nbytes;
    uint16_t puerto;
    int i=0;

    //Nos aseguramos de que se introducen el puerto por linea de comandos
    if (argc!=2){
        printf("Tienes que introducir el puerto por linea de comandos");
        exit (EXIT_FAILURE);
    }
    puerto = (uint16_t)strtoul(argv[1], NULL, 10); //convertimos el puerto a una cadena de enteros

    //Rellenamos la estructura dirección del servidor
    direccionser.sin_port = htons(puerto);
    direccionser.sin_family=AF_INET;
    direccionser.sin_addr.s_addr = INADDR_ANY;

    //Creamos el socket servidor
    socketserv = socket (AF_INET,SOCK_DGRAM,0);
    if ( socketserv < 0){
        perror ( "No se pudo crear el socket " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Le asignamos la dirección al socket servidor
    if ( bind ( socketserv , (struct sockaddr *) &direccionser , sizeof (struct sockaddr_in ) ) < 0) {
        perror ( "No se pudo asignar direccion " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Recibimos mensajes del cliente 
    while(1){
        //Recibe un mensaje a el cliente
        if((nbytes=recvfrom(socketserv,mensaje,MAX,0,(struct sockaddr *)&direccioncli,&tamanho)) ==-1) {
            perror ( "No se pudo recibir el mensaje en el receptor" ) ;
            exit(EXIT_FAILURE) ;
        }
        mensaje[nbytes]='\0';//Añadimos un salto de linea al final del mensaje recibido

        //Obtenemos la dirección IP y el puerto del cliente
        char ipemisor[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(direccioncli.sin_addr), ipemisor,INET_ADDRSTRLEN);
        printf("\nMensaje recibido: %s\nNúmero de bytes recividos: %zd\nIp del emisor: %s\nPuerto del emisor: %d\n",mensaje, nbytes,ipemisor,ntohs(direccioncli.sin_port)); //Imprimimos la información
        
        //Pasamos el mensaje recibido a mayusculas
        for(i=0;i<strlen(mensaje);i++){
            mensaje[i] = toupper (mensaje[i]);
        }

        //Enviamos el mensaje ya pasado a mayusculas a el cliente
        if ( (nbytes=sendto(socketserv, mensaje, strlen(mensaje),0,(struct sockaddr *)&direccioncli,tamanho)) < 0) {
            perror ( "No se pudo enviar el mensaje al receptor" ) ;
            exit ( EXIT_FAILURE ) ;
        }
        printf("Número de bytes enviados %zd\n", nbytes); //Imprimimos el numero de bytes enviados
}

    //Cerramos el socket servidor
    if ( close (socketserv) < 0) {
        perror ( "No se pudo cerrar el socket de servidor" ) ;
        exit ( EXIT_FAILURE ) ;
    }

    return (EXIT_SUCCESS);
}