#ifndef LISTA_H
#define LISTA_H

#include "livro.h"

typedef struct NoLista {
    Livro livro;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *inicio;
    NoLista *fim;
} Lista;

void lista_inicializar(Lista *lista);
int lista_inserir_fim(Lista *lista, Livro livro);
int lista_remover_id(Lista *lista, int id);
void lista_imprimir(Lista *lista);
void lista_liberar(Lista *lista);

#endif