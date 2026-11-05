
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void lista_inicializar(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

int lista_inserir_fim(Lista *lista, Livro livro) {
    NoLista *novo = malloc(sizeof(NoLista));

    if (novo == NULL) {
        return 0;
    }

    novo->livro = livro;
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

    if (atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("\nID: %d\n", atual->livro.id);
        printf("Titulo: %s\n", atual->livro.titulo);
        printf("Autor: %s\n", atual->livro.autor);
        printf("Ano: %d\n", atual->livro.ano);

        atual = atual->proximo;
    }
}

int lista_remover_id(Lista *lista, int id) {
    NoLista *atual = lista->inicio;
    NoLista *anterior = NULL;

    while (atual != NULL) {
        if (atual->livro.id == id) {

            if (anterior == NULL) {
                lista->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            if (atual == lista->fim) {
                lista->fim = anterior;
            }

            free(atual);
            return 1;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return 0;
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
