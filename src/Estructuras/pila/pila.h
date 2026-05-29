#ifndef PILA_H
#define PILA_H

#include "../nodos/nodo.h"

typedef struct
{
    Nodo *cima;
    int capacidad;
    int cantidad;
    void (*imprimir)(void*);
    void (*liberar)(void*);
} Pila;

int llena(Pila pila);
void imprimir(void *dato);
int vacia(Pila pila);
void push(Pila *pila, void *dato);
void* pop(Pila *pila);
void push_nodo(Pila *pila, Nodo *nuevo);
Nodo* pop_nodo(Pila *pila);
void imprimirPila(Pila pila);
void imprimirPilaInvertida(Pila pila);
void eliminarPila(Pila *pila);
void inicializarPila(Pila *pila);
int palindromo(Pila *pila);
void parentesis(Pila *pila);

void* peek_nodo(Pila pila);
int prioridad(char op);

#endif