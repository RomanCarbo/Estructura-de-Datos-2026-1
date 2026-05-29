#ifndef ARBOL_H
#define ARBOL_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>

#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4
typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}Arbol;


void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol,int opcion);

int contarNodos(NodoA *nodo);
int sonIguales(NodoA *a, NodoA *b);
int mismosDatos(NodoA *a, NodoA *b);
int eliminarArbol(Arbol *arbol, int valor);
int calcularAltura(NodoA *nodo);
void equilibrarArbol(Arbol *arbol);
void liberarArbol(Arbol *arbol);

#endif