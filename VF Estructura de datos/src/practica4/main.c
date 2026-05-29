#include <stdio.h>
#include <stdlib.h>
#include "Laberinto.h"
#include "../Estructuras/pila/pila.h" 

int main(void){
    Pila pila;
    inicializarPila(&pila);
    pila.imprimir = &imprimirCoordenada;

    unsigned char **lab = crear_laberinto();
    lab[3][16] = 'B';
	lab[18][1] = 'A';
    
    imprimirLab(lab);
    getchar();

    Coordenada* inicio = buscarInicio(lab); 
    Coordenada *coord = crearCoordenada(inicio->x, inicio->y);
    push(&pila, coord);

    while(lab[coord->x][coord->y] !='B'){ 
        if(avanzar(alternativas(lab, coord), &coord)){
            Coordenada *nueva = crearCoordenada(coord->x, coord->y);
            push(&pila, nueva);
            if(lab[coord->x][coord->y] != 'B'){
                lab[coord->x][coord->y] = '.';
            }
        } else {
            lab[coord->x][coord->y] = 'o'; 
            
            free(pop(&pila));

            Coordenada* anterior = pop(&pila);
            coord->x = anterior->x;
            coord->y = anterior->y;
            
            push(&pila, anterior);
        }
    }
	imprimirLab(lab);
    printf("\n\nFinalizado.\n");
    free(inicio); 
    
    return 0;
}