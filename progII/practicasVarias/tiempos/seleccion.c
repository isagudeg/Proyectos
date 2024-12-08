
#include <stdlib.h>
#include <stdbool.h>
#include "vectordinamico.h"


void selec(vectorD *v1, unsigned long int tam){
    unsigned long int e,i,PosMenor;
    TELEMENTO aux;
    for (e=0; e<(tam-1) ; e++){
        PosMenor=e;
        for (i=e+1;i<tam;i++){
            if (Componentei(*v1,i)<Componentei(*v1,PosMenor)){
                PosMenor=i;
            }
        }
        aux=Componentei(*v1,e);
        AsignaVector(v1,e,Componentei(*v1,PosMenor));
        AsignaVector(v1,PosMenor,aux);
    }
}