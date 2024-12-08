
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef int TELEMENTO;

typedef struct {
    TELEMENTO *datos;
    unsigned long int tam;
} STVECTOR;

typedef STVECTOR *vectorD;

/*Función CreaVector: asigna memoria y devuelve la asignación al vector*/
void CreaVector(vectorD *v1, unsigned long int tam1) {
    *v1 = (vectorD) malloc(sizeof (STVECTOR));
    (*v1)->datos = (TELEMENTO*) malloc(tam1 * sizeof (TELEMENTO));
    (**v1).tam = tam1;
}

/*Función AsignaVector: Llena una posición del vector con un valor*/
void AsignaVector(vectorD *v1, unsigned long int posicion, TELEMENTO valor) {
    *( (*v1) ->datos + posicion) = valor;
}


bool EsNulo(vectorD v1) {
    if (v1 == 0)
        return true;
    return false;
}

void LiberaVector(vectorD *v1) {
    if (!EsNulo(*v1)) {
        /*Primero liberamos el bloque al que apunta datos*/
        free((*v1)->datos);
        /*Y después liberamos la estructura*/
        free(*v1);
        /*Volvemos a inicializar el puntero a 0*/
        *v1=0;
    }
}

TELEMENTO Componentei(vectorD v1,unsigned long int posicion){
    if (!EsNulo(v1))
        if (posicion < v1->tam)
            return *(v1->datos+posicion);
}

unsigned long int tamano(vectorD v1){
    return v1->tam;
}

void inicializaVectorRand(vectorD *v1){
    unsigned long int tam;
    unsigned long int i;
    TELEMENTO valor;

    srand(time(NULL));

    tam=tamano(*v1);

    for(i=0;i<tam;i++){
        AsignaVector(v1,i,rand());
    }
}

void swap (vectorD *v1, unsigned long int m, unsigned long int n){
    TELEMENTO elementoaux;

    elementoaux=Componentei(*v1,m);
    AsignaVector(v1,m,Componentei(*v1,n));
    AsignaVector(v1,n,elementoaux);

}