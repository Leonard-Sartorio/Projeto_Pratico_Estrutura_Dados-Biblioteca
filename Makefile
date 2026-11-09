
CC = gcc

# Compilador e flags de otimização/avisos e erros.
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC = src/main.c \
      src/livro.c \
      src/lista.c \
      src/arvore.c \
      src/pilha.c \
      src/fila.c \
      src/ordenacao.c

TARGET = biblioteca

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
