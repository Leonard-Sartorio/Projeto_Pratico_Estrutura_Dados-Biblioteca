#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void pilha_inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

int pilha_push(Pilha *pilha, const char *acao) {
    NoPilha *novo = malloc(sizeof(NoPilha));

    if (novo == NULL) {
        return 0;
    }

    strncpy(novo->acao, acao, TAM_ACAO - 1);
    novo->acao[TAM_ACAO - 1] = '\0';

    novo->proximo = pilha->topo;
    pilha->topo = novo;

    return 1;
}

int pilha_pop(Pilha *pilha, char *acao) {
    NoPilha *temp;

    if (pilha->topo == NULL) {
        return 0;
    }

    temp = pilha->topo;

    if (acao != NULL) {
        strcpy(acao, temp->acao);
    }

    pilha->topo = temp->proximo;

    free(temp);

    return 1;
}

int pilha_peek(Pilha *pilha, char *acao) {
    if (pilha->topo == NULL) {
        return 0;
    }

    if (acao != NULL) {
        strcpy(acao, pilha->topo->acao);
    }

    return 1;
}

/* Exibe as cinco acoes mais recentes sem remover nenhuma */
void pilha_imprimir_ultimas(Pilha *pilha) {
    NoPilha *atual = pilha->topo;
    int quantidade = 0;

    if (atual == NULL) {
        printf("\nHistorico vazio.\n");
        return;
    }

    printf("\n===== ULTIMAS ACOES =====\n");

    while (atual != NULL && quantidade < 5) {
        printf("%d - %s\n", quantidade + 1, atual->acao);

        atual = atual->proximo;
        quantidade++;
    }
}

void pilha_liberar(Pilha *pilha) {
    NoPilha *atual = pilha->topo;

    while (atual != NULL) {
        NoPilha *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    pilha->topo = NULL;
}