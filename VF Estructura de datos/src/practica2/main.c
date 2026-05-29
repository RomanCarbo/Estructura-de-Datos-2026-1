#include <stdio.h>
#include "../Estructuras/listadoble/listadoble.h"
#include "../captura/captura.h"
#include "alumnos.h"

#define LONGITUD 50

int main(void)
{
    ListaD lista;
    lista = inicializarListaD();
    lista.imprimir = &imprimirAlumno;
    
    int (*orden_actual)(void*, void*) = &compararAlumnosA;
    lista.comparar = orden_actual;
    
    int opc;

    do {
        printf("\n--- MENU ---");
        printf("\n[1] Registrar Alumno");
        printf("\n[2] Desplegar Alumnos");
        printf("\n[3] Reordenar");
        printf("\n[4] Buscar Alumno");
        printf("\n[5] Borrar Alumno");
        printf("\n[6] Salir");
        printf("\nElige una opcion: ");
        scanf("%d", &opc);
        if (opc<1 || opc>6){ 
            opc = -1;
        }
        while (getchar() != '\n'); 

        switch (opc) 
        {
            case 1: 
            {
                lista.comparar = orden_actual; 
                Alumno *nuevo = registrarAlumno(&lista);
                insertarOrdenado(&lista, nuevo); 
            }
            break;

            case 2:
            {
                int opc5;
                printf("\n--- Desplegar Alumnos ---");
                printf("\n[1] Ascendente");
                printf("\n[2] Descendente");
                printf("\nElige una opcion: ");
                scanf("%d", &opc5);
                while (getchar() != '\n');
                
                switch(opc5)
                {
                    case 1:
                        mostrarListaA(lista);
                    break;
                    case 2:
                        mostrarListaD(lista);
                    break;
                    default:
                        printf("\nOpcion invalida.\n");
                    break;
                }
            }
            break;

            case 3:
            {
                int opc1 = 0;
                
                printf("\n--- Reordenar ---");
                printf("\n[1] Nombre");
                printf("\n[2] Matricula");
                printf("\n[3] Promedio");
                printf("\n[4] Semestre");
                printf("\n[5] Salir");
                printf("\nElige la opcion: ");
                scanf("%d", &opc1);
                if (opc1 < 1 || opc1 > 5){
                    opc1 = -1;
                }
                while (getchar() != '\n'); 

                switch (opc1)
                {
                    case 1:
                    { //por nombre
                        int orden;
                        printf("\n[1] Ascendente");
                        printf("\n[2] Descendente");
                        printf("\nElige el orden: ");
                        scanf("%d", &orden);
                        while (getchar() != '\n'); 

                        switch (orden) 
                        {
                            case 1:
                                orden_actual = &compararAlumnosA; 
                                reordenar(&lista, orden_actual);
                            break;
                            case 2:
                                orden_actual = &compararAlumnosD; 
                                reordenar(&lista, orden_actual);
                            break;
                            default:
                                printf("\nOpción inválida.");
                            break;
                        }
                    }
                    break;

                    case 2: 
                    { //ordenar por matricula
                        int orden;
                        printf("\n[1] Ascendente");
                        printf("\n[2] Descendente");
                        printf("\nElige el orden: ");
                        scanf("%d", &orden);
                        while (getchar() != '\n'); 

                        switch (orden)
                        {
                            case 1:
                                orden_actual = &compararMatriculaA; 
                                reordenar(&lista, orden_actual);
                            break;
                            case 2:
                                orden_actual = &compararMatriculaD; 
                                reordenar(&lista, orden_actual);
                            break;
                            default:
                                printf("\nOpción inválida.");
                            break;
                        }
                    }
                    break;

                    case 3: 
                    { //ordenar por promedio
                        int orden;
                        printf("\n[1] Ascendente");
                        printf("\n[2] Descendente");
                        printf("\nElige el orden: ");
                        scanf("%d", &orden);
                        while (getchar() != '\n'); 

                        switch (orden)
                        {
                            case 1:
                                orden_actual = &compararPromedioA; 
                                reordenar(&lista, orden_actual);
                            break;
                            case 2:
                                orden_actual = &compararPromedioD; 
                                reordenar(&lista, orden_actual);
                            break;
                            default:
                                printf("\nOpcion incorrecta");
                            break;
                        }
                    }
                    break;

                    case 4:
                    { //por semestre
                        int orden;
                        printf("\n[1] Ascendente");
                        printf("\n[2] Descendente");
                        printf("\nElige el orden: ");
                        scanf("%d", &orden);
                        while (getchar() != '\n'); 

                        switch (orden) 
                        {
                            case 1:
                                orden_actual = &compararSemestresA; 
                                reordenar(&lista, orden_actual);
                            break;
                            case 2:
                                orden_actual = &compararSemestresD; 
                                reordenar(&lista, orden_actual);
                            break;
                            default:
                                printf("\nOpción inválida.");
                            break;
                        }
                    }
                    break;

                    case 5:
                        printf("\nCancelando reordenamiento...");
                        break;

                    default:
                        printf("\nOpcion incorrecta");
                        break;
                }
            }
            break;

            case 4: 
            {   
                int opc2 = 0;
                void *buscado = NULL;
                
                printf("\n--- Buscar Alumno ---");
                printf("\n[1] Nombre");
                printf("\n[2] Matricula");
                printf("\n[3] Promedio");
                printf("\n[4] Semestre");
                printf("\n[5] Salir");
                printf("\nElige el criterio de busqueda: ");
                scanf("%d", &opc2);
                if (opc2 < 1 || opc2 > 5){ 
                    opc2 = -1;
                }
                while (getchar() != '\n'); 
                
                switch(opc2)
                {
                    case 1:
                    {
                        lista.comparar = compararAlumnosA;
                        Alumno aux;
                        printf("\nQue alumno quieres buscar (Nombre): ");
                        fgets(aux.nombre, 64, stdin);
                        int i = 0;
                        while(aux.nombre[i] != '\0')
                        {
                            if (aux.nombre[i] == '\n') 
                            {
                                aux.nombre[i] = '\0';
                                break;
                            }
                            i++;
                        }
                        buscado = crearAlumno(aux);
                    }   
                    break;
                    case 2:
                    {
                        lista.comparar = compararMatriculaA;
                        Alumno aux;
                        printf("\nMatricula del alumno a buscar: ");
                        scanf("%u", &aux.matricula);
                        getchar();
                        buscado = crearAlumno(aux);
                    }
                    break;
                    case 3:
                    {
                        lista.comparar = compararPromedioA;
                        Alumno aux;
                        printf("\nPromedio del alumno a buscar: ");
                        scanf("%f", &aux.promedio);
                        getchar();
                        buscado = crearAlumno(aux);
                    }
                    break;
                    case 4:
                    {
                        lista.comparar = compararSemestresA;
                        Alumno aux;
                        printf("\nSemestre del alumno a buscar: ");
                        scanf("%d", &aux.semestres);
                        getchar();
                        buscado = crearAlumno(aux);
                    }
                    break;
                    case 5:
                        printf("\nSaliendo de busqueda...");
                    break;
                    default:
                        printf("\nOpcion invalida");
                    break;
                }
                
                if (buscado != NULL) {
                    void *encontrado = buscarDato(lista, buscado);
                    if(encontrado != NULL)
                    {
                        printf("\nAlumno encontrado:\n");
                        imprimirAlumno(encontrado);
                    }
                    else{
                        printf("\nAlumno no encontrado.\n");
                    }
                    free(buscado);
                }
            }
            break;

            case 5: 
            {
                printf("\n--- Borrar Alumno ---");
                Alumno aux;
                printf("\nMatricula del alumno a borrar: ");
                scanf("%u", &aux.matricula);
                getchar();
                void* buscado = crearAlumno(aux);
                
                lista.comparar = compararMatriculaA;
                borrarDato(&lista, buscado);
                free(buscado);
                printf("\nAlumno borrado.\n");
            }
            break;

            case 6:
                printf("\nFinalizando programa.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    } while (opc != 6);

    return 0;
}