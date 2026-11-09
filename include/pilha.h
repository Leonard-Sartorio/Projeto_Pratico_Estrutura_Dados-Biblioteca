#ifndef PILHA_H
#define PILHA_H

#define TAM_ACAO 120

typedef struct NoPilha {
    char acao[TAM_ACAO];
    struct NoPilha *proximo;
} NoPilha;

typedef struct {
    NoPilha *topo;
} Pilha;

void pilha_inicializar(Pilha *pilha);
int pilha_push(Pilha *pilha, const char *acao);
int pilha_pop(Pilha *pilha, char *acao);
int pilha_peek(Pilha *pilha, char *acao);
void pilha_imprimir_ultimas(Pilha *pilha);
void pilha_liberar(Pilha *pilha);

#endif