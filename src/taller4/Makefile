cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ../src/Estructuras/heap
libs = ../../lib -lCaptura -lHeap
source = $(wildcard *.c)
output = ../../bin/taller4

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
