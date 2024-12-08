
#include <stdlib.h>
#include <stdbool.h>
#include "vectordinamico.h"


void burbuja(vectorD *v1, unsigned long int tam){
    unsigned long int e,i;
    TELEMENTO aux;

    for (e=0;e<(tam-1);e++){
        for (i=0;i<(tam-e-1);i++){
            if (Componentei(*v1,i)>Componentei(*v1,i+1)){
                aux=Componentei(*v1,i);
                AsignaVector(v1,i,Componentei(*v1,i+1));
                AsignaVector(v1,i+1,aux);
            }
        }
    }
}
