#include "pila.h"
#include "../nodos/nodo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../captura/captura.h"

int llena(Pila pila)
{
    return 0; //Se cambia a 0 para que la pila dinamica nunca se considere "llena"
}
int vacia(Pila pila)
{
    return pila.cantidad == 0 && pila.cima==NULL ;
}

void push(Pila *pila,void *dato)
{
    if(llena(*pila))
    {
        printf("\n Overflow");
    }
    else
    {
        Nodo *nuevo = crearNodo(dato);
        nuevo->sig = pila->cima;
        pila->cima = nuevo;
        pila->cantidad++;
    }
}
void* pop(Pila *pila)
{
    if(vacia(*pila))
    {
        printf("\n Underflow");
        return NULL;
    }
    else
    {
        Nodo *aux = pila->cima;     
        pila->cima = aux->sig;
        aux->sig = NULL;
        void *dato = aux->dato;
        free(aux);
        pila->cantidad--;
        return dato;
    }
}

void push_nodo(Pila *pila,Nodo *nuevo)
{
    if(llena(*pila))
    {
        printf("\n Overflow");
    }
    else
    {
        nuevo->sig = pila->cima;
        pila->cima = nuevo;
        pila->cantidad++;
    }
}

Nodo* pop_nodo(Pila *pila)
{
    if(vacia(*pila))
    {
        printf("\n Underflow");
        return NULL;
    }
    else
    {
        Nodo *aux = pila->cima;     
        pila->cima = aux->sig;
        aux->sig = NULL;
        pila->cantidad--;
        return aux;
    }
}

void imprimirPila(Pila pila)
{
    Pila aux = (Pila){NULL,pila.capacidad,0,NULL};
    Nodo *nodo;
    printf("\n\nPila [%d]:",pila.cantidad);
    while( !vacia(pila) )
    {
        nodo = pop_nodo(&pila);
        printf("\n ");
        pila.imprimir(nodo->dato);
        push_nodo(&aux,nodo);
    }
    while( !vacia(aux) )
        push_nodo(&pila,pop_nodo(&aux));
}
void imprimirPilaInvertida(Pila pila)
{
    Pila aux = (Pila){NULL,pila.capacidad,0,NULL};
    Nodo *nodo;
    printf("\n\nPila Invertida [%d]:",pila.cantidad);
    while( !vacia(pila) )
        push_nodo(&aux,pop_nodo(&pila));
    while( !vacia(aux) )
    {       
        nodo = pop_nodo(&aux);
        printf("\n ");
        pila.imprimir(nodo->dato);
        push_nodo(&pila,nodo);
    }   
}

void eliminarPila(Pila *pila)
{
    void *dato;
    while(!vacia(*pila))
    {
        dato = pop(pila);
        if( pila->liberar )
            pila->liberar(dato);
    }
}

void inicializarPila(Pila *pila)
{
    pila->cima = NULL;
    pila->capacidad = 0;
    pila->cantidad = 0;
    pila->imprimir = NULL;
    pila->liberar = NULL;
}

int palindromo(Pila *pila)
{
    int x;
    char mensaje[50];
    int bandera = 1;

    printf("\nVerificacion del palindromo\n");
    x = inputCadena("Ingrese un palindromo: ", mensaje, 50);

    if(x != 0)
    {
        int i = 0;
        while(mensaje[i] != '\0')
        {
            //Asigna memoria para cada caracter y almacena la copia
            char* caracter = malloc(sizeof(char));
            if(caracter) {
                *caracter = mensaje[i];
                Nodo* nuevo = crearNodo(caracter);
                push_nodo(pila, nuevo);
            }
            i++;
        }

        int j = 0;
        
        while(pila->cantidad != 0)
        {
            Nodo* nuevo = pop_nodo(pila);
            char letra = *((char*)nuevo->dato);
            if(letra != mensaje[j])
            {
                bandera = 0;
            }
            free(nuevo->dato);
            free(nuevo);
            j++;
        }


    }

    return bandera;
}

void parentesis(Pila *pila)
{
    int bandera = 1;
    char mensaje[50];
    int x = inputCadena("Ingresa tu mensaje: ", mensaje, 50);

    if(x != 0)
    {
        int i = 0;
        while(mensaje[i] != '\0')
        {
            if(mensaje[i] == '(' || mensaje[i] == '{' || mensaje[i] == '[')
            {     
		
                char* caracter = malloc(sizeof(char));
                if(caracter) {
                    *caracter = mensaje[i];
                    Nodo* nuevo = crearNodo(caracter);
                    push_nodo(pila, nuevo);
                }
            }
            else if(mensaje[i] == ')' || mensaje[i] == '}' || mensaje[i] == ']')
            {
                if(vacia(*pila))
                {
                    bandera = 0;
                    break;
                }

                Nodo* nuevo1 = pop_nodo(pila);
                char caracter = *((char*)nuevo1->dato);

                switch(mensaje[i])
                {
                    case ')':
                        if(caracter != '(')
                            bandera = 0;
                        break;
                    case '}':
                        if(caracter != '{')
                            bandera = 0;
                        break;
                    case ']':
                        if(caracter != '[')
                            bandera = 0;
                        break;
                }

                free(nuevo1->dato);
                free(nuevo1);
            }

            i++;
        }

        while(!vacia(*pila))
        {
            Nodo* nodo = pop_nodo(pila);
            free(nodo->dato);
            free(nodo);
            bandera = 0;
        }

        if(bandera != 1)
            printf("\nLa verificacion de parentesis es incorrecta\n");
        else
            printf("\nLa verificacion de parentesis es correcta\n");
    }
}

int prioridad(char op) {

    int valor = 0;

    switch (op) 
    {
        case '^': 
            valor = 3;
        break;

        case '*': 
            valor = 2;
        break;

        case '/': 
            valor = 2;
        break;

        case '+':
            valor = 1;
        break;

        case '-': 
            valor = 1;
        break;

        default:
            valor = 0;
        break;
    }

    return valor; 
}

void* peek_nodo(Pila pila)
{
    if (vacia(pila)) {
        return NULL;
    }
    return pila.cima->dato; 
}

