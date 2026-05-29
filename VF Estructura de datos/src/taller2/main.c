#include <stdio.h>
#include <stdlib.h>
#include "../Estructuras/pila/pila.h"

void ordenarPila(Pila *pila, int (*comparar)(void*, void*));
void imprimirEntero(void *dato);
int compararEnteros(void* a, void* b);

int main() {
    Pila pila;
    inicializarPila(&pila);
    
    pila.imprimir = imprimirEntero;
    
    int valores[] = {8, 5, 6, 10, 2, 3, 9};
    int cantidad = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < cantidad; i++) {
        push(&pila, &valores[i]);
    }
    
    printf("\nPila original:");
    imprimirPila(pila); 
    
    ordenarPila(&pila, compararEnteros);
    
    printf("\n\nPila ordenada:");
    imprimirPila(pila);
    
    return 0;
}
int compararEnteros(void* a, void* b) {
    int entA = *(int*)a;
    int entB = *(int*)b;
    return entA - entB;
}

void imprimirEntero(void *dato) {
    printf("%d", *(int*)dato);
}

void ordenarPila(Pila *pila, int (*comparar)(void*, void*)) {
    Pila pilaTemp;
    inicializarPila(&pilaTemp);
    
    while (!vacia(*pila)) {
        void *temp = pop(pila);

        while (!vacia(pilaTemp) && comparar(peek_nodo(pilaTemp), temp) < 0) {
            push(pila, pop(&pilaTemp));
        }
        push(&pilaTemp, temp);
    }  
    while (!vacia(pilaTemp)) {
        push(pila, pop(&pilaTemp));
    }
}