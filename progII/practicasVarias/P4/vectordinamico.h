#ifndef VECTORDINAMICO_H
#define VECTORDINAMICO_H

typedef int TELEMENTO; /*Tipo de datos del vector*/
typedef void * vectorD; /*tipo opaco*/

/*Funciones exportadas*/
/*Función CreaVector: asigna memoria y devuelve la asignación al vector*/
void CreaVector(vectorD *v1,unsigned long int tam1);
/*Función AsignaVector: Llena una posición del vector con un valor*/
void AsignaVector(vectorD *v1,unsigned long int posicion,TELEMENTO valor);


#endif /*VECTORDINAMICO_H*/




TELEMENTO Componentei(vectorD v1,unsigned long int posicion);
int EsNulo(vectorD v1);
void LiberaVector(vectorD *v1);
unsigned long int tamano(vectorD v1);


void inicializaVectorRand(vectorD *v1);
void swap (vectorD *v1, unsigned long int m, unsigned long int n);
void imprimir(vectorD vector);
void copiaVector(vectorD *copia,vectorD vector);