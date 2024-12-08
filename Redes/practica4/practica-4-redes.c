#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


/*
Martín González Dios
Isabel Gude Gómez
*/

/*Definimos una estructura para almacenar la información de la tabla de reenvío*/
typedef struct {
    struct in_addr ip;
    struct in_addr mascara;
    int sufijo;
    int interfaz;
} red;

int main(int argc, char **argv) {
    /*Comprobación del número de argumentos*/
    if(argc != 3) {
        perror("Error en el número de argumentos, el formato correcto es: ./practica4 <nombre_archivo> <dirección_IP_entrada>\n");
        exit(1);
    }

    /*Apertura del archivo*/
    FILE *archivo = fopen(argv[1], "r");
    if(archivo == NULL) {
        perror("Error al abrir el archivo\n");
        exit(1);
    }

    char linea[100];
    int tamTablaReenvio = 0;
    /*Contabilización del tamaño de la tabla de reenvío para almacenarla posteriormente*/
    while(fgets(linea, 100, archivo) != NULL) {
        tamTablaReenvio++;
    }

    /*Colocar el puntero del archivo al principio*/
    rewind(archivo);

    /*Declaración de la estructura con el tamaño adecuado*/
    red redStruct[tamTablaReenvio];

    /*Inicializar a 0 ip y máscara de la tabla de reenvío*/
    for(int i = 0; i < tamTablaReenvio; i++) {
        redStruct[i].ip.s_addr = 0;
        redStruct[i].mascara.s_addr = 0;
    }

    char ipStr[20]; //variable para guardar la ip en formato textual
    for(int i = 0; fgets(linea, 100, archivo) != NULL; i++) {
        /*Guardar la ip en formato textual y la interfaz en la estructura*/
        sscanf(linea, "%16[^,],%d", ipStr, &redStruct[i].interfaz);

        /*Convertir la ip a formato binario*/
        if((redStruct[i].sufijo = inet_net_pton(AF_INET, ipStr, (void *) &redStruct[i].ip.s_addr, sizeof(struct in_addr))) < 0) {
            perror("Error al convertir la dirección IP\n");
            exit(1);
        }

        /*Se obtiene la máscara de subred*/
        redStruct[i].mascara.s_addr = htonl(0xFFFFFFFF << (32 - redStruct[i].sufijo));
    }


    /*Impresión de la tabla de reenvío*/
    char ipImprimir[INET_ADDRSTRLEN];
    printf("Tabla de reenvío:\n");
    for(int i = 0; i < tamTablaReenvio; i++) {
        inet_ntop(AF_INET, &(redStruct[i].ip.s_addr), ipImprimir, INET_ADDRSTRLEN);
        printf("\t%s, %d\n", ipImprimir, redStruct[i].interfaz);
    } 
    printf("\n");

    /*Crear e inicializar estructura para la ip de entrada*/
    red ipEntrada;
    ipEntrada.sufijo = 0;
    ipEntrada.ip.s_addr = 0;

    /*Convertir a binario la ip de entrada*/
    if((ipEntrada.sufijo = inet_net_pton(AF_INET, argv[2], (void *) &ipEntrada.ip.s_addr, sizeof(struct in_addr))) < 0) {
        perror("Error al convertir la dirección IP de entrada\n");
        exit(1);
    }

    /*And logico (Máscara e ip de entrada)*/
    red resultado;
    resultado.ip.s_addr = 0;
    resultado.mascara.s_addr = 0;
    resultado.interfaz = 0;
    resultado.sufijo = 0;
    for(int i = 0; i < tamTablaReenvio; i++) {
        /*Operación AND entre la IP de entrada y la máscara de la red, y se compara con la red actual*/
        if((ipEntrada.ip.s_addr & redStruct[i].mascara.s_addr) == (redStruct[i].ip.s_addr & redStruct[i].mascara.s_addr)) {
            /*Nos quedamos con la red con menor sufijo*/
            if(resultado.sufijo < redStruct[i].sufijo) {
                resultado = redStruct[i];
            }
        }
    }
    
    /*Pasar a textual la ip resultado*/
    inet_ntop(AF_INET, &(resultado.ip.s_addr), ipImprimir, INET_ADDRSTRLEN);

    /*Impresión de la interfaz*/
    printf("Interfaz: %d\n", resultado.interfaz);
    printf("Número de bits del prefijo(sufijo): %d\n", resultado.sufijo);
    printf("IP de red: %s\n", ipImprimir);

    fclose(archivo);

    exit(0);

}