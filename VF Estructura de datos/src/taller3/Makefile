# ==========================================
# Makefile Optimizado - Taller 3 UABC
# ==========================================

cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g

# CORRECCIÓN DE RUTAS: 
# Desde 'src/taller3', para ir a 'src/captura' solo subes un nivel '../'
includes = -I ../captura -I ../Estructuras/arbol

lib_path = ../../lib
libs = -lCaptura -lArbol

source = $(wildcard *.c) 
output = ../../bin/taller3.exe

# Regla principal
build:
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(lib_path) $(libs)
	@echo "¡Taller 3 Compilado Exitosamente!"

# Regla Rebuild (Ajustada para que encuentre las carpetas desde taller3)
rebuild:
	make -C ../captura
	make -C ../Estructuras/arbol
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(lib_path) $(libs)
	@echo "Reconstruccion y Compilacion Exitosa!!!"

run:
	$(output)

clean:
	del /f ..\..\bin\taller3.exe