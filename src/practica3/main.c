#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

#define LONGITUD 64

void imprimirCadena(void *a);
void liberarCadena(void *a);

int main(void)
{
    Pila pila;
    inicializarPila(&pila);
	pila.imprimir = imprimirCadena;

    int opc = 0;

    do {
        printf("---- MENU ----\n");
        printf("[1] Palindromo\n[2] Verificar parentesis\n[3] Salir\n");
        inputEntero("Seleccione una opcion: ", &opc);

        switch(opc)
        {
            case 1:
            {
                int i = palindromo(&pila);

                if(i == 1)
                    printf("\nSi es un palindromo\n");
                else
                    printf("\nNo es un palindromo\n");
            }
            break;

            case 2:
            {
                printf("\nVerificacion de parentesis\n");
                parentesis(&pila);
            }
            break;

            case 3:
                printf("\nPrograma finalizado.\n");
                break;

            default:
                printf("\nOpcion invalida\n");
                break;
        }
    } while(opc != 3);

    return 0;
}

void imprimirCadena(void *dato)
{
    char *aux = (char*)dato;
    printf("%s\n", aux);
}

void liberarCadena(void *dato)
{
    char *aux = (char*)dato;
    free(aux);
}