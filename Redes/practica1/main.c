#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ether.h>


struct in_addr miip ;
int main(int argc, char** argv) {
/*
    if( inet_pton ( AF_INET , "193.110.128.200" , ( void * ) &miip ) != 1) {
        fprintf( stderr , "Formato de direccion incorrecto " ) ;
        exit( EXIT_FAILURE ) ;
    }
    printf("%X\n",miip.s_addr);
    printf("%X\n",miip.s_addr[c1]);
    printf("%X\n",miip.s_addr[2]);
    printf("%X\n",miip.s_addr[3]);*/



    const char *ip_text = "193.110.128.200";
    struct in_addr ip_addr;
    unsigned char *bytes;

    // Convertir la dirección IP de formato textual a binario
    if (inet_pton(AF_INET, ip_text, &ip_addr) != 1) {
        fprintf(stderr, "Error al convertir la IP.\n");
        return 1;
    }

    // Convertir la dirección IP en formato binario a una serie de bytes
    bytes = (unsigned char *)&ip_addr;

    // Imprimir los 4 bytes por separado
    printf("Dirección IP en formato binario:\n");
    printf("Byte 1: %u\n", bytes[0]);
    printf("Byte 2: %u\n", bytes[1]);
    printf("Byte 3: %u\n", bytes[2]);
    printf("Byte 4: %u\n", bytes[3]);
    return (EXIT_SUCCESS);
}