#ifndef CAMBIO_H
#define CAMBIO_H
#include "vectordinamico.h"

typedef int TELEMENTO; /*Tipo de datos del vector*/
typedef void * vectorD; /*tipo opaco*/

int cambioilimi(int cambio, vectorD valor,vectorD *solucion);
int cambiolimi(int cambio, vectorD valor,vectorD *solucion, vectorD *stock, int *nostock);
void devcambio(vectorD valor,vectorD solucion, char nombremoneda[]);
void guardaStock(vectorD stock, int tamano);
void devstock(vectorD valor,vectorD stock, char nombremoneda[]);


#endif /*CAMBIO_H*/