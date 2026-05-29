#ifndef LABERINTO_H
#define LABERINTO_H

#include <stdio.h>
#include <stdlib.h>

#define ARRIBA 1
#define ABAJO 2
#define DERECHA 3
#define IZQUIERDA 4

#define REN 27
#define COL 26

typedef struct{
    int x, y;
} Coordenada;

unsigned char **crear_laberinto(void);
void imprimirLab(unsigned char **lab);
Coordenada* buscarInicio(unsigned char **lab);

Coordenada* crearCoordenada(int x, int y);
int compararCoordenada(void *a, void *b);
void imprimirCoordenada(void *dato);

unsigned char alternativas(unsigned char **lab, Coordenada *coordenada);
void imprimirPosibles(unsigned char caminos);
int avanzar(unsigned char posible, Coordenada **nueva);

#endif