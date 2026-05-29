#include "Laberinto.h"

unsigned char **crear_laberinto(void){
    int i, j;
    char *tmp = 
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
x*x*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x**************x\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

    unsigned char **lab = (unsigned char**) malloc(sizeof(unsigned char *)*REN);
    for(i = 0; i < REN; i++){
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char)*COL);
    }
    for(i = 0; i < REN; i++){
        for(j = 0; j < COL; j++){
            lab[i][j] = tmp[(i*COL)+j];
        }   
    }
    return lab;
}

void imprimirLab(unsigned char **lab){
    for(int i = 0; i < REN; i++){
        printf("\n\r");
        for(int j = 0; j < COL; j++){
            if(lab[i][j] == '*') printf("  ");
            else printf("%c ", lab[i][j]);
        }
    }
}

Coordenada* buscarInicio(unsigned char **lab) {
    Coordenada *inicio = malloc(sizeof(Coordenada));
    for (int i = 0; i < REN; i++) {
        for (int j = 0; j < COL; j++) {
            if (lab[i][j] == 'A') {
                inicio->x = i;
                inicio->y = j;
                return inicio; 
            }
        }
    }
    inicio->x = 0;
    inicio->y = 0;
    return inicio;
}