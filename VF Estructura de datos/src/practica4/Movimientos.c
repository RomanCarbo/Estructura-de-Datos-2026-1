#include "Laberinto.h"

unsigned char alternativas(unsigned char **lab, Coordenada *coordenada){
    unsigned char caracter;

    caracter = lab[coordenada->x-1][coordenada->y];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        return ARRIBA;

    caracter = lab[coordenada->x+1][coordenada->y];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        return ABAJO;

    caracter = lab[coordenada->x][coordenada->y+1];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        return DERECHA;


    caracter = lab[coordenada->x][coordenada->y-1];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        return IZQUIERDA;

    return 0; 
}

int avanzar(unsigned char posible, Coordenada **nueva){
    if(posible == ARRIBA){ 
        (*nueva)->x--;
        return 1;
    }
    if(posible == ABAJO){
        (*nueva)->x++;
        return 1;
    }
    if(posible == DERECHA){
        (*nueva)->y++;
        return 1;
    }
    if(posible == IZQUIERDA){
        (*nueva)->y--;
        return 1;
    }
    
    return 0;
}
void imprimirPosibles(unsigned char caminos){
    if(caminos & ARRIBA) printf("\nARRIBA");
    if(caminos & ABAJO) printf("\nABAJO");
    if(caminos & IZQUIERDA) printf("\nIZQUIERDA");
    if(caminos & DERECHA) printf("\nDERECHA");
}