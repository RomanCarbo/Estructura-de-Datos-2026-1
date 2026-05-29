#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Estructuras/pila/pila.h"
#include "../Estructuras/arbol/arbol.h"

typedef struct {
    char caracter;
    float *valor;
} Dato;

void imprimir_letra(void *dato);
int validar_parentesis(char *cadena);
int prioridad(char c);
int esOperador(char caracter);
Dato* crearDato(char caracter);
void liberarDato(void *dato);
void imprimirDatoArbol(void *dato);
void postfixArbolDirecto(char* postfix, Arbol* arbol, Pila *pila);
void capturarValores(NodoA* raiz, char letras[], float valores[], int *n);
float realizarCalculo(float a, float b, char op);
float evaluarArbol(NodoA* raiz);


int main(void){
    Pila pila;
    inicializarPila(&pila);
    pila.imprimir = imprimir_letra;

    Arbol arbol;
    arbol.raiz = NULL;
    arbol.cantidad = 0;
    arbol.imprimir = imprimirDatoArbol;
    arbol.comparar = NULL;
    arbol.liberar = liberarDato;

    char cadena[50]; 
    char aux[50];
    int arbolCreado = 0;

    int opc = 0;
    do {
        printf("\n\n--- MENU ---\n\n");
        printf("[1] Capturar expresion\n");
        printf("[2] Imprimir arbol de expresion\n");
        printf("[3] Evaluar expresion\n");
        printf("[4] Terminar programa\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opc);
        while(getchar() != '\n');

        switch(opc){
            case 1:
            {
                if(arbolCreado){
                    liberarArbol(&arbol);
                    arbol.raiz = NULL;
                    arbolCreado = 0;
                }

                int daux = 0;
                memset(aux, 0, sizeof(aux));

                printf("Ingresa la ecuacion Infix: ");
                scanf("%s", cadena);
                
                if (validar_parentesis(cadena) == 0) {
                    printf("\nLa verificacion de parentesis es incorrecta.\n");
                    break;
                }

                int tamano = strlen(cadena);

                for(int i = 0; i < tamano; i++){
                    char caracter = cadena[i];

                    if (caracter == '(') {
                        char *nuevo = malloc(sizeof(char));
                        *nuevo = caracter;
                        push(&pila, nuevo);
                    } 
                    else if (caracter == ')') {
                        while(pila.cima != NULL) {
                            char cima = *(char*)peek_nodo(pila);
                            if (cima == '(') {
                                free(pop(&pila));
                                break;
                            } else {
                                aux[daux] = *(char*)pop(&pila);
                                daux++;
                            }
                        }
                    } 
                    else if (prioridad(caracter) == 0) {
                        aux[daux] = caracter;
                        daux++;
                    } 
                    else {
                        while(pila.cima != NULL) {
                            char cima = *(char*)peek_nodo(pila);
                            if (cima == '(' || prioridad(caracter) > prioridad(cima)) {
                                break;
                            }
                            aux[daux] = *(char*)pop(&pila);
                            daux++;
                        }
                        char *nuevo = malloc(sizeof(char));
                        *nuevo = caracter;
                        push(&pila, nuevo);
                    }
                }

                while(pila.cima != NULL) {
                    aux[daux] = *(char*)pop(&pila);
                    daux++;
                }
                aux[daux] = '\0';

                printf("\nPostfix generado: %s\n", aux);

                postfixArbolDirecto(aux, &arbol, &pila);
                arbolCreado = 1;
                printf("Arbol de expresion creado con exito.\n");
                break;
            }
            case 2:
                if(!arbolCreado){
                    printf("\nPrimero debes capturar una expresion (Opcion 1).\n");
                } else {
                    printf("\nArbol: \n");
                    imprimirArbol(arbol);
                }
                break;
            case 3:
            {
                if(!arbolCreado){
                    printf("\nPrimero debes capturar una expresion (Opcion 1).\n");
                    break;
                }
                char letras[50];
                float valores[50];
                int n = 0;

                capturarValores(arbol.raiz, letras, valores, &n);
                printf("\nValores capturados correctamente.");
                
                float resultado = evaluarArbol(arbol.raiz);
                printf("\nEl resultado de la expresion es: %.2f\n", resultado);
                break;
            }
            case 4:
                printf("\nAdios\n");
                break;
            default:
                printf("\nOpcion fuera de rango\n");
                break;
        }
    } while(opc != 4);

    eliminarPila(&pila);
    liberarArbol(&arbol);
    
    return 0;
}

void postfixArbolDirecto(char* postfix, Arbol* arbol, Pila *pila) {
    int i = 0;
    while(postfix[i] != '\0'){
        char a = postfix[i];
        
        Dato *nuevoDato = crearDato(a);
        NodoA *nuevoNodoA = crearNodoA(nuevoDato);

        if(prioridad(a) == 0){
            push_nodo(pila, crearNodo(nuevoNodoA)); 
        } 
        else if(esOperador(a)){
            Nodo* nodo_dch = pop_nodo(pila);
            NodoA* hijo_derecho = (NodoA*)(nodo_dch->dato); 
            free(nodo_dch); 

            Nodo* nodo_izq = pop_nodo(pila);
            NodoA* hijo_izquierdo = (NodoA*)(nodo_izq->dato); 
            free(nodo_izq);

            nuevoNodoA->dch = hijo_derecho;
            nuevoNodoA->izq = hijo_izquierdo;
            
            push_nodo(pila, crearNodo(nuevoNodoA));
        }
        i++;
    }
    
    Nodo* nodo = pop_nodo(pila);
    arbol->raiz = (NodoA*)(nodo->dato);
    free(nodo);
}

int esOperador(char caracter) {
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^');
}

Dato* crearDato(char caracter) {
    Dato *nuevo = (Dato*)calloc(1, sizeof(Dato));
    if (nuevo) {
        nuevo->caracter = caracter;
        nuevo->valor = NULL;
    }
    return nuevo;
}

void liberarDato(void *dato) {
    if (dato) {
        Dato *info = (Dato*)dato;
        if (info->valor) free(info->valor);
        free(info); 
    }
}

void imprimir_letra(void *dato) {
    printf("%c", *(char*)dato); 
}

void imprimirDatoArbol(void *dato) {
    Dato *info = (Dato*)dato;
    if (info) 
        printf("%c", info->caracter);
}

int validar_parentesis(char *cadena) {
    Pila pilaVal;
    inicializarPila(&pilaVal);
    int bandera = 1;

    for(int i = 0; cadena[i] != '\0'; i++) {
        if(cadena[i] == '(') {
            char *c = malloc(sizeof(char));
            *c = cadena[i];
            push(&pilaVal, c);
        } 
        else if(cadena[i] == ')') {
            if(pilaVal.cima == NULL) {
                bandera = 0;
                break;
            }
            free(pop(&pilaVal));
        }
    }
    if(pilaVal.cima != NULL) bandera = 0;
    
    while(pilaVal.cima != NULL) free(pop(&pilaVal));
    
    return bandera;
}

float realizarCalculo(float a, float b, char op) {
    switch(op) {
        case '+': 
            return a + b;
        case '-': 
         return a - b;
        case '*': 
            return a * b;
        case '/': 
            return (b == 0) ? 0 : a / b;
        case '^': 
            return pow(a, b);
        default: 
            return 0;
    }
}

float evaluarArbol(NodoA* raiz) {
    if (raiz == NULL) return 0;
    Dato* info = (Dato*)raiz->dato; 

    if (!esOperador(info->caracter)) { 
        return (info->valor != NULL) ? *(info->valor) : 0;
    }

    float val_izq = evaluarArbol(raiz->izq);
    float val_dch = evaluarArbol(raiz->dch);

    return realizarCalculo(val_izq, val_dch, info->caracter);
}

void capturarValores(NodoA* raiz, char letras[], float valores[], int *n) {
    if (raiz == NULL) return;

    capturarValores(raiz->izq, letras, valores, n);

    Dato* info = (Dato*)raiz->dato;
    if (!esOperador(info->caracter)) {
        if (info->valor != NULL) {
            free(info->valor);
            info->valor = NULL;
        }
        
        int i, existe = 0;
        for (i = 0; i < *n; i++) {
            if (letras[i] == info->caracter) {
                existe = 1;
                break;
            }
        }
        
        info->valor = (float*)malloc(sizeof(float));
        if (!existe) {
            letras[*n] = info->caracter;
            printf("Ingresa el valor para %c: ", info->caracter);
            scanf("%f", &valores[*n]);
            *(info->valor) = valores[*n];
            (*n)++;
        } else {
            *(info->valor) = valores[i];
        }
    }

    capturarValores(raiz->dch, letras, valores, n);
}