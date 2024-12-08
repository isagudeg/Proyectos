#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define MAX 1000 //Tamaño maximo del mensaje


int main(int argc, char** argv) {

    int socketcli;
    struct sockaddr_in direccioncli,direccionserv;
    char mensaje [1000], *a, linea[1000];
    socklen_t tamanho= sizeof(struct sockaddr_in);
    uint16_t puerto;
    ssize_t nbytes;
    FILE *lectura, *escritura;
    int i=0;

    //Nos aseguramos de que se introducen el nombre del fichero, el puerto propio, la IP y el puerto del servidor por linea de comandos
    if (argc!=5){
        printf("Tienes que introducir el nombre del fichero, el puerto propio, la IP y el puerto del servidor por linea de comandos");
        exit (EXIT_FAILURE);
    }

    //Completa la dirección del cliente
    puerto = (uint16_t)strtoul(argv[2], NULL, 10);
    direccioncli.sin_port = htons(puerto); //pasamos el puerto a orden de red
    direccioncli.sin_family=AF_INET;
    direccioncli.sin_addr.s_addr=htonl(INADDR_ANY);


    //Creamos el socket cliente
    socketcli = socket (AF_INET,SOCK_DGRAM,0);
    if ( socketcli < 0){
        perror ( "No se pudo crear el socket " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Le asignamos la dirección al socket cliente
    if ( bind ( socketcli , (struct sockaddr *) &direccioncli , tamanho ) < 0) {
        perror ( "No se pudo asignar direccion " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //Abrimos el archivo en modo lectura
    lectura = fopen (argv[1],"r");
    if (lectura==NULL){
            printf("Error al leer el archivo de entrada");
            exit(EXIT_FAILURE);
    } 

    //Transformamos el nombre del archivo a mayusculas para guardar la respuesta del servidor
    while (argv[1][i] != '\0'){
        argv[1][i] = toupper (argv[1][i]);
        i++;
    }

    //Abrimos el nuevo archivo destino en modo escritura
    escritura = fopen (argv[1],"wr");
    if (escritura==NULL){
        printf("Error al leer el archivo de salida");
        exit(EXIT_FAILURE);
    } 

    //Completa la dirección del servidor
    puerto = (uint16_t)strtoul(argv[4], NULL, 10);
    direccionserv.sin_port = htons(puerto); //pasamos el puerto a orden de red
    direccionserv.sin_family=AF_INET;
    inet_pton(AF_INET, argv[3],(void *)&direccionserv.sin_addr.s_addr);


    //Leemos el archivo inicial línea a línea, se lo enviamos al servidor y escribimos el mensaje devuelto en el archivo destino
    do{
        sleep(1);
        a=fgets(linea, 1000, lectura); //leemos una linea del archivo
        if (a!=NULL){
            //Enviamos como mensaje la linea leida a el cliente
            if ( (nbytes=sendto(socketcli, linea,strlen(linea),0,(struct sockaddr *)&direccionserv,tamanho)) < 0) {
                perror ( "No se pudo enviar el mensaje al receptor" ) ;
                exit ( EXIT_FAILURE ) ;
            }
            printf("Número de bytes enviados %zd\n", nbytes); //Imprimimos el numero de bytes enviados
            
            //Recibimos la lñínea enviada pasada a mayusculas
            if((nbytes=recvfrom(socketcli,mensaje,MAX,0,(struct sockaddr *)&direccionserv,&tamanho)) ==-1) {
                perror ( "No se pudo recibir el mensaje en el receptor" ) ;
                exit ( EXIT_FAILURE ) ;
            }

            //Añadimos un salto de linea al final del mensaje recibido
            mensaje[nbytes]='\0';
            fprintf(escritura,"%s", mensaje); //Escribimos la linea pasada a mayusculas en el archivo destino
            printf("Se ha recibido %s\n", mensaje); //Imprimimos el mensaje recibido (la linea pasada a mayusculas)
        }
    }while (a!=NULL); //Repite mientras haya lineas en el archivo
    printf("\n");
    
    //Cerramos los archivo
    fclose (lectura);
    fclose (escritura);
    
    //Cerramos el socket cliente
    if ( close (socketcli) < 0) {
        perror ( "No se pudo cerrar el socket de servidor" ) ;
        exit ( EXIT_FAILURE ) ;
    }

    return (EXIT_SUCCESS);
}