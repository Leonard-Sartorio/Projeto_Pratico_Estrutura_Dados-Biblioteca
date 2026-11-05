
#ifndef LISTA_H
#define LISTA_H

typedef struct NoLista {
    int id;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *inicio;
    NoLista *fim;
} Lista;

void lista_inicializar(Lista *lista);
int lista_inserir_fim(Lista *lista, int id);
void lista_imprimir(Lista *lista);
void lista_liberar(Lista *lista);

#endif
