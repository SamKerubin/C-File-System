# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = filesystem

# Regla principal
all: $(EXEC)

# Cómo construir el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Limpieza de archivos
clean:
	rm -f $(OBJ) $(EXEC)

# Recompilar desde cero
rebuild: clean all

# Para que make no confunda los .h con comandos
.PHONY: all clean rebuild