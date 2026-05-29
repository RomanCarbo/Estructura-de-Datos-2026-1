# --- Variabes ---
CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 -g

# --- Archivos de esta carpeta ---
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# --- Archivos externos (Nodos) ---
# Le indicamos dónde está el código fuente del nodo
NODO_SRC = ../nodos/nodo.c
# Así se llamará una vez compilado
NODO_OBJ = nodo.o

# Nombre del ejecutable
TARGET = practica1

# --- Reglas ---
all: $(TARGET)

# Unimos los objetos locales y el objeto del nodo para crear el ejecutable
$(TARGET): $(OBJS) $(NODO_OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(NODO_OBJ)
	@echo "¡Compilacion exitosa!"

# Regla especial para compilar el nodo.c que está en otra carpeta
$(NODO_OBJ): $(NODO_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla genérica para los .c locales
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpieza general
clean:
	rm -f *.o $(TARGET)