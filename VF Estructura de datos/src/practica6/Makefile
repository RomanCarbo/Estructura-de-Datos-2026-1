cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/Estructuras/pila -I ../src/captura
libs = ../../lib -lPila -lCaptura
source = $(wildcard *.c) 
output = ../../bin/practica6

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
