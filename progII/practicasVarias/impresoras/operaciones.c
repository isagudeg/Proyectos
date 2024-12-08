#include <stdlib.h>
#include <stdio.h>


#include <string.h>
#include "lista.h"
#include "cola.h"

/**
 * Imprime el nombre de las impresoras que hay en una lista del tipo TLISTA.
 *
 * @param l lista a imprimir.
 */
void imprimirLista(TLISTA l){ 
    TIPOELEMENTOLISTA e;
    TPOSICION pos;
    int longitud,i;

    pos=primeroLista(l);
    longitud=longitudLista(l);
    printf("\nImpresoras disponibles:\n");
    for(i=1;i<=longitud;i++){
        recuperarElementoLista(l,pos,&e);
        printf(" %s\n",e.nombre);
        pos=siguienteLista(l,pos);
    }
}


/**
 * Imprime el identificador numérico de las impresiones pendientes que hay en una cola del tipo TCOLA.
 *
 * @param q cola a imprimir.
 */
void imprimirCola(TCOLA *q){
    TIPOELEMENTOCOLA impresion, elemento1;
    if(esColaVacia(*q)==0){
        printf("Trabajos pendientes de impresión: \n");
        consultarPrimerElementoCola(*q,&elemento1);
        while (impresion!=elemento1){
            consultarPrimerElementoCola(*q,&impresion);
            printf("%d \n",impresion);
            anadirElementoCola(q,impresion);
            suprimirElementoCola(q);
            consultarPrimerElementoCola(*q,&impresion);
        }
    }
    else{
        printf("No hay trabajos pendientes de impresión. \n");
    }
}


/**
 * Devuelve el número de impresiones pendientes que hay en una cola del tipo TCOLA.
 *
 * @param q puntero a la cola a contar.
 */
int cantidadCola(TCOLA *q){
    TIPOELEMENTOCOLA impresion, elemento1;
    int cant=0;
    if(esColaVacia(*q)==1){
        cant=0;
    }
    else{
        consultarPrimerElementoCola(*q,&elemento1);
        while (impresion!=elemento1){
            consultarPrimerElementoCola(*q,&impresion);
            cant++;
            anadirElementoCola(q,impresion);
            suprimirElementoCola(q);
            consultarPrimerElementoCola(*q,&impresion);
        }
    }
    return cant;
}


/**
 * Elimina una impresora existente en una lista del tipo TLISTA.
 *
 * @param l puntero a la lista a modificar.
 */
void eliminarImpresora(TLISTA *l){
    TIPOELEMENTOLISTA e;
    TPOSICION pos;
    int longitud,i,igualdad;
    char nombreimp[25];

    printf("Escriba el nombre de la impresora que desea eliminar: ");
    scanf(" %s", nombreimp);
    pos=primeroLista(*l);
    longitud=longitudLista(*l);
    for(i=1;i<=longitud;i++){
        recuperarElementoLista(*l,pos,&e);
        igualdad = strncmp(e.nombre, nombreimp, strlen(nombreimp));
        if(igualdad==0){
            destruirCola(&e.impresiones);
            suprimirElementoLista(l,pos);
            i=longitud;
        }
        else{
            pos=siguienteLista(*l,pos);
        }
    }
    if(longitud==longitudLista(*l)){
        printf("La impresora %s no existe.\n",nombreimp);
    }
}


/**
 * Añade una impresora nueva a una lista del tipo TLISTA.
 *
 * @param l puntero a la lista a modificar.
 */
void añadirImpresora(TLISTA *l){
    TIPOELEMENTOLISTA e;
    TPOSICION pos;
    int longitud,i,igualdad;
    char nombreimp[25];

    printf("A contunuación añada los datos de la nueva impresora \nNombre: ");
    scanf(" %s", nombreimp);
    pos=primeroLista(*l);
    longitud=longitudLista(*l);
    for(i=1;i<=longitud;i++){
        recuperarElementoLista(*l,pos,&e);
        igualdad = strncmp(e.nombre, nombreimp, strlen(nombreimp));
        if(igualdad==0){
            printf("La impresora %s ya existe.\n",nombreimp);
            i=longitud;
        }
        else{
            pos=siguienteLista(*l,pos);
        }
    }
    if(igualdad!=0){               
    strcpy(e.nombre,nombreimp);
        printf("Marca: ");
        scanf(" %s", e.marca);
        printf("Modelo: ");
        scanf(" %s", e.modelo);
        printf("Ubicación: ");
        scanf(" %s", e.ubicacion);
        pos=finLista(*l);
        crearCola(&e.impresiones);
        insertarElementoLista(l,pos,e);
    }
}


/**
 * Añade un trabajo a la cola de impresiones de una impresora de una lista del tipo TLISTA.
 *
 * @param l puntero a la lista a modificar.
 */
void mandarTrabajo(TLISTA *l){
    TIPOELEMENTOLISTA e;
    TPOSICION pos;
    int longitud,i,igualdad;
    char nombreimp[25];
    TIPOELEMENTOCOLA impresion;

    printf("Introduzca el nombre de la impresora a la que desea mandar el trabajo: ");
    scanf(" %s", nombreimp);
    pos=primeroLista(*l);
    longitud=longitudLista(*l);
    for(i=1;i<=longitud;i++){
        recuperarElementoLista(*l,pos,&e);
        igualdad = strncmp(e.nombre, nombreimp, strlen(nombreimp));
        if(igualdad==0){
            printf("Introduzca el identificador numerico del trabajo que desea imprimir: ");
            scanf(" %d", &impresion);
            anadirElementoCola(&e.impresiones,impresion);
            i=longitud;
        }
        else{
            pos=siguienteLista(*l,pos);
        }
    }
    if(igualdad!=0){               
        printf("La impresora %s no existe.\n",nombreimp);
    }
}


/**
 * Imprime la cola de trabajos pendientes de una impresora de una lista del tipo TLISTA.
 *
 * @param l lista a consultar.
 */
void trabajosPendientes(TLISTA l){
    TIPOELEMENTOLISTA e;
    TPOSICION pos;
    int longitud,i,igualdad;
    char nombreimp[25];

    printf("Introduzca el nombre de la impresora que desea consultar: ");
    scanf(" %s", nombreimp);
    pos=primeroLista(l);
    longitud=longitudLista(l);
    for(i=1;i<=longitud;i++){
        recuperarElementoLista(l,pos,&e);
        igualdad = strncmp(e.nombre, nombreimp, strlen(nombreimp));
        if(igualdad==0){
            imprimirCola(&e.impresiones);
            i=longitud;
        }
        else{
            pos=siguienteLista(l,pos);
        }
    }
    if(igualdad!=0){               
        printf("La impresora %s no existe.\n",nombreimp);
    }
}


/**
 * Imprime las impresoras con menos impresiones pendientes de una lista del tipo TLISTA.
 *
 * @param l lista a consultar.
 */
void cargaBaja(TLISTA l){
    TIPOELEMENTOLISTA e;
    TPOSICION pos;
    int longitud,i;
    int cant;

    printf("Impresoras con menos carga de trabajo: \n");
    pos=primeroLista(l);
    longitud=longitudLista(l);
    cant=-1;
    for(i=1;i<=longitud;i++){
        recuperarElementoLista(l,pos,&e);
        if(cant==-1){
            cant=cantidadCola(&e.impresiones);
        }
        else{
            if(cant>cantidadCola(&e.impresiones)){
                cant=cantidadCola(&e.impresiones);
            }
        }
        pos=siguienteLista(l,pos);
        
    }
    pos=primeroLista(l);
    for(i=1;i<=longitud;i++){
        recuperarElementoLista(l,pos,&e);
        if(cant==cantidadCola(&e.impresiones)){
            printf(" %s \n",e.nombre);
        }
        pos=siguienteLista(l,pos);
    }
}


/**
 * Imprime el primer trabajo pendiente (lo elimina de la cola) de una impresora de una lista del tipo TLISTA.
 *
 * @param l puntero de la lista a modificar.
 */
void imprimirTrabajo(TLISTA *l){
    TIPOELEMENTOLISTA e;
    TIPOELEMENTOCOLA impresion;
    TPOSICION pos;
    int longitud,i,igualdad;
    char nombreimp[25];

    printf("Introduzca el nombre de la impresora en la que se encuentra el trabajo a imprimir: ");
    scanf(" %s", nombreimp);
    pos=primeroLista(*l);
    longitud=longitudLista(*l);
    for(i=1;i<=longitud;i++){
        recuperarElementoLista(*l,pos,&e);
        igualdad = strncmp(e.nombre, nombreimp, strlen(nombreimp));
        if(igualdad==0){
            if(esColaVacia(e.impresiones)==1){
                printf("No hay trabajos pendientes de impresión. \n");
            }
            else{
                consultarPrimerElementoCola(e.impresiones,&impresion);
                suprimirElementoCola(&e.impresiones);
                printf("El trabajo %d acaba de ser impreso.\n",impresion);
            }
            i=longitud;
        }
        else{
            pos=siguienteLista(*l,pos);
        }
    }
    if(igualdad!=0){               
        printf("La impresora %s no existe.\n",nombreimp);
    }
}