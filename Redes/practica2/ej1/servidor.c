#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    int socket_ser, socket_con;
    struct sockaddr_in direccion,ipportcli;
    ssize_t nbytes;
    socklen_t tamanho;
    char mensaje[1000]="HOLA CARACOLA",mensaje2[1000]="Buenas noches";
    uint16_t puerto;

    if(argc!=2){
        printf("No se ha añadido el puerto");
        exit(EXIT_FAILURE);
    }
    else{
        puerto= (uint16_t)strtoul(argv[1],NULL,10);
    }

    socket_ser=socket(AF_INET,SOCK_STREAM,0);
    if(socket_ser < 0){
        perror("No se pudo crear el socket") ;
        exit( EXIT_FAILURE ) ;
    }

    direccion.sin_family=AF_INET;
    direccion.sin_port = htons(puerto);
    if(bind(socket_ser,(struct sockaddr *) &direccion, sizeof(struct sockaddr_in)) < 0){
        perror ( "No se pudo asignar direccion\n");
        exit( EXIT_FAILURE ) ;
    }

    if(listen(socket_ser, 99) < 0){
        perror ( "El servidor no está escuchando\n");
        exit( EXIT_FAILURE ) ;
    }

    if((socket_con = accept(socket_ser,( struct sockaddr *) &ipportcli,&tamanho)) < 0){
        perror ( "No se pudo aceptar la conexion\n" ) ;
        exit( EXIT_FAILURE ) ;
    }
    else{
        char miiptext [INET_ADDRSTRLEN];
        if(inet_ntop(AF_INET,(const void*)&ipportcli.sin_addr.s_addr,miiptext,INET_ADDRSTRLEN)!=NULL){
            printf("Dirección IP del cliente: %s\n", miiptext);
        }
        printf("Puerto del cliente: %u\n", ipportcli.sin_port);
    }

    if((nbytes=send(socket_con,mensaje, strlen(mensaje),0)) < 0){
        perror ( "No se pudo enviar el mensaje\n" ) ;
        exit( EXIT_FAILURE ) ;
    }

    if((nbytes=send(socket_con,mensaje2, strlen(mensaje2),0)) < 0){
        perror ( "No se pudo enviar el mensaje\n" ) ;
        exit( EXIT_FAILURE ) ;
    }

    printf("Número de bytes enviador: %zd\n", nbytes);

    if(close(socket_con) < 0){
        perror ( "No se pudo cerrar el socket de conexión\n" ) ;
        exit( EXIT_FAILURE ) ;
    }

    if(close(socket_ser) < 0){
        perror ( "No se pudo cerrar el socket servidor\n" ) ;
        exit( EXIT_FAILURE ) ;
    }

   return (EXIT_SUCCESS);
}
