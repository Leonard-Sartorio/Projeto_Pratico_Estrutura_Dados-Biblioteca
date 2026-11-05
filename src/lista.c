
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void lista_inicializar(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

int lista_inserir_fim(Lista *lista, int id) {
    NoLista *novo = malloc(sizeof(NoLista));

    if (novo == NULL)
        return 0;

    novo->id = id;
    novo->proximo = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        lista->fim->proximo = novo;
    }

    lista->fim = novo;
    return 1;
}

void lista_imprimir(Lista *lista) {
    NoLista *atual = lista->inicio;

    while (atual != NULL) {
        printf("%d", atual->id);

        if (atual->proximo != NULL)
            printf(" -> ");

        atual = atual->proximo;
    }

    printf("\n");
}

void lista_liberar(Lista *lista) {
    NoLista *atual = lista->inicio;

    while (atual != NULL) {
        NoLista *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}
