#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "vectordinamico.h"


void imprimir(vectorD vector){
    short tam;
    float valor;
    printf("Los elementos del vector son: [ ");
    tam=tamano(vector);
    for(short i=0;i<tam;i++){
        valor=Componentei(vector,i);
        printf(" %f",valor);
    }
    printf("]");
}


float mediaGeometrica(vectorD vector){
    int tam;
    float mult=1;
    float mediaGeo,exponente;

    tam=tamano(vector);
    for(short i=0;i<tam;i++){
        mult=mult*Componentei(vector,i);
    }
    exponente=(float)(1.0/tam);
    mediaGeo=pow(mult,exponente);
    return(mediaGeo);
}

float media(vectorD vector){
    int tam;
    float sum=0;
    float media;

    tam=tamano(vector);
    for(short i=0;i<tam;i++){
        sum+=Componentei(vector,i);
    }
    media=sum/tam;
    return(media);
}


int main(int argc, char** argv){
    vectorD vector;
    short longitud, i, cantvector=0;
    TELEMENTO valor;
    char opcion;
    float mediaGeo,mediav;

    if (argc>=2){
        CreaVector(&vector, (argc-1));
        for (i = 1; i<argc; i++){
            valor=atof(argv[i]);
            AsignaVector(&vector, (i-1), valor);
        }
        cantvector=1;
    }

    do{
        printf("\n-----------------\n");
        printf("\na) Crear vector\n");
        printf("\nb) Liberar vector\n");
        printf("\nc) Imprimir vector\n");
        printf("\nd) Media Geométrica\n");
        printf("\ne) Media\n");
        printf("\ns) Salir\n");
        printf("\n-----------------\n");
        printf("\nOpcion: ");
        scanf(" %c", &opcion); //cuidado con el espacio
        switch (opcion) {
            case 'a': 
                if (cantvector!=0) {
                    LiberaVector(&vector);
                }
                printf("Cual es la longitud del vector?");
                scanf(" %hd", &longitud);
                CreaVector(&vector, longitud);
                cantvector=1;
                
                for (i = 0; i<longitud; i++){
                    printf("vector (%hd)", i);
                    scanf(" %f", &valor);
                    AsignaVector(&vector, i, valor);
                }
                break;
            case 'b':
                if(cantvector!=0){
                    LiberaVector(&vector);
                    printf("Vector liberado");
                }
                else{
                    printf("No hay ningún vector creado");
                }
                cantvector=0;
                break;
            case 'c':
                if (cantvector==0) {
                    printf("Error en imprimir: el vector no existe");
                    break;
                }
                imprimir(vector);
                break;
            case 'd':
                if (cantvector==0) {
                    printf("Error en Media Geométrica: el vector no existe");
                    break;
                }
                mediaGeo=mediaGeometrica(vector);
                printf("La media geométrica del vector es: %f",mediaGeo);
                break;
            case 'e':
                if (cantvector==0) {
                    printf("Error en Media: el vector no existe");
                    break;
                }
                mediav=media(vector);
                printf("La media del vector es: %f",mediav);
                break;
            case 's':
                if(cantvector!=0){
                    LiberaVector(&vector);
                }
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("La opción es incorrecta");
                break;
        }
    } while (opcion != 's');
    return(EXIT_SUCCESS);
}




