#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void fila_inicializar(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int fila_enfileirar(Fila *fila, Livro livro) {
    NoFila *novo = malloc(sizeof(NoFila));

    if (novo == NULL) {
        return 0;
    }

    novo->livro = livro;
    novo->proximo = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novo;
    } else {
        fila->fim->proximo = novo;
    }

    fila->fim = novo;

    return 1;
}

int fila_desenfileirar(Fila *fila, Livro *livro) {
    NoFila *temp;

    if (fila->inicio == NULL) {
        return 0;
    }

    temp = fila->inicio;

    if (livro != NULL) {
        *livro = temp->livro;
    }

    fila->inicio = temp->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);

    return 1;
}

void fila_imprimir(Fila *fila) {
    NoFila *atual = fila->inicio;

    if (atual == NULL) {
        printf("\nFila vazia.\n");
        return;
    }

    printf("\n===== FILA DE ATENDIMENTO =====\n");

    while (atual != NULL) {
        printf("\nID: %d\n", atual->livro.id);
        printf("Titulo: %s\n", atual->livro.titulo);

        atual = atual->proximo;
    }
}

void fila_liberar(Fila *fila) {
    NoFila *atual = fila->inicio;

    while (atual != NULL) {
        NoFila *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    fila->inicio = NULL;
    fila->fim = NULL;
}