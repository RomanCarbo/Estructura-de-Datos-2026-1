#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include "../Estructuras/nodos/nodo.h"

typedef struct {
    Nodo *inicio;
    int (*comparar)(void*, void*);
    void (*imprimir)(void*);
    int cant;
} Lista;

void mostrarLista(Lista lista);
void insertarFinal(Lista *lista, void* dato);
void borrarLista(Lista *lista);
void borrarDato(Lista *lista, void* dato);
void* buscarDato(Lista lista, void* dato);
void insertarOrdenado(Nodo **lista, void* dato, int (*cmp)(void*, void*));
void insertarInicio(Lista *lista, void* dato);
void insertarEnPosicion(Lista *lista, void* dato, int pos);
void eliminarEnPosicion(Lista *lista, int pos);

#endif
