cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ../src/Estructuras/arbol -I ..src/Estructuras/heap
libs = ../../lib -lCaptura -lArbol -lHeap
source = $(wildcard *.c) 
output = ../../bin/practica8

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
