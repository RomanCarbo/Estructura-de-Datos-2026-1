#include "alumnos.h"
#include <stdio.h>
#include "../Estructuras/listadoble/listadoble.h" 


Alumno* registrarAlumno(ListaD *lista)
{

Alumno *nuevo = malloc(sizeof(Alumno));
printf("\nIngresa el nombre del alumnno: "); 
fgets(nuevo->nombre,64,stdin);
						int i=0;
						while(nuevo->nombre[i]!= '\0')
						{
							if (nuevo->nombre[i]== '\n') 
							{
								nuevo->nombre[i]='\0';
								break;
							}
							i++;
						}

   int matricula;
do {
        matricula = 0;
        printf("\nIngresa la matricula: ");
        scanf("%u", &nuevo->matricula);
        while(getchar() != '\n');
        
        NodoD *actual;
        for(actual = lista->inicio; actual != NULL; actual = actual->sig)
        {
            Alumno *Alumnoa = (Alumno*)actual->dato;
            if(Alumnoa->matricula == nuevo->matricula)
            {
                printf("La matricula ya existe, ingresa otra\n");
                matricula = 1;
                break;
            }
        }
    } while(matricula);
printf("\nIngresa el semestre del alumno: ");
scanf("%d", &nuevo->semestres);

printf("\nIngresa el promedio del alumno: ");
scanf("%f", &nuevo->promedio);

return nuevo;
	
}

int compararAlumnosA(void *a, void *b)
{
    Alumno *aa = a, *ab = b;
    return strcmp(aa->nombre, ab->nombre);
	
}
int compararAlumnosD(void *a, void *b)
{
    Alumno *aa = a, *ab = b;
    return strcmp(ab->nombre,aa->nombre); 
}


int compararPromedioA(void *a, void *b)
{
    Alumno *ea = a, *eb = b;
    if(ea->promedio < eb->promedio) return -1;
    else if(ea->promedio > eb->promedio) return 1;
    else return 0;
}

int compararPromedioD(void *a, void *b)
{
    Alumno *ea = a, *eb = b;
    if(ea->promedio < eb->promedio) return 1;
    else if(ea->promedio > eb->promedio) return -1;
    else return 0;
}

int compararMatriculaA(void *a, void *b)
{
	Alumno *ea = a, *eb = b;
    if(ea->matricula < eb->matricula) return -1;
    else if(ea->matricula > eb->matricula) return 1;
    else return 0;
}

int compararMatriculaD(void *a, void *b)
{
	Alumno *ea = a, *eb = b;
    if(ea->matricula < eb->matricula) return 1;
    else if(ea->matricula > eb->matricula) return -1;
    else return 0;
}

int compararSemestresA(void *a, void *b)
{
	Alumno *ea = a, *eb = b;
    if(ea->semestres < eb->semestres) return -1;
    else if(ea->semestres > eb->semestres) return 1;
    else return 0;
}

int compararSemestresD(void *a, void *b)
{
	Alumno *ea = a, *eb = b;
    if(ea->semestres < eb->semestres) return 1;
    else if(ea->semestres > eb->semestres) return -1;
    else return 0;
}



void* crearAlumno(Alumno a)   //AUXILIAR
{
    Alumno *nuevo = malloc(sizeof(Alumno));
    *nuevo = a;
    return nuevo;
}

void imprimirAlumno(void *a)
{
    Alumno *aa = a;
    printf("Nombre:%s Matricula:%u Semestre:%d Promedio:%.2f\n", aa->nombre, aa->matricula, aa->semestres, aa->promedio);
}
