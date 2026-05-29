
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
void liberarEntero(void*);

void myprintf(char *formato,...);

int main(void)
{
	Arbol arbolA;
	arbolA.raiz = NULL;
	arbolA.cantidad = 0;
	arbolA.imprimir = &imprimirEntero;
	arbolA.comparar = &compararEntero;
	arbolA.liberar = &liberarEntero;
	
	Arbol arbolB;
	arbolB.raiz = NULL;
	arbolB.cantidad = 0;
	arbolB.imprimir = &imprimirEntero;
	arbolB.comparar = &compararEntero;
	arbolB.liberar = &liberarEntero;
	
	int opc, valor;
	
	do{
		printf("\n\n--- MENU ---\n\n");
		printf("\n[1] Insertar en Arbol A");
		printf("\n[2] Insertar en Arbol B");
		printf("\n[3] Comparar Arboles");
		printf("\n[4] Eliminar dato en Arbol A");
		printf("\n[5] Eliminar dato en Arbol B");
		printf("\n[6] Profundidades");
		printf("\n[7] Equilibrar arboles");
		printf("\n[8] Mostrar arboles");
		printf("\n[9] Terminar programa");
		printf("\nSelecciona una opcion: ");
		scanf("%d", &opc);
		
		switch(opc)
		{
			case 1:
				printf("\nIngresa el valor a insertar en el Arbol A: ");
				scanf("%d", &valor);
				insertarArbol(&arbolA, crearEntero(valor));
				printf("\nValor %d insertado en Arbol A.", valor);
				break;
				
			case 2:
				printf("\nIngresa el valor a insertar en el Arbol B: ");
				scanf("%d", &valor);
				insertarArbol(&arbolB, crearEntero(valor));
				printf("\nValor %d insertado en Arbol B.", valor);
				break;
				
			case 3:
				if (sonIguales(arbolA.raiz, arbolB.raiz))
				{
					printf("\nLos arboles son iguales en estructura y datos.");
				}
				else if (mismosDatos(arbolA.raiz, arbolB.raiz))
				{
					printf("\nLos arboles tienen los mismos datos pero diferente estructura.");
				}
				else
				{
					printf("\nLos arboles son diferentes.");
				}
				break;
				
			case 4:
				printf("Ingresa el valor a eliminar del Arbol A: ");
				scanf("%d", &valor);
				if (eliminarArbol(&arbolA, valor))
					printf("\nValor %d eliminado del Arbol A.", valor);
				else
					printf("\nValor %d no encontrado en el Arbol A.", valor);
				break;
				
			case 5:
				printf("Ingresa el valor a eliminar del Arbol B: ");
				scanf("%d", &valor);
				if (eliminarArbol(&arbolB, valor))
					printf("\nValor %d eliminado del Arbol B.", valor);
				else
					printf("\nValor %d no encontrado en el Arbol B.", valor);
				break;
				
			case 6:
				printf("\nProfundidades: \n");
				printf("\nProfundidad del Arbol A: %d", calcularAltura(arbolA.raiz));
				printf("\nProfundidad del Arbol B: %d", calcularAltura(arbolB.raiz));
				break;
				
			case 7:
				equilibrarArbol(&arbolA);
				equilibrarArbol(&arbolB);
				printf("\nNueva altura Arbol A: %d", calcularAltura(arbolA.raiz));
				printf("\nNueva altura Arbol B: %d", calcularAltura(arbolB.raiz));
				break;
				
			case 8:
				printf("\nARBOL A\n");
				if (arbolA.raiz)
				{
					printf("\nCantidad de nodos: %d", arbolA.cantidad);
					printf("\nEstructura del arbol:\n");
					imprimirArbol(arbolA);
				}
				else
					printf("\nEl Arbol A esta vacio.");
				
				printf("\nARBOL B\n");
				if (arbolB.raiz)
				{
					printf("\nCantidad de nodos: %d", arbolB.cantidad);
					printf("\nEstructura del arbol:\n");
					imprimirArbol(arbolB);
				}
				else
					printf("\nEl Arbol B esta vacio.");
				break;
				
			case 9:
				printf("\nAdios\n");
				liberarArbol(&arbolA);
				liberarArbol(&arbolB);
				break;
				
			default:
				printf("\nOpcion invalida");
		}

		
	}while(opc != 9);
}


int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}

void liberarEntero(void *a)
{
	free(a);
}