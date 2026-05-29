cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ../src/Estructuras/pila

lib_path = -L ../../lib
libs = -lPila -lCaptura

source = $(wildcard *.c) 
output = ../../bin/taller2

build :
	gcc $(cflags) $(source) -o $(output) $(includes) $(lib_path) $(libs)
	@echo "Compilo Exitosamente!!!"