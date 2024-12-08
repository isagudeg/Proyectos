


#include <stdlib.h>
#include <stdbool.h>

typedef float TELEMENTO;

typedef struct {
    TELEMENTO *datos;
    short tam;
} STVECTOR;

typedef STVECTOR *vectorD;

/*Función CreaVector: asigna memoria y devuelve la asignación al vector*/
void CreaVector(vectorD *v1, int tam1) {
    *v1 = (vectorD) malloc(sizeof (STVECTOR));
    (*v1)->datos = (TELEMENTO*) malloc(tam1 * sizeof (TELEMENTO));
    (**v1).tam = tam1;
}

/*Función AsignaVector: Llena una posición del vector con un valor*/
void AsignaVector(vectorD *v1, short posicion, TELEMENTO valor) {
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

TELEMENTO Componentei(vectorD v1,short posicion){
    if (!EsNulo(v1))
        if (posicion < v1->tam)
            return *(v1->datos+posicion);
}

short tamano(vectorD v1){
    return v1->tam;
}
