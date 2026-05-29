#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estructuras/pila/pila.h" 
void imprimir_letra(void *dato);
int validar_parentesis(char *cadena);

int main(void){
    Pila *pila = malloc(sizeof(Pila));
    pila->cima = NULL;
    pila->cantidad = 0;
    pila->imprimir = imprimir_letra;

    char cadena[50]; 
    char aux[50];
    int daux = 0;

    printf("Infix: ");
    scanf("%s", cadena);
    
    if (validar_parentesis(cadena) == 0) {
        printf("\nLa verificacion de parentesis es incorrecta.\n");
        return 0;
    }
    printf("\nLa verificacion de parentesis es correcta.\n");

    int tamano = 0;
    while(cadena[tamano] != '\0'){
        tamano++;
    }

    for(int i = 0; i < tamano; i++){
        char caracter = cadena[i];


        if (caracter == '(') {
            char *nuevo = malloc(sizeof(char));
            *nuevo = caracter;
            push(pila, nuevo);
        } 

        else if (caracter == ')') {
            while(pila->cima != NULL) {
                char cima = *(char*)peek_nodo(*pila);
                
                if (cima == '(') {
                    free(pop(pila));
                    break;
                } else {
                    aux[daux] = *(char*)pop(pila);
                    daux++;
                }
            }
        } 
        else if (prioridad(caracter) == 0) {
            aux[daux] = caracter;
            daux++;
        } 
        else {
            while(pila->cima != NULL) {
                char cima = *(char*)peek_nodo(*pila);
                
                if (cima == '(' || prioridad(caracter) > prioridad(cima)) {
                    break;
                }
                
                aux[daux] = *(char*)pop(pila);
                daux++;
            }
            
            char *nuevo = malloc(sizeof(char));
            *nuevo = caracter;
            push(pila, nuevo);
        }
        
    }

    while(pila->cima != NULL) {
        aux[daux] = *(char*)pop(pila);
        daux++;
    }
    
    aux[daux] = '\0';
    
    printf("Postfix: %s\n", aux);

    return 0;
}
void imprimir_letra(void *dato) {
    printf("%c", *(char*)dato); 
}

int validar_parentesis(char *cadena) {
    Pila *pilaVal = malloc(sizeof(Pila));
    pilaVal->cima = NULL;
    int bandera = 1;

    for(int i = 0; cadena[i] != '\0'; i++) {
        if(cadena[i] == '(') {
            char *c = malloc(sizeof(char));
            *c = cadena[i];
            push(pilaVal, c);
        } 
        else if(cadena[i] == ')') {
            if(pilaVal->cima == NULL) {
                bandera = 0;
                break;
            }
            free(pop(pilaVal));
        }
    }
    if(pilaVal->cima != NULL) {
        bandera = 0;
    }
    
    while(pilaVal->cima != NULL) {
        free(pop(pilaVal));
    }
    free(pilaVal);
    
    return bandera;
}