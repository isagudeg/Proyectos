#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vectordinamico.h"
#include "cambio.h"


int main(int argc, char** argv){
    vectorD monedas,solucion,stock;
    TELEMENTO valormoneda,cambio;
    unsigned long int tamarch=0,pos=0;
    int nostock,*nostockpunt = &nostock;
    char opcion,opcionilim,linea[1024],valor[25],nombremoneda[25],nombrestock[25];
    FILE *docu;

    /*if (argc<2){
       printf("Debe añadir un fichero externo con los valores de las monedas existentes\n");
       return 1;
    }
    docu = fopen(argv[1], "r");*/
    docu = fopen("euros.txt", "r");

    if(docu == NULL){
        printf("error");
        exit(1);
    }

    while (fgets(linea, sizeof(linea), docu) != NULL) {//cuenta cuantas lineas tiene el archivo
        tamarch++;
    }

    CreaVector(&monedas,tamarch-1);

    fseek(docu,0,SEEK_SET);
    fgets(nombremoneda, sizeof(nombremoneda), docu); //guarda el nombre de la moneda
    while (fgets(valor, sizeof(valor), docu) != NULL) { //guarda los datos del archivo en el vector de las monedas
        valormoneda=atoi(valor);
        AsignaVector(&monedas,pos,valormoneda);
        pos++;
    }

    fclose(docu);

    do{
        printf("\n-----------------\n");
        printf("\n1) Monedas ilimitadas\n");
        printf("\n2) Monedas limitadas \n");
        printf("\n3) Salir\n");
        printf("\n-----------------\n");
        printf("\nOpción: ");
        scanf(" %c", &opcion);
        switch (opcion) {
            case '1':
                do{
                    printf("\nEscriba la cantidad de cambio a devolver: ");
                    scanf(" %d", &cambio);
                    
                    if(cambio!=0){
                        CreaVector(&solucion,tamarch-1);
                        cambioilimi(cambio,monedas,&solucion);
                        devcambio(monedas,solucion,nombremoneda);
                        LiberaVector(&solucion);
                    }

                }while (cambio!=0);
                break;
            case '2':
                printf("\n-----------------\n");
                printf("\nElija una opción:\na) Devolver cambio,\nb) Aumentar el stock\n");
                printf("\n-----------------\n");
                printf("\nOpción: ");
                scanf(" %c", &opcionilim);

                CreaVector(&stock,tamarch-1);
                printf("\nEscriba el nombre del documento donde se almacena el stock: ");
                scanf(" %s", &nombrestock);
                docu = fopen(nombrestock, "r");

                if(docu == NULL){
                    printf("error");
                    exit(1);
                }
                pos=0;
                while (fgets(valor, sizeof(valor), docu) != NULL) {//guarda los datos de stock en el vector stock
                    valormoneda=atoi(valor);
                    AsignaVector(&stock,pos,valormoneda);
                    pos++;
                }
                fclose(docu);

                if(opcionilim=='a'){
                    do{
                        printf("\nEscriba la cantidad de cambio a devolver: ");
                        scanf(" %d", &cambio);
                        
                        if(cambio!=0){
                            CreaVector(&solucion,tamarch-1);
                            nostock=0;
                            cambiolimi(cambio,monedas,&solucion,&stock,nostockpunt);
                            // si nostock es 1 no hay stock
                            if(nostock!=1){
                                devcambio(monedas,solucion,nombremoneda);
                                printf("----------------------------------------\n");
                                devstock(monedas,stock,nombremoneda);
                                guardaStock(stock,tamarch-1,nombrestock);
                            }
                            LiberaVector(&solucion);
                        }
                    }while (cambio!=0);
                }
                else if (opcionilim=='b'){
                    for(int i=0;i<(tamarch-1);i++){
                        AsignaVector(&stock,i,Componentei(stock,i)+10);
                    }
                    guardaStock(stock,tamarch-1,nombrestock);
                    printf("Se han añadido 10 monedas de cada tipo");
                }
                else{
                    printf("La opción no es correcta.");
                }
                break;
            case '3':
                break;
            default:
                printf("La opción es incorrecta");
                break;
        }
    } while (opcion != '3');



    
    return(EXIT_SUCCESS);
}



