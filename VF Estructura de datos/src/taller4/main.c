#include <stdio.h>
#include <string.h>

void imprimirArbolEstructura(int arr[], int n, int index, char* prefijo, int esIzquierdo, int esRaiz) {
    if (index >= n) return;

    if (esRaiz) {
        printf("%d\n", arr[index]);
    } else {
        printf("%s", prefijo);
        printf("%s %d\n", esIzquierdo ? "|----L" : "|----R", arr[index]);
    }

    char nuevoPrefijo[512];
    strcpy(nuevoPrefijo, prefijo);
    if (!esRaiz) {
        if (esIzquierdo) {

            strcat(nuevoPrefijo, "        "); 
        } else {

            strcat(nuevoPrefijo, "|       "); 
        }
    }


    int izq = 2 * index + 1;
    int der = 2 * index + 2;


    if (der < n) {

        printf("%s|\n", nuevoPrefijo);
        if (izq < n && !esRaiz) {
            printf("%s|\n", nuevoPrefijo); 
        }
        imprimirArbolEstructura(arr, n, der, nuevoPrefijo, 0, 0);
    }

    if (esRaiz && izq < n) {
        printf("|\n");
    }

    if (izq < n) {
        printf("%s|\n", nuevoPrefijo);
        imprimirArbolEstructura(arr, n, izq, nuevoPrefijo, 1, 0);
    }
}

int main(void) {
    int heap[] = {7, 4, 5, 2, 1, 3};
    int n = sizeof(heap) / sizeof(heap[0]);

    printf("Ejemplo con un heap maximo:\n");
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", heap[i], i < n - 1 ? " , " : "");
    }
    printf(" ]\n\n");

    printf("Imprimir el Arbol\n");
    if (n == 0) {
        printf("Arbol vacio\n");
    } else {
        imprimirArbolEstructura(heap, n, 0, "", 0, 1);
    }

    return 0;
}