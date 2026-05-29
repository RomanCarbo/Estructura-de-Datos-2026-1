#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

int* crearEntero(int dato);
int compararEntero(void *a, void *b);
void imprimirEntero(void *a);

void invertirArbol(NodoA *raiz);
void* buscarEnArbolIterativo(NodoA *raiz, void *objetivo, int (*comparar)(void*, void*));


int main(void)
{
    Arbol arbol;
    arbol.raiz = NULL;
    arbol.cantidad = 0;
    arbol.imprimir = &imprimirEntero;
    arbol.comparar = &compararEntero;
    arbol.liberar = &free;
    
    insertarArbol(&arbol, crearEntero(7));
    insertarArbol(&arbol, crearEntero(4));
    insertarArbol(&arbol, crearEntero(2));
    insertarArbol(&arbol, crearEntero(8));
    insertarArbol(&arbol, crearEntero(9));
    insertarArbol(&arbol, crearEntero(6));
    insertarArbol(&arbol, crearEntero(1));
    insertarArbol(&arbol, crearEntero(5));
    
    printf("--- Arbol ---\n");
    imprimirArbol(arbol);
    printf("\n");

    printf("\n--- Recorrido en orden ---\n");

    imprimirOrden(arbol, 2);
    printf("\n\n");

    printf("--- Busqueda ---\n");
    
    int valorBuscar1 = 6;
    int valorBuscar2 = 15;

    void *resultado1 = buscarEnArbolIterativo(arbol.raiz, &valorBuscar1, arbol.comparar);
    if(resultado1) {
        printf("Buscado %d: Encontrado: ", valorBuscar1);
        imprimirEntero(resultado1);
        printf("\n");
    } else {
        printf("Buscado %d: No encontrado (NULL)\n", valorBuscar1);
    }

    void *resultado2 = buscarEnArbolIterativo(arbol.raiz, &valorBuscar2, arbol.comparar);
    if(resultado2) {
        printf("Buscado %d: Encontrado\n", valorBuscar2);
    } else {
        printf("Buscado %d: No encontrado (NULL)\n", valorBuscar2);
    }
    printf("\n");

    invertirArbol(arbol.raiz);
    
    printf("\n--- Arbol invertido ---\n");
    imprimirArbol(arbol);
    printf("\n");
    
    printf("\n--- Recorrido invertido en orden ---\n");

    imprimirOrden(arbol, 2); 
    printf("\n\n");

    liberarArbol(&arbol); 
    printf("Fin del programa\n");
    
    return 0;
}

void invertirArbol(NodoA *raiz) {
    if (raiz == NULL) {
        return;
    }

    NodoA *temp = raiz->izq;
    raiz->izq = raiz->dch;
    raiz->dch = temp;

    invertirArbol(raiz->izq);
    invertirArbol(raiz->dch);
}

void* buscarEnArbolIterativo(NodoA *raiz, void *objetivo, int (*comparar)(void*, void*)) {
    NodoA *actual = raiz;

    while (actual != NULL) {
        int resultado = comparar(objetivo, actual->dato);

        if (resultado == 0) {
            return actual->dato; 
        } else if (resultado < 0) {
            actual = actual->izq; 
        } else {
            actual = actual->dch; 
        }
    }
    return NULL; 
}

int* crearEntero(int dato) {
    int *nuevo = malloc(sizeof(int));
    if (nuevo) {
        *nuevo = dato;
    }
    return nuevo;
}

int compararEntero(void *a, void *b) {
    int *aa = (int*)a;
    int *bb = (int*)b;
    if(*aa == *bb) return 0;
    else if(*aa < *bb) return -1;
    else return 1;
}

void imprimirEntero(void *a) {
    int *aa = (int*)a;
    printf("%d", *aa);
}