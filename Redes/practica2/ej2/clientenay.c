#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

int main(int argc, char** argv) {
    int socket_cli,i=0;
    struct sockaddr_in direccion;
    socklen_t tamanho;
    char mensajenullo[1000]="es nulo", *comprobacio, linea[1000],mensaje[1000];
    uint16_t puerto;
    ssize_t nbytes;
    FILE *arquivoin, *arquivoout;

    if(argc!=4){
        printf("No se ha añadido el nombre del archivo, ip o la puerto");
        exit(EXIT_FAILURE);
    }
    

    arquivoin= fopen(argv[1],"r");
    if(arquivoin==NULL){
        printf("ERROR al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    while (argv[1][i] != '\0') {  
        argv[1][i] = toupper(argv[1][i]);
        i++;
    }

    arquivoout= fopen(argv[1],"w");
    if(arquivoout==NULL){
        printf("ERROR al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    

    puerto= (uint16_t)strtoul(argv[3],NULL,10);
        
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

    do{

        comprobacio = fgets(linea,1000,arquivoin);
        if(comprobacio!=NULL){
            if((nbytes=send(socket_cli, linea, strlen(linea),0)) < 0){
                perror ( "No se pudo enviar el mensaje\n" ) ;
                exit( EXIT_FAILURE ) ;
            }
        }
        else{
            if((nbytes=send(socket_cli, mensajenullo, strlen(mensajenullo),0)) < 0){
                perror ( "No se pudo enviar el mensaje\n" ) ;
                exit( EXIT_FAILURE ) ;
            }

        }


        if((nbytes = recv(socket_cli, mensaje, 1000, 0)) < 0){
        perror ("No se pudo recibir el mensaje\n");
        exit( EXIT_FAILURE ) ;
        }
        else{
            mensaje[nbytes] = '\0'; 
            printf("%s\n",mensaje);
            fprintf(arquivoout,"%s",mensaje);
        }
    }while (comprobacio!=NULL);

    fclose(arquivoin);
    fclose(arquivoout);

    if(close(socket_cli) < 0){
        perror ( "No se pudo cerrar el socket servidor\n" ) ;
        exit( EXIT_FAILURE ) ;
    }

    return (EXIT_SUCCESS);
}
