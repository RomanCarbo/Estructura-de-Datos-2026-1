#include "listadoble.h"
#include <stdio.h>
#include "../../practica2/alumnos.h"

ListaD inicializarListaD(void)
{
	return (ListaD) {NULL,NULL,0,NULL,NULL,NULL};
}

void mostrarListaA(ListaD lista)
{
	NodoD *p; //es un apuntador de tipo nodo
	printf("\n Lista[%d]: \n",lista.cant);
	for( p = lista.inicio ;  p!=NULL ; p = p->sig  )
	{
		printf(" ");
		lista.imprimir(p->dato);
		printf("->");
	}
	printf("NULL");
}
void mostrarListaD(ListaD lista)
{
	NodoD *p; //es un apuntador de tipo nodo
	printf("\n Lista[%d]: ",lista.cant);
	for( p = lista.fin ;  p!=NULL ; p = p->ant  )
	{
		printf(" ");
		lista.imprimir(p->dato);
		printf("->");
	}
	printf("NULL");
}


void insertarOrdenado(ListaD *lista, void *dato)
{
    NodoD *nuevo = crearNodoD(dato);
    
    if (lista->inicio == NULL) {
        lista->inicio = nuevo;
        lista->fin = nuevo;
        lista->cant++;
        return; 
    }

    NodoD *actual;
    for (actual = lista->inicio; actual != NULL; actual = actual->sig) {
        if (lista->comparar(dato, actual->dato) == -1) {
            if (actual->ant == NULL) {
                nuevo->sig = actual;
                actual->ant = nuevo;
                lista->inicio = nuevo;
            } 

            else {
                nuevo->sig = actual;
                nuevo->ant = actual->ant;
                actual->ant->sig = nuevo;
                actual->ant = nuevo;
            }
            lista->cant++;
            return; 
        }
    }
    
    lista->fin->sig = nuevo;
    nuevo->ant = lista->fin;
    lista->fin = nuevo;
    lista->cant++;
}	


void reordenar(ListaD *listaOrigen, int (*comparar)(void*, void*))
 {
    ListaD aux;
    aux.inicio = NULL;
	aux.fin = NULL;
    aux.comparar = comparar;
    aux.imprimir = listaOrigen->imprimir;
    aux.cant = 0;

    NodoD *actual =listaOrigen->inicio;
    while(actual !=NULL) 
	{
        NodoD *siguiente = actual->sig;
        Alumno *copia_alumno = (Alumno*)malloc(sizeof(Alumno)); //reservo para un alumno sin nada
        if (copia_alumno !=NULL) {
            *copia_alumno = *((Alumno*)actual->dato);
            insertarOrdenado(&aux, copia_alumno);
        }

        
        eliminarEnPosicion(listaOrigen, 0); //aqui elimino el actual y por eso USO UNA COPIA
        
        actual = siguiente; //actualizo el actual con el nodo siguiente
    }
    
    listaOrigen->inicio = aux.inicio;
    listaOrigen->cant = aux.cant;
    listaOrigen->comparar = comparar;
	listaOrigen->fin = aux.fin;

}



void eliminarEnPosicion(ListaD *lista,int pos)
{		
	//VALIDAR
	if( pos==0 ||(pos > 0  && pos < lista->cant ))
	{			
		NodoD *anterior ,*actual; //inicializamos los punteros nomas
		anterior = NULL;
		actual = lista->inicio; //el puntero actual apunta al inicio de la lista original
		for (int i=0; i<lista->cant  ; i++) //busca recorrer cada nodo de la lista
		// y pone < por que i empieza en 0, pero bien podria ser 1 y ser <= pero bueno
		{
			if( i==pos) //posicion localizada
			{
				if(anterior == NULL)
				{
					//esto sifnifica que estamos al inicio de la lista
					lista->inicio = actual->sig; //ponemos el inicio en el siguiente nodo
				if(actual->sig!=NULL) //Esto significa que hay un nodo 
					{
						actual->sig->ant = anterior;  //daria error si no hicieramos el if
						//porque ->sig seria null y no nodo
					}
				}
				else
				{
					anterior->sig = actual->sig; //el nodo anterior ahora apunta al siguiente
					if(actual->sig != NULL)
					{
						actual->sig->ant= anterior;
					}
				}
				    if(actual->sig == NULL) {						// borramos el último nodo
					lista->fin = anterior;
					}
			}

				free(actual->dato);
				free(actual); //se borra el actual
				lista->cant--;  //se baja cantidad
				break; //se hace porque ya borramos el nodo
			}
			anterior = actual; //anterior apunta al nodo actual
			actual = actual->sig;  //actual apunta al nodo siguiente
		}			
	}	


void* buscarDato(ListaD lista,void *dato)
{
	NodoD *actual=NULL;
	for( actual = lista.inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if( lista.comparar(dato,actual->dato) == 0) //si encuentra el alumno
		{
			return actual->dato; //retorna el dato, que es el alumno
		}
		
	}	
	return NULL; 
	
}

void borrarDato(ListaD *lista,void* dato)
{
	
	NodoD *actual,*anterior = NULL;
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if(lista->comparar(dato,actual->dato) == 0)
		{
			if(anterior != NULL)
			{
					anterior->sig = actual->sig;
				if(actual->sig != NULL)
				{
				actual->sig->ant = anterior;
				} 
			}
				else
				{
					lista->inicio = actual->sig;
					if(actual->sig != NULL)
					{
						actual->sig->ant = NULL;
					}
				}

			if(actual->sig == NULL) 
			{  //actualiza fin
			lista->fin = anterior;
			}
			//free(actual->dato);
			free(actual);
			lista->cant--;
			break;			
		}		
		anterior = actual;
	}	
}

