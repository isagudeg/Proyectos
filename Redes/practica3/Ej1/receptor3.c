#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 1000

int main(int argc, char** argv) {
    int socketrec,nfloats;
    struct sockaddr_in direccionrecep, direccionemi;
    float mensaje[MAX];
    socklen_t tamanho= sizeof(struct sockaddr_in);
    uint16_t puerto;
    ssize_t nbytes;

    //Nos aseguramos de que se introducen la IP y el puerto por linea de comandos
    if (argc!=2){ 
        printf("Tienes que introducir la IP y el puerto del servidor por linea de comandos");
        exit (EXIT_FAILURE);
    }


    puerto = (uint16_t)strtoul(argv[1], NULL, 10); 
    direccionrecep.sin_port = htons(puerto); //pasamos el puerto a orden de red
    direccionrecep.sin_family=AF_INET;
    direccionrecep.sin_addr.s_addr=INADDR_ANY;


    //Creamos el socket emisor
    socketrec = socket (AF_INET,SOCK_DGRAM,0);
    if ( socketrec < 0){
        perror ( "No se pudo crear el socket receptor " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Le asignamos una dirección al socket receptor
    if( bind (socketrec , (struct sockaddr *) &direccionrecep , tamanho ) < 0) {
        perror ( "No se pudo asignar direccion al receptor " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Enviamos un mensaje a el cliente
    if((nbytes=recvfrom(socketrec,mensaje,MAX,0,(struct sockaddr *)&direccionemi,&tamanho)) ==-1) {
        perror ( "No se pudo recibir el mensaje en el receptor" ) ;
        exit ( EXIT_FAILURE ) ;
    }

    char ipemisor[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(direccionemi.sin_addr), ipemisor,INET_ADDRSTRLEN);
    printf("Número de bytes recibidos: %zd\n", nbytes);

    nfloats=nbytes/4;
    for(int i=0;i<nfloats;i++){
        printf("Número recibido: %f\n",mensaje[i]);
    }
    printf("Ip del emisor: %s\nPuerto del emisor: %d\n",ipemisor,ntohs(direccionemi.sin_port));

    close(socketrec);

    return (EXIT_SUCCESS);
}