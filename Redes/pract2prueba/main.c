#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ether.h>


struct in_addr miip ;
int main(int argc, char** argv) {
    uint16_t puerto = 5000;
    uint16_t puertoh = ntohs(puerto);
    uint16_t puerton= htons(puerto);

    printf("\nValores iniciales en hexadecimal: %x",puerto);
    printf("\nValores convertido en hexadecimal: %x",puertoh);
    printf("\nValores convertido inverso en hexadecimal: %x",puerton);

    const char *ip_text = "193.110.128.200";
    struct in_addr ip_addr;
    unsigned char *bytes;

    if (inet_pton(AF_INET, ip_text, &ip_addr) != 1) {
        fprintf(stderr, "Error al convertir la IP.\n");
        return 1;
    }

    printf("\nValores iniciales: %c",*ip_text);
    printf("\nValores iniciales en hexadecimal: %x",*ip_text);
    printf("\nValores convertido en hexadecimal: %x",inet_pton(AF_INET, ip_text, &ip_addr));
    

    printf("\nip4 de youtube: %s","142.250.184.14");
    printf("\nip6 de youtube: %s","2a00:1450:4003:807::200e");




    return (EXIT_SUCCESS);
}