#ifndef ALUMNO_H
#define ALUMNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estructuras/listadoble/listadoble.h"

// Definición de la estructura Alumno
typedef struct
{
    unsigned int matricula;
    char nombre[64];
    int semestres;
    float promedio;
} Alumno;

// Función para crear un Alumno desde teclado
Alumno* registrarAlumno(ListaD* lista);

// Función auxiliar para crear un Alumno a partir de una variable Alumno
void* crearAlumno(Alumno a);

// Funciones de comparación
int compararAlumnosA(void *a, void *b); // Ascendente por nombre
int compararAlumnosD(void *a, void *b); // Descendente por nombre

int compararPromedioA(void *a, void *b); // Ascendente por promedio
int compararPromedioD(void *a, void *b); // Descendente por promedio

int compararMatriculaA(void *a, void *b); // Ascendente por matrícula
int compararMatriculaD(void *a, void *b); // Descendente por matrícula

int compararSemestresA(void *a, void *b); // Ascendente por semestres
int compararSemestresD(void *a, void *b); // Descendente por semestres

// Función para imprimir un Alumno
void imprimirAlumno(void *a);

#endif