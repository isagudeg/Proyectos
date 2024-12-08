#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 1000 //Tamaño máximo del mensaje que recibe

int main(int argc, char** argv) {
    int socketrec;
    struct sockaddr_in direccionrecep, direccionemi;
    char mensaje[MAX];
    socklen_t tamanho= sizeof(struct sockaddr_in);
    uint16_t puerto; //Puerto del receptor
    ssize_t nbytes; //Numero de bytes recibidos

    //Nos aseguramos de que se introducen su puerto por linea de comandos
    if(argc<2){ 
        printf("Tienes que introducir el puerto del receptor por linea de comandos");
        exit (EXIT_FAILURE);
    }

    //Completa la dirección del receptor
    puerto = (uint16_t)strtoul(argv[1], NULL, 10); 
    direccionrecep.sin_port = htons(puerto); //pasamos el puerto a orden de red
    direccionrecep.sin_family=AF_INET;
    direccionrecep.sin_addr.s_addr=INADDR_ANY;

    //Creamos el socket receptor
    socketrec = socket (AF_INET,SOCK_DGRAM,0);
    if ( socketrec < 0){
        perror ( "No se pudo crear el socket receptor " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Le asignamos una direccion al socket receptor
    if( bind (socketrec , (struct sockaddr *) &direccionrecep , tamanho ) < 0) {
        perror ( "No se pudo asignar direccion al receptor " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //recibimos un mensaje del emisor
    if((nbytes=recvfrom(socketrec,mensaje,MAX,0,(struct sockaddr *)&direccionemi,&tamanho)) ==-1) {
        perror ( "No se pudo recibir el mensaje en el receptor" ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Conevretimos la direccion IP del emisor de formato red a texto
    char ipemisor[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(direccionemi.sin_addr), ipemisor,INET_ADDRSTRLEN);
    printf("Mensaje recuibido: %s\n",mensaje); //Imprimimos el mensaje recibido
    printf("Número de bytes enviados: %zd\nIp del emisor: %s\nPuerto del emisor: %d\n", nbytes,ipemisor,ntohs(direccionemi.sin_port)); //Imprimimos info sobre el mensaje y el emisor

    //Cerramos el socket receptor
    close(socketrec);

    return (EXIT_SUCCESS);
}