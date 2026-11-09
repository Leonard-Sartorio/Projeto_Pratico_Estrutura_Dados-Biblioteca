#ifndef ARVORE_H
#define ARVORE_H

#include "livro.h"

typedef struct NoArvore {
    Livro livro;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct {
    NoArvore *raiz;
} Arvore;

void arvore_inicializar(Arvore *arvore);

int arvore_inserir(Arvore *arvore, Livro livro);

Livro *arvore_buscar(Arvore *arvore, int id);

int arvore_remover(Arvore *arvore, int id);

void arvore_listar_em_ordem(Arvore *arvore);

Livro *arvore_menor_id(Arvore *arvore);

Livro *arvore_maior_id(Arvore *arvore);

void arvore_liberar(Arvore *arvore);

#endif