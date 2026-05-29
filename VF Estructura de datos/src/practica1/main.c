#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

typedef struct {
    unsigned int matricula;
    char nombre[64];
    int semestres;
    float promedio;
} Alumno;

void* crearAlumno(unsigned int matricula, const char *nombre, int semestres, float promedio);
void imprimirAlumno(void *a);
int cmpMatricula(void *a, void *b);
int cmpNombre(void *a, void *b);
int cmpSemestres(void *a, void *b);
int cmpPromedio(void *a, void *b);

int main(void) {
    Lista lista;
    lista.inicio = NULL;
    lista.cant = 0;
    lista.imprimir = &imprimirAlumno;
    
    int (*orden_actual)(void*, void*) = &cmpMatricula; 
    lista.comparar = orden_actual; 

    int opcion;
    do {
        printf("\n----- Menu de alumnos -----\n");
        printf("[1] Registrar Alumno\n");
        printf("[2] Desplegar Alumnos\n");
        printf("[3] Reordenar\n");
        printf("[4] Buscar Alumno\n");
        printf("[5] Borrar Alumno\n");
        printf("[6] Salir del programa\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: {
                unsigned int mat;
                char nombre[64];
                int sem;
                float prom;
                
                printf("Nombre: ");
                scanf(" %[^\n]", nombre);
                printf("Matricula: "); 
                scanf("%u", &mat);
                printf("Semestres: "); 
                scanf("%d", &sem);
                printf("Promedio: "); 
                scanf("%f", &prom);
                
                Alumno tmp;
                tmp.matricula = mat;
                
                lista.comparar = &cmpMatricula; 
                
                if (buscarDato(lista, &tmp) != NULL) {
                    printf("La Matricula ya existe.\n");
                } else {

                    lista.comparar = orden_actual;
                    insertarOrdenado(&lista.inicio, crearAlumno(mat, nombre, sem, prom), lista.comparar);
                    lista.cant++;
                    printf("Alumno registrado correctamente.\n");
                }
                break;
            }

            case 2:
                mostrarLista(lista);
                break;

            case 3: {
                int op;
                printf("Reordenar por: \n[1] Matricula \n[2] Nombre \n[3] Semestre \n[4] Promedio\n");
                scanf("%d", &op);

                switch(op) {
                    case 1: 
                        orden_actual = &cmpMatricula;
                    break;
                    case 2:
                        orden_actual = &cmpNombre;
                        break;
                    case 3: 
                        orden_actual = &cmpSemestres; 
                        break;
                    case 4: 
                        orden_actual = &cmpPromedio; 
                        break;
                    default: 
                        printf("Opcion invalida.\n");
                        break;
                }
                
                lista.comparar = orden_actual;

                Lista aux;
                aux.inicio = NULL; 
                aux.cant = 0;
                aux.imprimir = lista.imprimir;
                aux.comparar = lista.comparar;

                for (Nodo *p = lista.inicio; p; p = p->sig) {
                    insertarOrdenado(&aux.inicio, p->dato, lista.comparar);
                    aux.cant++;
                }
                
                lista = aux;
                printf("Lista reordenada.\n");
                break;
            }

            case 4: {
                int crit;
                printf("Buscar por: \n[1] Matricula \n[2] Nombre \n[3] Semestre \n[4] Promedio\n");
                scanf("%d", &crit);

                Alumno tmp;
                switch(crit) {
                    case 1:
                        printf("Matricula: "); 
                        scanf("%u", &tmp.matricula);
                        lista.comparar = &cmpMatricula;
                        break;
                    case 2:
                        printf("Nombre: "); 
                        scanf(" %[^\n]", tmp.nombre);
                        lista.comparar = &cmpNombre;
                        break;
                    case 3:
                        printf("Semestres: ");
                        scanf("%d", &tmp.semestres);
                        lista.comparar = &cmpSemestres;
                        break;
                    case 4:
                        printf("Promedio: "); 
                        scanf("%f", &tmp.promedio);
                        lista.comparar = &cmpPromedio;
                        break;
                    default:
                        printf("Criterio invalido.\n");
                        break;
                }

                void* encontrado = buscarDato(lista, &tmp);
                if (encontrado) 
                    imprimirAlumno(encontrado);
                    
                else printf("Alumno no encontrado.\n");
                break;
            }

            case 5: {
                Alumno tmp;
                unsigned int mat;
                printf("Matricula del Alumno a borrar: "); 
                scanf("%u", &mat);
                tmp.matricula = mat;
                lista.comparar = &cmpMatricula;
                borrarDato(&lista, &tmp);
                printf("Alumno borrado.\n");
                break;
            }

            case 6:
                printf("Fin del programa.\n");
                borrarLista(&lista);
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 6);

    return 0;
}

void* crearAlumno(unsigned int matricula, const char *nombre, int semestres, float promedio) {
    Alumno *nuevo = malloc(sizeof(Alumno));
    nuevo->matricula = matricula;
    strcpy(nuevo->nombre, nombre);
    nuevo->semestres = semestres;
    nuevo->promedio = promedio;
    return nuevo;
}

void imprimirAlumno(void *a) {
    Alumno *al = (Alumno*)a;
    printf("\nNombre: %s -> Matricula: %u -> Semestres: %d -> Prom: %.2f", al->nombre,al->matricula, al->semestres, al->promedio);
}

int cmpMatricula(void *a, void *b) {
    Alumno *alu1 = (Alumno*)a, *alu2 = (Alumno*)b;
    if (alu1->matricula < alu2->matricula) 
        return -1;
    if (alu1->matricula > alu2->matricula) 
        return 1;
    return 0;
}

int cmpNombre(void *a, void *b) {
    return strcmp(((Alumno*)a)->nombre, ((Alumno*)b)->nombre);
}

int cmpSemestres(void *a, void *b) {
    return ((Alumno*)a)->semestres - ((Alumno*)b)->semestres;
}

int cmpPromedio(void *a, void *b) {
    Alumno *al1 = (Alumno*)a, *al2 = (Alumno*)b;
    if (al1->promedio < al2->promedio) return -1;
    if (al1->promedio > al2->promedio) return 1;
    return 0;
}