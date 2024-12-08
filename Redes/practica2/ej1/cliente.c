#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    int socket_cli;
    struct sockaddr_in direccion;
    socklen_t tamanho;
    char mensaje[1000];
    uint16_t puerto;
    ssize_t nbytes;

    if(argc!=3){
        printf("No se ha añadido el puerto o la ip");
        exit(EXIT_FAILURE);
    }
    else{
        puerto= (uint16_t)strtoul(argv[1],NULL,10);
    }

    socket_cli=socket(AF_INET,SOCK_STREAM,0);
    if(socket_cli < 0){
        perror("No se pudo crear el socket");
        exit( EXIT_FAILURE );
    }

    direccion.sin_family=AF_INET;
    direccion.sin_port = htons(puerto);
    if(inet_pton(AF_INET,argv[2],(void *)&direccion.sin_addr) !=1 ){
        fprintf(stderr,"Formato de dirección fallida");
        exit( EXIT_FAILURE );
    }
    
    if(connect(socket_cli,(struct sockaddr *) &direccion, sizeof(struct sockaddr_in)) < 0){
        perror ("No se pudo asignar direccion\n");
        exit( EXIT_FAILURE ) ;
    }
    while( (nbytes=recv(socket_cli,mensaje,5,0)) > 0 ){
        mensaje[nbytes] = '\0'; 
        printf("Mensaje: %s\n",mensaje);
        printf("Número de bytes recibidos: %zd\n",nbytes);
        }
    if((nbytes = recv(socket_cli, mensaje, 1000, 0)) < 0){
        perror ("No se pudo recibir el mensaje\n");
        exit( EXIT_FAILURE ) ;
    }
    else if(nbytes==0){
        printf("Se ha cerrado el socket de conexión\n");
    }

    if(close(socket_cli) < 0){
        perror ( "No se pudo cerrar el socket servidor\n" ) ;
        exit( EXIT_FAILURE ) ;
    }



    return (EXIT_SUCCESS);
}
