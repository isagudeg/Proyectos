#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "lista.h"
#include "cola.h"

//Necesita un parámetro l del tipo TLISTA e imprime los elementos de la lista.
void imprimirLista(TLISTA l);

//Necesita un parámetro *q del tipo TCOLA e imprime los elementos de la cola.
void imprimirCola(TCOLA *q);

//Necesita un parámetro *q del tipo TCOLA y devuelve la cantidad de elementos que contiene la cola.
int cantidadCola(TCOLA *q);

//Necesita un parámetro *l del tipo TLISTA, pide una impresora de la lista y si la encuentra la elimina.
void eliminarImpresora(TLISTA *l);

//Necesita un parámetro *l del tipo TLISTA, pide los datos de una nueva impresora y la añade a la lista.
void añadirImpresora(TLISTA *l);

//Necesita un parámetro *l del tipo TLISTA, pide el nombre de impresora y del trabajo nuevo y lo añade a la cola de impresiones.
void mandarTrabajo(TLISTA *l);

//Necesita un parámetro *l del tipo TLISTA, pide el nombre de impresora a consultar e imprime la lista de trabajos pendientes de impresión.
void trabajosPendientes(TLISTA l);

//Necesita un parámetro *l del tipo TLISTA, imprime las impresoras con menos carga de trabajo.
void cargaBaja(TLISTA l);

//Necesita un parámetro *l del tipo TLISTA, pide el nombre de la impresora en la que se encuentra el trabajo 
// que queremos imprimir y lo elimina de la cola de impresión y nos devuelve su identificador por pantalla.
void imprimirTrabajo(TLISTA *l);



#endif