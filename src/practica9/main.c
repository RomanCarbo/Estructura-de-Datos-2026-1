#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Estructuras/hash/hashtable.h"
#include "../Estructuras/arbol/arbol.h"
#include "Libro.h"
#include "../Estructuras/cola/cola.h" 

HashTable ht_isbn, ht_titulo, ht_autor, ht_anio, ht_ini_tit, ht_ini_aut;

void limpiarBuffer();

void temporal(void *dato);

void imprimirLibroConSalto(void *dato);

int comparar_para_arbol(void *a, void *b);

int folding_isbn(void *dato);
int comparar_isbn(void *a, void *b);

int folding_titulo(void *dato);
int comparar_titulo(void *a, void *b);

int folding_autor(void *dato);
int comparar_autor(void *a, void *b);

int folding_anio(void *dato);
int comparar_anio(void *a, void *b);

int folding_inicial_titulo(void *dato);
int comparar_inicial_titulo(void *a, void *b);

int folding_inicial_autor(void *dato);
int comparar_inicial_autor(void *a, void *b);

int comparar_para_arbol(void *a, void *b);

void inicializar_tabla();
void agregar_libro_a_tablas(Libro *l);
void eliminar_libro_de_tablas(Libro *l);
void mostrar_resultados(Cola *c, int indice);



int main(void)
{
    inicializar_tabla();

    Libro *libros = obtener_libros();
    for(int i = 0; i < CANT_LIBROS; i++) {
        agregar_libro_a_tablas(&libros[i]);
    }

    int opc, subopc;
    Libro libroAuxiliar; 
    Cola resultados;

    do {
        
        printf("\n1. Buscar por ISBN");
        printf("\n2. Buscar por Titulo");
        printf("\n3. Buscar por Autor");
        printf("\n4. Buscar por Fecha");
        printf("\n5. Eliminar Libro");
        printf("\n6. agregar Libro");
        printf("\n7. Salir");
        printf("\nSelecciona: ");
        scanf("%d", &opc); limpiarBuffer();

        switch(opc) {
            case 1:
                printf("Ingrese ISBN : ");
                fgets(libroAuxiliar.isbn, MAX_ISBN, stdin);
                libroAuxiliar.isbn[strcspn(libroAuxiliar.isbn, "\n")] = 0; 
                
                resultados = buscarClave(&ht_isbn, &libroAuxiliar);
                mostrar_resultados(&resultados, 1);
                break;

            case 2: 
                printf("\n1. Titulo Exacto\n2. Rango de iniciales\nSelecciona: ");
                scanf("%d", &subopc); limpiarBuffer();
                if(subopc == 1) {
                    printf("Ingrese Titulo: ");
                    fgets(libroAuxiliar.titulo, MAX_TITULO, stdin);
                    libroAuxiliar.titulo[strcspn(libroAuxiliar.titulo, "\n")] = 0;
                    
                    resultados = buscarClave(&ht_titulo, &libroAuxiliar);
                    mostrar_resultados(&resultados, 2);
                } else {
                    char ini, fin;
                    printf("Inicial Inicio (A-Z): "); scanf("%c", &ini); limpiarBuffer();
                    printf("Inicial Fin (A-Z): "); scanf("%c", &fin); limpiarBuffer();
                    
                    Cola acumulada = inicializarCola();
                    for(char c = toupper(ini); c <= toupper(fin); c++) {
                        libroAuxiliar.titulo[0] = c; libroAuxiliar.titulo[1] = '\0';
                        Cola parcial = buscarClave(&ht_ini_tit, &libroAuxiliar);
                        
                        while(!vaciaC(parcial)) {
                             enqueue(&acumulada, dequeue(&parcial));
                        }
                    }
                    mostrar_resultados(&acumulada, 2);
                }
                break;

            case 3: 
                printf("\n1. Nombre Exacto\n2. Rango de iniciales \n Seleccionar: ");
                scanf("%d", &subopc); limpiarBuffer();
                if(subopc == 1) {
                    printf("Ingrese Autor: ");
                    fgets(libroAuxiliar.autor, MAX_AUTOR, stdin);
                    libroAuxiliar.autor[strcspn(libroAuxiliar.autor, "\n")] = 0;
                    
                    resultados = buscarClave(&ht_autor, &libroAuxiliar);
                    mostrar_resultados(&resultados, 3);
                } else {
                    char ini, fin;
                    printf("Inicial Inicio (A-Z): "); scanf("%c", &ini); limpiarBuffer();
                    printf("Inicial Fin (A-Z): "); scanf("%c", &fin); limpiarBuffer();
                    
                    Cola acumulada = inicializarCola();
                    for(char c = toupper(ini); c <= toupper(fin); c++) {
                        libroAuxiliar.autor[0] = c; libroAuxiliar.autor[1] = '\0';
                        Cola parcial = buscarClave(&ht_ini_aut, &libroAuxiliar);
                        
                        while(!vaciaC(parcial)) {
                            enqueue(&acumulada, dequeue(&parcial));
                        }
                    }
                    mostrar_resultados(&acumulada, 3);
                }
                break;

            case 4: 
                printf("\n1. Anio Exacto\n2. Rango de Anios\nSeleccionar: ");
                scanf("%d", &subopc); limpiarBuffer();
                if(subopc == 1) {
                    printf("Ingrese Anioo: ");
                    scanf("%d", &libroAuxiliar.fecha); limpiarBuffer();
                    
                    resultados = buscarClave(&ht_anio, &libroAuxiliar);
                    mostrar_resultados(&resultados, 4);
                } else {
                    int ini, fin;
                    printf("Anio Inicio: "); scanf("%d", &ini);
                    printf("Anio Fin: "); scanf("%d", &fin); limpiarBuffer();
                    
                    Cola acumulada = inicializarCola();
                    for(int y = ini; y <= fin; y++) {
                        libroAuxiliar.fecha = y;
                        Cola parcial = buscarClave(&ht_anio, &libroAuxiliar);
                        
                        while(!vaciaC(parcial)) {
                            enqueue(&acumulada, dequeue(&parcial));
                        }
                    }
                    mostrar_resultados(&acumulada, 4);
                }
                break;
            
            case 5: 
                printf("Ingrese ISBN del libro a eliminar: ");
                fgets(libroAuxiliar.isbn, MAX_ISBN, stdin);
                libroAuxiliar.isbn[strcspn(libroAuxiliar.isbn, "\n")] = 0;

                resultados = buscarClave(&ht_isbn, &libroAuxiliar);
                
                if(vaciaC(resultados)) {
                    printf("Error: Libro no encontrado.\n");
                } else {
                    Libro *libroReal = (Libro*)dequeue(&resultados);
                    eliminar_libro_de_tablas(libroReal);
                    printf("Libro '%s' eliminado de todas las tablas exitosamente.\n", libroReal->titulo);
                }
                break;

            case 6:
                printf("Ingrese ISBN: ");
                fgets(libroAuxiliar.isbn, MAX_ISBN, stdin);
                libroAuxiliar.isbn[strcspn(libroAuxiliar.isbn, "\n")] = 0;
    
    
                resultados = buscarClave(&ht_isbn, &libroAuxiliar);
                    if(!vaciaC(resultados)) {
                        printf("Error: Ya existe un libro con ese ISBN.\n");
                     break;
                }
    
                printf("Ingrese Titulo: ");
                fgets(libroAuxiliar.titulo, MAX_TITULO, stdin);
                libroAuxiliar.titulo[strcspn(libroAuxiliar.titulo, "\n")] = 0;
    
                printf("Ingrese Autor: ");
                fgets(libroAuxiliar.autor, MAX_AUTOR, stdin);
                libroAuxiliar.autor[strcspn(libroAuxiliar.autor, "\n")] = 0;
    
                printf("Ingrese Anio: ");
                 scanf("%d", &libroAuxiliar.fecha); 
                 limpiarBuffer();
    
                printf("Disponible 1=Si, 0=No: ");
                scanf("%d", &libroAuxiliar.disponible); limpiarBuffer();
    
    
                Libro *nuevoLibro = (Libro*)malloc(sizeof(Libro));
                if(nuevoLibro == NULL) {
                printf("No se puedeo agregar.\n");
                    break;
                 }
    
                *nuevoLibro = libroAuxiliar;
                agregar_libro_a_tablas(nuevoLibro);
                printf("Libro agregado exitosamente.\n");

             break;
        }

    } while(opc != 7);
    return 0;
}


void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void temporal(void *dato) {
}

void imprimirLibroConSalto(void *dato) {
    printf("\n"); 
    imprimirLibro(dato);
}

int comparar_para_arbol(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->titulo, l2->titulo); 
}


int folding_isbn(void *dato) {
    Libro *l = (Libro*)dato;
    int suma = 0;
    char *str = l->isbn;
    while(*str) {
        if(isdigit(*str)) suma += (*str - '0'); 
        str++;
    }
    return suma;
}

int comparar_isbn(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->isbn, l2->isbn);
}

int folding_titulo(void *dato) {
    Libro *l = (Libro*)dato;
    int suma = 0;
    char *str = l->titulo;
    for(int i=0; str[i]; i++) suma += (int)str[i];
    return suma;
}

int comparar_titulo(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->titulo, l2->titulo);
}

int folding_autor(void *dato) {
    Libro *l = (Libro*)dato;
    int suma = 0;
    char *str = l->autor;
    for(int i=0; str[i]; i++) suma += (int)str[i];
    return suma;
}

int comparar_autor(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->autor, l2->autor);
}

int folding_anio(void *dato) { 
    Libro *l = (Libro*)dato;
    return l->fecha;
}

int comparar_anio(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return l1->fecha - l2->fecha;
}

int folding_inicial_titulo(void *dato) {
    Libro *l = (Libro*)dato;
    return (int)toupper(l->titulo[0]);
}

int comparar_inicial_titulo(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return toupper(l1->titulo[0]) - toupper(l2->titulo[0]);
}

int folding_inicial_autor(void *dato) {
    Libro *l = (Libro*)dato;
    return (int)toupper(l->autor[0]);
}

int comparar_inicial_autor(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return toupper(l1->autor[0]) - toupper(l2->autor[0]);
}

void inicializar_tabla() {
    int tam = 13; 
    ht_isbn = inicializarHashTable(tam, folding_isbn, imprimirLibro, comparar_isbn);
    ht_titulo = inicializarHashTable(tam, folding_titulo, imprimirLibro, comparar_titulo);
    ht_autor = inicializarHashTable(tam, folding_autor, imprimirLibro, comparar_autor);
    ht_anio = inicializarHashTable(tam, folding_anio, imprimirLibro, comparar_anio);
    ht_ini_tit = inicializarHashTable(tam, folding_inicial_titulo, imprimirLibro, comparar_inicial_titulo);
    ht_ini_aut = inicializarHashTable(tam, folding_inicial_autor, imprimirLibro, comparar_inicial_autor);
}

void agregar_libro_a_tablas(Libro *l) {
    insertarClave(&ht_isbn, l);
    insertarClave(&ht_titulo, l);
    insertarClave(&ht_autor, l);
    insertarClave(&ht_anio, l);
    insertarClave(&ht_ini_tit, l);
    insertarClave(&ht_ini_aut, l);
}

void eliminar_libro_de_tablas(Libro *l) {
    eliminarClave(&ht_isbn, l);
    eliminarClave(&ht_titulo, l);
    eliminarClave(&ht_autor, l);
    eliminarClave(&ht_anio, l);
    eliminarClave(&ht_ini_tit, l);
    eliminarClave(&ht_ini_aut, l);
}


void mostrar_resultados(Cola *c, int indice) {
    if(vaciaC(*c)) { 
        printf(" No se encontraron resultados.\n");
        return;
    }

    Arbol arbolOrdenador;
    arbolOrdenador.raiz = NULL;
    arbolOrdenador.cantidad = 0;
    arbolOrdenador.liberar = temporal; 
    arbolOrdenador.imprimir = imprimirLibroConSalto; 
    switch(indice) {
        case 1:
            arbolOrdenador.comparar = comparar_isbn;
            break;
        case 2: 
            arbolOrdenador.comparar = comparar_titulo;
            break;
        case 3:
            arbolOrdenador.comparar = comparar_autor;
            break;
        case 4:
            arbolOrdenador.comparar = comparar_anio;
            break;
        default:
            arbolOrdenador.comparar = comparar_titulo;
            break;
    }

    while(!vaciaC(*c)) {
        insertarArbol(&arbolOrdenador, dequeue(c));
    }

    printf("\nLibros \n");
    printf("%-18s  %-50s  %-30s  %s  %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
    imprimirOrden(arbolOrdenador, ORDEN); 
    
    liberarArbol(&arbolOrdenador);
}