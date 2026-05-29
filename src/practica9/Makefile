cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ..src/Estructuras/heap -I ..src/Estructuras/hash -I ..src/Estructuras/cola
libs = ../../lib -lCaptura -lHeap -lHashTable -lCola
source = $(wildcard *.c) 
output = ../../bin/practica9

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
