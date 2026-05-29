cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/Estructuras/pila -I ../src/captura -I ..src/Estructuras/arbol
libs = ../../lib -lPila -lCaptura -lArbol
source = $(wildcard *.c) 
output = ../../bin/practica7

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
