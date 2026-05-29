#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H
#include "nododoble.h"


typedef struct 
{
    NodoD *inicio;
    NodoD *fin;
    int cant;
    int (*comparar)(void *datoA, void *datoB);
    void (*imprimir)(void *datoA);
    void (*liberar)(void *datoA);
} ListaD;



ListaD inicializarListaD(void);

void mostrarListaD(ListaD lista);
void mostrarListaA(ListaD lista);

void insertarOrdenado(ListaD *lista, void *dato);

void reordenar(ListaD *lista, int (*comparar)(void*, void*));

void eliminarEnPosicion(ListaD *lista, int pos);

void* buscarDato(ListaD lista, void *dato);

void borrarDato(ListaD *lista, void *dato);

#endif