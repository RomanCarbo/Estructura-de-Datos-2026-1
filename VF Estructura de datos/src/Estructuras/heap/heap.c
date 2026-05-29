#include "heap.h"


Heap inicializarHeap(void (*imprimir)(void*),int (*comparar)(void*,void*), void (*liberar)(void*) )
{
	Arbol arbol = (Arbol){NULL,0,imprimir,NULL,liberar};
	return (Heap){NULL,0,arbol,imprimir,comparar,MIN};
}

void insertarHeap(Heap *heap, void *dato)
{
	NodoA **aux;
	heap->cantidad++;
	aux = NULL;
	while(!aux)
		aux = realloc(heap->arr,sizeof(NodoA*)*heap->cantidad);
	heap->arr = aux;
	heap->arr[heap->cantidad-1] = crearNodoA(dato);
	heapify(heap);
}

void* quitarHeap(Heap *heap)
{
	if(heap->cantidad == 0)
		return NULL;
	heap->cantidad--;
	void *dato = heap->arr[0]->dato;
	free(heap->arr[0]);
	heap->arr[0] = heap->arr[heap->cantidad];
	//DECREMENTAR MEMORIA	
	heap->arr = realloc(heap->arr,sizeof(NodoA*)*heap->cantidad);
	heapify(heap);	
	return dato;
}

/*
void heapMin(Heap *heap,int p)
{
	if( p < 0)
		return;
	int minimo = p;
	int hi = HIJO_IZQUIERDO(p);
	int hd = HIJO_DERECHO(p);
	if( (hi<heap->cantidad) && heap->comparar(heap->arr[hi]->dato,heap->arr[minimo]->dato)<0)
		minimo = hi;
	if( (hd<heap->cantidad) && heap->comparar(heap->arr[hd]->dato,heap->arr[minimo]->dato)<0)
		minimo = hd;
	if( minimo!= p)
	{
		NodoA *aux = heap->arr[p];
		heap->arr[p] = heap->arr[minimo];
		heap->arr[minimo] = aux;
		heapMin(heap,minimo);
	}
	else
		heapMin(heap,p-1);	
}
void heapMax(Heap *heap,int p)
{
	if( p < 0)
		return;
	int maximo = p;
	int hi = HIJO_IZQUIERDO(p);
	int hd = HIJO_DERECHO(p);
	if( (hi<heap->cantidad) && heap->comparar(heap->arr[hi]->dato,heap->arr[maximo]->dato)>0)
		maximo = hi;
	if( (hd<heap->cantidad) && heap->comparar(heap->arr[hd]->dato,heap->arr[maximo]->dato)>0)
		maximo = hd;
	if( maximo!= p)
	{
		NodoA *aux = heap->arr[p];
		heap->arr[p] = heap->arr[maximo];
		heap->arr[maximo] = aux;
		heapMax(heap,maximo);
	}
	else
		heapMax(heap,p-1);	
	
}
void heapify(Heap *heap)
{
	int p = heap->cantidad/2-1;
	switch(heap->tipo)
	{
		case MIN:
			heapMin(heap,p);
			break;
		case MAX:
			heapMax(heap,p);
			break;
	}
}
*/

void actualizarArbol(Heap *heap)
{
	int i,hi,hd;;
	
	if (heap->cantidad == 0) {
		heap->arbol.raiz = NULL;
		heap->arbol.cantidad = 0;
		return;
	}
	
	for( i = 0 ; i < heap->cantidad ; i++)
	{		
		hi = HIJO_IZQUIERDO(i);
		hd = HIJO_DERECHO(i);
		heap->arr[i]->izq = (hi<heap->cantidad) ? heap->arr[hi]:NULL;
		heap->arr[i]->dch = (hd<heap->cantidad) ? heap->arr[hd]:NULL;
	}
	if(heap->arr)
	{
		heap->arbol.raiz = heap->arr[0];
		heap->arbol.cantidad = heap->cantidad;
	}
	else 
	{
		heap->arbol.raiz = NULL;
		heap->arbol.cantidad = 0;
	}
}

int siCambiar(Heap *heap,int indice,int hijo)
{
	switch(heap->tipo)
	{
		case MAX:		
			if(heap->comparar(heap->arr[hijo]->dato,heap->arr[indice]->dato)>0)
				return 1;
			break;
		case MIN:		
			if(heap->comparar(heap->arr[hijo]->dato,heap->arr[indice]->dato)<0)
				return 1;
			break;
	}
	return 0;
}	
void heapTipo(Heap *heap,int p)
{
	if( p < 0)
		return;
	int indice = p;
	int hi = HIJO_IZQUIERDO(p);
	int hd = HIJO_DERECHO(p);
	if( (hi<heap->cantidad) && siCambiar(heap,indice,hi))
		indice = hi;
	if( (hd<heap->cantidad) && siCambiar(heap,indice,hd))
		indice = hd;
	if( indice!= p)
	{
		NodoA *aux = heap->arr[p];
		heap->arr[p] = heap->arr[indice];
		heap->arr[indice] = aux;
		heapTipo(heap,indice);
	}
	else
		heapTipo(heap,p-1);	
}
void heapify(Heap *heap)
{
	int p = heap->cantidad/2-1;
	heapTipo(heap,p);
	actualizarArbol(heap);
}


void imprimirHeap(Heap heap)
{
	int i;
	for( i = 0; i< heap.cantidad ; i++)
	{
		heap.imprimir( heap.arr[i]->dato);
	}	
}


void* eliminarElementoHeap(Heap *heap, int index)
{
	if (index < 0 || index >= heap->cantidad) {
		return NULL;
	}

	void *dato = heap->arr[index]->dato;
	free(heap->arr[index]);

	heap->cantidad--;

	if (heap->cantidad == 0) {
		free(heap->arr);
		heap->arr = NULL;
	} else if (index != heap->cantidad) {
		heap->arr[index] = heap->arr[heap->cantidad];
		
		NodoA **aux = NULL;
		aux = realloc(heap->arr, sizeof(NodoA*) * heap->cantidad);
		while(aux == NULL && heap->cantidad > 0) {
				aux = realloc(heap->arr, sizeof(NodoA*) * heap->cantidad);
		}
		heap->arr = aux;
	}

	heapify(heap);
	
	return dato;
}

void vaciarHeap(Heap *heap, void (*liberarDato)(void*))
{
	if (liberarDato) {
		for (int i = 0; i < heap->cantidad; i++) {
			liberarDato(heap->arr[i]->dato);
			free(heap->arr[i]);
		}
	} else {
		for (int i = 0; i < heap->cantidad; i++) {
			free(heap->arr[i]);
		}
	}
	
	free(heap->arr);
	heap->arr = NULL;
	heap->cantidad = 0;
	actualizarArbol(heap);
}