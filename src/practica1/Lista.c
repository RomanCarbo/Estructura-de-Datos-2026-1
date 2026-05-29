#include "Lista.h"

void borrarLista(Lista *lista) {
    Nodo *actual, *anterior = NULL;
    for (actual = lista->inicio; actual != NULL;) {
        anterior = actual;
        actual = actual->sig;
        free(anterior->dato);
        free(anterior);
    }
    lista->inicio = NULL;
    lista->cant = 0;
}

void borrarDato(Lista *lista, void* dato) {
    Nodo *actual, *anterior = NULL;
    for (actual = lista->inicio; actual != NULL; actual = actual->sig) {
        if (lista->comparar(dato, actual->dato) == 0) {
            if (anterior != NULL)
                anterior->sig = actual->sig;
            else
                lista->inicio = actual->sig;
            free(actual->dato);
            free(actual);
            lista->cant--;
            break;
        }
        anterior = actual;
    }
}

void* buscarDato(Lista lista, void *dato) {
    Nodo *actual;
    for (actual = lista.inicio; actual != NULL; actual = actual->sig) {
        if (lista.comparar(dato, actual->dato) == 0)
            return actual->dato;
    }
    return NULL;
}

void insertarOrdenado(Nodo **lista, void* dato, int (*cmp)(void*, void*)) {
    Nodo *nuevo = crearNodo(dato);
    if (*lista == NULL || cmp(dato, (*lista)->dato) < 0) {
        nuevo->sig = *lista;
        *lista = nuevo;
        return;
    }
    Nodo *actual = *lista;
    while (actual->sig && cmp(dato, actual->sig->dato) > 0)
        actual = actual->sig;
    nuevo->sig = actual->sig;
    actual->sig = nuevo;
}

void mostrarLista(Lista lista) {
    Nodo *p;
    printf("\nLista %d:\n", lista.cant);
    for (p = lista.inicio; p != NULL; p = p->sig) {
        lista.imprimir(p->dato);
        printf("\n");
    }
    if (lista.cant == 0)
        printf("Lista esta vacia\n");
}

void insertarFinal(Lista *lista, void* dato) {
    Nodo *nuevo = crearNodo(dato);
    if (lista->inicio == NULL) {
        lista->inicio = nuevo;
    } else {
        Nodo *p;
        for (p = lista->inicio; p->sig != NULL; p = p->sig);
        p->sig = nuevo;
    }
    lista->cant++;
}

void insertarInicio(Lista *lista, void* dato) {
    Nodo *nuevo = crearNodo(dato);
    nuevo->sig = lista->inicio;
    lista->inicio = nuevo;
    lista->cant++;
}

void insertarEnPosicion(Lista *lista, void* dato, int pos) {
    if (pos < 0 || pos > lista->cant)
		return;
    if (pos == 0) {
        insertarInicio(lista, dato);
        return;
    }
    Nodo *nuevo = crearNodo(dato);
    Nodo *actual = lista->inicio;
    for (int i = 0; i < pos - 1; i++)
        actual = actual->sig;
    nuevo->sig = actual->sig;
    actual->sig = nuevo;
    lista->cant++;
}

void eliminarEnPosicion(Lista *lista, int pos) {
    if (pos < 0 || pos >= lista->cant) return;
    Nodo *actual = lista->inicio, *anterior = NULL;
    for (int i = 0; i < pos; i++) {
        anterior = actual;
        actual = actual->sig;
    }
    if (anterior == NULL)
        lista->inicio = actual->sig;
    else
        anterior->sig = actual->sig;
    free(actual->dato);
    free(actual);
    lista->cant--;
}
