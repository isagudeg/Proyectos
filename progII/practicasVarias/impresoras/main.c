#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <math.h>
#include "lista.h"
#include "cola.h"
#include "operaciones.h"


int main(int argc, char** argv){
    TLISTA lista;
    TIPOELEMENTOLISTA e;
    TPOSICION pos;
    int longitud,i;
    char opcion;
    FILE *docu;

    if (argc==1){
       printf("Debe indicar el nombre del archivo\n");
       return 1;
    }

    docu = fopen(argv[1], "r");
    //docu = fopen("nombres_impresoras.txt", "r");
    if(docu == NULL){
        printf("error");
        exit(1);
    }

    crearLista(&lista);
    while (fscanf(docu,"%s %s %s %s",e.nombre,e.marca,e.modelo,e.ubicacion) != EOF){
        pos=finLista(lista);
        crearCola(&e.impresiones);
        insertarElementoLista(&lista,pos,e);
    }
    fclose(docu);
    imprimirLista(lista);


    do{
        printf("\n-----------------\n");
        printf("\na) Eliminar impresora\n");
        printf("\nb) Añadir impresora\n");
        printf("\nc) Enviar trabajo\n");
        printf("\nd) Trabajos pendientes\n");
        printf("\ne) Imprimir trabajo\n");
        printf("\nf) Impresoras con carga baja\n");
        printf("\ns) Salir\n");
        printf("\n-----------------\n");
        printf("\nOpcion: ");
        scanf(" %c", &opcion);
        switch (opcion) {
            case 'a':
                eliminarImpresora(&lista);
                imprimirLista(lista);
                break;
            case 'b':
                añadirImpresora(&lista);           
                imprimirLista(lista);
                break;
            case 'c':
                mandarTrabajo(&lista);
                break;
            case 'd':
                trabajosPendientes(lista);
                break;
            case 'e':
                imprimirTrabajo(&lista);
                break;
            case 'f':
                cargaBaja(lista);
                break;
            case 's':
                docu = fopen(argv[1], "w");
                //docu = fopen("nombres_impresoras.txt", "w");
                if(docu == NULL){
                    printf("error");
                    exit(1);
                }

                pos=primeroLista(lista);
                longitud=longitudLista(lista);
                for(i=1;i<=longitud;i++){
                    recuperarElementoLista(lista,pos,&e);
                    fprintf(docu, "%s %s %s %s\n", e.nombre, e.marca, e.modelo, e.ubicacion);
                    destruirCola(&e.impresiones);
                    pos=siguienteLista(lista,pos);
                }
                destruirLista(&lista);  
                fclose(docu);          
                break;
            default:
                printf("La opción es incorrecta");
                break;
        }
    } while (opcion != 's');

    
    return(EXIT_SUCCESS);
}