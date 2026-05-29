#include "arbol.h"

void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{

		if(raiz->izq)
			insertarArbolOrdenado(raiz->izq,dato,comparar);
		else
			raiz->izq = crearNodoA(dato);
	}
	else
	{
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}

void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}


void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)	
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}

int contarNodos(NodoA *nodo)
{
	if (!nodo)
		return 0;
	return 1 + contarNodos(nodo->izq) + contarNodos(nodo->dch);
}

int sonIguales(NodoA *a, NodoA *b)
{
	if (!a && !b)
		return 1;
	if (!a || !b)
		return 0;
	
	int *datoA = (int*)a->dato;
	int *datoB = (int*)b->dato;
	
	if (*datoA != *datoB)
		return 0;
	
	return sonIguales(a->izq, b->izq) && sonIguales(a->dch, b->dch);
}

void obtenerDatosEnOrden(NodoA *raiz, int *array, int *index)
{
	if (!raiz)
		return;
	obtenerDatosEnOrden(raiz->izq, array, index);
	int *dato = (int*)raiz->dato;
	array[(*index)++] = *dato;
	obtenerDatosEnOrden(raiz->dch, array, index);
}

int mismosDatos(NodoA *a, NodoA *b)
{
	int cantA = contarNodos(a);
	int cantB = contarNodos(b);
	
	if (cantA != cantB)
		return 0;
	
	if (cantA == 0)
		return 1;
	
	int *arrayA = (int*)calloc(cantA, sizeof(int));
	int *arrayB = (int*)calloc(cantB, sizeof(int));
	int indexA = 0, indexB = 0;
	
	obtenerDatosEnOrden(a, arrayA, &indexA);
	obtenerDatosEnOrden(b, arrayB, &indexB);
	
	int iguales = 1;
	for (int i = 0; i < cantA; i++)
	{
		if (arrayA[i] != arrayB[i])
		{
			iguales = 0;
			break;
		}
	}
	
	free(arrayA);
	free(arrayB);
	return iguales;
}


NodoA* buscarNodoConPadre(NodoA *raiz, int valor, NodoA **padre, int (*comparar)(void*,void*))
{
	if (!raiz)
		return NULL;
	
	int *dato = (int*)raiz->dato;
	if (*dato == valor)
		return raiz;
	
	*padre = raiz;
	int *valorPtr = &valor;
	if (comparar(valorPtr, raiz->dato) < 0)
		return buscarNodoConPadre(raiz->izq, valor, padre, comparar);
	else
		return buscarNodoConPadre(raiz->dch, valor, padre, comparar);
}


NodoA* encontrarMinimo(NodoA *nodo)
{
	while (nodo->izq)
		nodo = nodo->izq;
	return nodo;
}

int eliminarArbol(Arbol *arbol, int valor)
{
	if (!arbol->raiz)
		return 0;
	
	NodoA *padre = NULL;
	NodoA *nodo = buscarNodoConPadre(arbol->raiz, valor, &padre, arbol->comparar);
	
	if (!nodo)
		return 0;
	
	// Caso 1: Nodo hoja
	if (!nodo->izq && !nodo->dch)
	{
		if (!padre)
			arbol->raiz = NULL;
		else if (padre->izq == nodo)
			padre->izq = NULL;
		else
			padre->dch = NULL;
		
		arbol->liberar(nodo->dato);
		free(nodo);
	}
	// Caso 2: Nodo con un hijo
	else if (!nodo->izq || !nodo->dch)
	{
		NodoA *hijo = nodo->izq ? nodo->izq : nodo->dch;
		
		if (!padre)
			arbol->raiz = hijo;
		else if (padre->izq == nodo)
			padre->izq = hijo;
		else
			padre->dch = hijo;
		
		arbol->liberar(nodo->dato);
		free(nodo);
	}
	// Caso 3: Nodo con dos hijos
	else
	{
		NodoA *sucesor = encontrarMinimo(nodo->dch);
		int *valorSucesor = (int*)malloc(sizeof(int));
		*valorSucesor = *(int*)sucesor->dato;
		
		eliminarArbol(arbol, *valorSucesor);
		arbol->liberar(nodo->dato);
		nodo->dato = valorSucesor;
		arbol->cantidad++;
	}
	
	arbol->cantidad--;
	return 1;
}


int calcularAltura(NodoA *nodo)
{
	if (!nodo)
		return 0;
	
	int alturaIzq = calcularAltura(nodo->izq);
	int alturaDch = calcularAltura(nodo->dch);
	
	return 1 + (alturaIzq > alturaDch ? alturaIzq : alturaDch);
}


NodoA* construirBalanceado(int *array, int inicio, int fin)
{
	if (inicio > fin)
		return NULL;
	
	int medio = (inicio + fin) / 2;
	int *dato = (int*)malloc(sizeof(int));
	*dato = array[medio];
	
	NodoA *nodo = crearNodoA(dato);
	nodo->izq = construirBalanceado(array, inicio, medio - 1);
	nodo->dch = construirBalanceado(array, medio + 1, fin);
	
	return nodo;
}


void liberarArbolPostorden(NodoA *nodo, void (*liberar)(void*))
{
	if (!nodo)
		return;
	
	liberarArbolPostorden(nodo->izq, liberar);
	liberarArbolPostorden(nodo->dch, liberar);
	liberar(nodo->dato);
	free(nodo);
}


void equilibrarArbol(Arbol *arbol)
{
	if (!arbol->raiz)
		return;
	
	int cantidad = contarNodos(arbol->raiz);
	int *array = (int*)calloc(cantidad, sizeof(int));
	int index = 0;
	
	obtenerDatosEnOrden(arbol->raiz, array, &index);
	
	liberarArbolPostorden(arbol->raiz, arbol->liberar);
	
	arbol->raiz = construirBalanceado(array, 0, cantidad - 1);
	free(array);
}


void liberarArbol(Arbol *arbol)
{
	if (arbol->raiz)
	{
		liberarArbolPostorden(arbol->raiz, arbol->liberar);
		arbol->raiz = NULL;
		arbol->cantidad = 0;
	}
}