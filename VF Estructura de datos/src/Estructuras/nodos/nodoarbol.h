#ifndef NODO_ARBOL
#define NODO_ARBOL
#include <stdlib.h>

typedef struct nodo_arbol
{
	struct nodo_arbol *izq;
	struct nodo_arbol *dch;
	void *dato;
}NodoA;

NodoA* crearNodoA(void *dato);

#endif