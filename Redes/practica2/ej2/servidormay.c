#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

int main(int argc, char** argv) {
    int socket_ser, socket_con,i;
    struct sockaddr_in direccion,ipportcli;
    ssize_t nbytes;
    socklen_t tamanho;
    char mensaje[1000];
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
    //direccion.sin_addr.s_addr = INADDR_ANY;//////////////
    if(bind(socket_ser,(struct sockaddr *) &direccion, sizeof(struct sockaddr_in)) < 0){
        perror ( "No se pudo asignar direccion\n");
        exit( EXIT_FAILURE ) ;
    }

    if(listen(socket_ser, 99) < 0){
        perror ( "El servidor no está escuchando\n");
        exit( EXIT_FAILURE ) ;
    }

    tamanho = sizeof(ipportcli);
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

    while(strcmp(mensaje,"es nulo")!=0){
        i=0;

        if((nbytes = recv(socket_con, mensaje, 1000, 0)) < 0){
            perror ("No se pudo recibir el mensaje\n");
            exit( EXIT_FAILURE ) ;
        }
        else if(nbytes==0){
            printf("Se ha cerrado el socket de conexión\n");
        }
            
        mensaje[nbytes] = '\0';  

        if(strcmp(mensaje,"es nulo")!=0){

            printf("%s\n",mensaje);
            while (mensaje[i] != '\0') {  
                mensaje[i] = toupper(mensaje[i]);
                i++;
            }

            if((nbytes=send(socket_con, mensaje, strlen(mensaje),0)) < 0){
                perror ( "No se pudo enviar el mensaje\n" ) ;
                exit( EXIT_FAILURE ) ;
            }
                
        }
    }

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
