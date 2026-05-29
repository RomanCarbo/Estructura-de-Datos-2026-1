#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../captura/captura.h"
#include "../Estructuras/heap/heap.h"

typedef struct {
    char* nombreDocumento;
    int numeroPaginas;
} ArchivoImpresion;

ArchivoImpresion* crearArchivo(int paginas, char* nombre);
void liberarArchivo(void* dato);
void imprimirArchivo(void* dato);
int compararArchivos(void* a, void* b);
void mostrarEstadoHeap(Heap heap);

int compararEntero(void*,void*);
void imprimirEntero(void*);
int main(void)
{
    srand(time(NULL));
	Heap heap = inicializarHeap(&imprimirArchivo, &compararArchivos, &liberarArchivo);
    int opc;

    do {
        mostrarEstadoHeap(heap);
		
		
		printf("\nCola de impresion\n");
		if (heap.tipo == MIN) {
			printf("Prioridad actual: Menor numero de paginas\n");
		} else {
			printf("Prioridad actual: Mayor numero de paginas\n");
		}
		printf("\n--- Menu ---\n");
		printf("\n[0] Cambiar prioridad");
		printf("\n[1] Mostrar cola de impresion");
		printf("\n[2] Agregar archivos");
		printf("\n[3] Imprimir archivos");
		printf("\n[4] Eliminar archivos especifico");
		printf("\n[5] Eliminar todos los archivos");
		printf("\n[6] Salir");
		printf("\nSelecciona una opcion:");
		scanf("%d", &opc);
        while(getchar() != '\n');

        switch (opc) {
            case 0: {
                if (heap.tipo == MIN) {
                    heap.tipo = MAX;
                    printf("\nNueva prioridad: Mayor numero de paginas");
                } else {
                    heap.tipo = MIN;
                    printf("\nNueva prioridad: Menor numero de paginas");
                }
                heapify(&heap);
                break;
            }

            case 1: {               
                mostrarEstadoHeap(heap);
                break;
            }

            case 2: {
                int paginas = (rand() % 1000) + 1;
                
                char* nombre[] = {
                    "Reporte_Mensual", "Tesis_Grado", "Examen_Estructuras", 
                    "Recibo_Luz", "Nomina_Empleados", "Manual_Usuario", 
                    "Contrato_Renta", "Factura_Compra", "Apuntes_Clase", 
                    "Proyecto_Final", "Presentacion_Ventas", "Balance_General", 
                    "Carta_Recomendacion", "Certificado_Medico", "Constancia_Estudios", 
                    "Curriculum_Vitae", "Minuta_Reunion", "Presupuesto_Anual", 
                    "Plano_Arquitectonico", "Guia_Instalacion", "Registro_Asistencia", 
                    "Informe_Laboratorio", "Inventario_Almacen", "Poliza_Seguro", 
                    "Receta_Medica", "Formulario_Inscripcion", "Lista_Precios", 
                    "Catalogo_Productos", "Memorandum_Interno", "Cierre_Contable"
                };
                int cantidad=sizeof(nombre)/sizeof(nombre[0]);
                int indiceElegido = rand() % cantidad;
                char nombreFinal[100];
                sprintf(nombreFinal, "%s_%d", nombre[indiceElegido], rand() % 1000);
                printf("Nombre: ", nombre);
                printf("Numero de Paginas: ", paginas);

                if (nombre[indiceElegido] && paginas > 0) {
                    ArchivoImpresion* nuevo = crearArchivo(paginas, nombre[indiceElegido]);
                    insertarHeap(&heap, nuevo);
                    printf("\nArchivo agregado");
                } else {
                    printf("\nError, datos invalidos");
                }
                
                
                break;
            }

            case 3: {
                ArchivoImpresion* archivo = (ArchivoImpresion*)quitarHeap(&heap);
                
                if (archivo) {
                    imprimirArchivo(archivo);
                    liberarArchivo(archivo);
                } else {
                    printf("\nLa cola de impresion esta vacia");
                }
                break;
            }

            case 4: {
                if (heap.cantidad == 0) {
                    printf("\nNo hay archivos para eliminar");
                    break;
                }
                
                printf("\nSeleccione el archivo a eliminar: \n");
                for (int i = 0; i < heap.cantidad; i++) {
                    printf("[%d] ", i);
                    imprimirArchivo(heap.arr[i]->dato);
                    printf("\n");
                }

                int index = -1;
                inputEntero("Indice del archivo a eliminar: ", &index);

                if (index < 0 || index >= heap.cantidad) {
                    printf("\nIndice invalido");
                } else {
                    ArchivoImpresion* eliminado = (ArchivoImpresion*)eliminarElementoHeap(&heap, index);
                    if (eliminado) {
                        printf("\nArchivo eliminado: ");
                        imprimirArchivo(eliminado);
                        printf("\n");
                        liberarArchivo(eliminado);
                    }
                }
                break;
            }

            case 5: {
                vaciarHeap(&heap, &liberarArchivo);
                printf("\nSe han eliminado todos los archivos de la cola");
                break;
            }

            case 6: {
                vaciarHeap(&heap, &liberarArchivo);
                printf("\nFinalizando programa...");
                break;
            }

            default:
                printf("\nOpcion invalida");
                break;
        }

    } while (opc != 6);
	
	
	return 0;
}


void imprimirEntero(void *a)
{
	int *aa=a;
	printf(" %d",*aa);
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

ArchivoImpresion* crearArchivo(int paginas, char* nombre) {
    ArchivoImpresion* nuevo = (ArchivoImpresion*)malloc(sizeof(ArchivoImpresion));
    if (!nuevo) return NULL;

    nuevo->numeroPaginas = paginas;
    nuevo->nombreDocumento = cadenaDinamica(nombre);
    
    return nuevo;
}

void liberarArchivo(void* dato) {
    if (!dato) return;
    ArchivoImpresion* archivo = (ArchivoImpresion*)dato;
    free(archivo->nombreDocumento);
    free(archivo);
}


void imprimirArchivo(void* dato) {
    if (!dato) return;
    ArchivoImpresion* archivo = (ArchivoImpresion*)dato;
    printf("[Pag: %-4d, Nombre: %s]", archivo->numeroPaginas, archivo->nombreDocumento);
}


int compararArchivos(void* a, void* b) {
    ArchivoImpresion* archA = (ArchivoImpresion*)a;
    ArchivoImpresion* archB = (ArchivoImpresion*)b;

    if (archA->numeroPaginas == archB->numeroPaginas) return 0;
    if (archA->numeroPaginas < archB->numeroPaginas) return -1;
    return 1;
}


void mostrarEstadoHeap(Heap heap) {
    printf("\n--- COLA DE IMPRESION ---\n");
    
    int limite = (heap.cantidad < 5) ? heap.cantidad : 5;
    if (limite == 0) {
        printf("\n[Cola vacia]");
    } else {
        for (int i = 0; i < limite; i++) {
            printf("  %d. ", i + 1);
            imprimirArchivo(heap.arr[i]->dato);
            printf("\n");
        }
    }
    printf("\n");

    printf("\nArreglo:");
    if (heap.cantidad == 0) {
        printf("\n\n[Vacio]\n");
    } else {
        imprimirHeap(heap);
        printf("\n");
    }

    printf("\nArbol:");
    if (heap.cantidad == 0) {
        printf("\n\n[Vacio]\n");
    } else {
        imprimirArbol(heap.arbol);
        printf("\n\n");
    }
}