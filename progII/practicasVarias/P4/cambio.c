
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "vectordinamico.h"

int cambioilimi(int cambio, vectorD valor,vectorD *solucion){
    int i,suma=0;

    for (i=0; i<tamano(valor); i++){
        AsignaVector(solucion,i,0);
    }
    i=0;
    while (suma<cambio && tamano(valor)){
        if (suma+Componentei(valor,i)<=cambio){
            AsignaVector(solucion,i,Componentei(*solucion,i)+1);
            suma=suma+Componentei(valor,i);
        }
        else
            i++;
    }
    if (suma==cambio){
        return 1;
    }
    else{
        for (i=0;i<cambio;i++){ 
            AsignaVector(solucion,i,0);
        }
        return 0;
    }
}


int cambiolimi(int cambio, vectorD valor,vectorD *solucion, vectorD *stock, int *nostock){
    int i,suma=0;
    vectorD copia;
    
    for (i=0; i<tamano(valor); i++){
        AsignaVector(solucion,i,0);
    }
    i=0;
    CreaVector(&copia,tamano(*stock)); //copiamos el vector stock antes de modificarlo
    copiaVector(&copia,*stock);
    while (suma<cambio && i<tamano(valor)){
        if (suma+Componentei(valor,i)<=cambio && Componentei(*stock,i)!=0){
            AsignaVector(solucion,i,Componentei(*solucion,i)+1);
            suma=suma+Componentei(valor,i);
            AsignaVector(stock,i,Componentei(*stock,i)-1);//modificamos el vector stock
        }
        else
            i++;
        
    }
    if (suma==cambio){
        return 1;
    }
    else{
        for (i=0;i<cambio;i++){ 
            AsignaVector(solucion,i,0);
        }
        printf("No hay stock suficiente o no se ha llegado a una solución.");
        *nostock=1;
        copiaVector(stock,copia);//restauramos el vector stock con la copia que realizamos antes de modificarlo
        return 0;
    }
}

//usa los valores de solucion para indicar cuantas monedas y de que valor hay que devolver
void devcambio(vectorD valor,vectorD solucion, char nombremoneda[]){
    unsigned long int tam;
    int componente;
    tam=tamano(solucion);
    printf("Dinero a devolver:\n");
    for(short i=0;i<tam;i++){
        componente=Componentei(solucion,i);
        if(Componentei(solucion,i)!=0){
            printf("%d moneda/as de %d céntimo/os de %s",componente,Componentei(valor,i),nombremoneda);
        }
    }
}

//reescribe el documento de stock
void guardaStock(vectorD stock, int tamano, char nombrestock[]){
    FILE *docu;

    docu = fopen(nombrestock, "w");
    if(docu == NULL){
        printf("error");
        exit(1);
    }
    for(unsigned long i=0;i<tamano;i++){
        fprintf(docu, "%d\n", Componentei(stock,i));
    }
    fclose(docu);
}

//usa los valores de stock para indicar cuantas monedas y de que valor quedan
void devstock(vectorD valor,vectorD stock, char nombremoneda[]){
    unsigned long int tam;
    int componente;
    tam=tamano(stock);
    printf("Monedas restantes:\n");
    for(short i=0;i<tam;i++){
        componente=Componentei(stock,i);
        if(Componentei(stock,i)!=0){
            printf("%d moneda/as de %d céntimo/os de %s",componente,Componentei(valor,i),nombremoneda);
        }
    }
}