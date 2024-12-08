#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vectordinamico.h"
#include "quicksort.h"
#include "burbuja.h"
#include "seleccion.h"
#include <time.h>


int main(int argc, char** argv){
    vectorD vector;
    unsigned long int tam,tamanomax,paso;
    clock_t inicio=-1, fin=-1;
    char opcion;
    FILE *docu;

    if (argc<4){
       printf("Debe indicar los datos que faltan en el siguiente orden: los valores de tamaño inicial, tamaño final y paso necesarios para realizar la experimentación\n");
       return 1;
    }

    do{
        printf("\n-----------------\n");
        printf("\n1) Ordenación rápida (quicksort)\n");
        printf("\n2) Método de la burbuja \n");
        printf("\n3) Método de selección\n");
        printf("\n4) Salir\n");
        printf("\n-----------------\n");
        printf("\nOpción: ");
        scanf(" %c", &opcion);
        switch (opcion) {
            case '1':
                docu = fopen("tiempos_quicksort.txt", "w");
                if(docu == NULL){
                    printf("error");
                    exit(1);
                }
                tam=(unsigned long int)atoi(argv[1]);
                tamanomax=(unsigned long int)atoi(argv[2]);
                paso=(unsigned long int)atoi(argv[3]);
                for(tam;tam<=tamanomax;tam=tam+paso){
                    CreaVector(&vector,tam);
                    inicializaVectorRand(&vector);
                    inicio=clock();
                    quicksort(&vector,0,tam);
                    fin=clock();
                    LiberaVector(&vector);
                    printf("%u\t%lf\n",tam,(fin-inicio)/(double)CLOCKS_PER_SEC);
                    fprintf(docu, "%u\t%.6lf\n", tam, (fin-inicio)/(double)CLOCKS_PER_SEC);
                }
                printf("\n");
                fclose(docu);
                break;
            case '2':
                docu = fopen("tiempos_burbuja.txt", "w");
                if(docu == NULL){
                    printf("error");
                    exit(1);
                }
                tam=(unsigned long int)atoi(argv[1]);
                tamanomax=(unsigned long int)atoi(argv[2]);
                paso=(unsigned long int)atoi(argv[3]);
                for(tam;tam<=tamanomax;tam=tam+paso){
                    CreaVector(&vector,tam);
                    inicializaVectorRand(&vector);
                    inicio=clock();
                    burbuja(&vector,tam);
                    fin=clock();
                    LiberaVector(&vector);
                    printf("%u\t%lf\n",tam,(fin-inicio)/(double)CLOCKS_PER_SEC);
                    fprintf(docu, "%u\t%.6lf\n", tam, (fin-inicio)/(double)CLOCKS_PER_SEC);
                }
                printf("\n");
                fclose(docu);
                break;
            case '3':
                docu = fopen("tiempos_seleccion.txt", "w");
                if(docu == NULL){
                    printf("error");
                    exit(1);
                }
                tam=(unsigned long int)atoi(argv[1]);
                tamanomax=(unsigned long int)atoi(argv[2]);
                paso=(unsigned long int)atoi(argv[3]);
                for(tam;tam<=tamanomax;tam=tam+paso){
                    CreaVector(&vector,tam);
                    inicializaVectorRand(&vector);
                    inicio=clock();
                    selec(&vector,tam);
                    fin=clock();
                    LiberaVector(&vector);
                    printf("%u\t%lf\n",tam,(fin-inicio)/(double)CLOCKS_PER_SEC);
                    fprintf(docu, "%u\t%.6lf\n", tam, (fin-inicio)/(double)CLOCKS_PER_SEC);
                }
                fclose(docu);
                break;
            case '4':          
                break;
            default:
                printf("La opción es incorrecta");
                break;
        }
    } while (opcion != '4');

    
    return(EXIT_SUCCESS);
}



