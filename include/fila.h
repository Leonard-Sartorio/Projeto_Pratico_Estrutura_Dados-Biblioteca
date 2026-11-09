#ifndef FILA_H
#define FILA_H

#include "livro.h"

typedef struct NoFila {
    Livro livro;
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

void fila_inicializar(Fila *fila);
int fila_enfileirar(Fila *fila, Livro livro);
int fila_desenfileirar(Fila *fila, Livro *livro);
void fila_imprimir(Fila *fila);
void fila_liberar(Fila *fila);

#endif