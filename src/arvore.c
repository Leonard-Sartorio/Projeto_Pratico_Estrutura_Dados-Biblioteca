
#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

/* Inicializa a arvore */
void arvore_inicializar(Arvore *arvore) {
    arvore->raiz = NULL;
}

/* Insere um livro na arvore */
static NoArvore *inserir_recursivo(NoArvore *raiz, Livro livro, int *sucesso) {
    if (raiz == NULL) {
        NoArvore *novo = malloc(sizeof(NoArvore));

        if (novo == NULL) {
            *sucesso = 0;
            return NULL;
        }

        novo->livro = livro;
        novo->esquerda = NULL;
        novo->direita = NULL;

        *sucesso = 1;
        return novo;
    }

    if (livro.id < raiz->livro.id) {
        NoArvore *novo = inserir_recursivo(raiz->esquerda, livro, sucesso);

        if (*sucesso) {
            raiz->esquerda = novo;
        }
    } else if (livro.id > raiz->livro.id) {
        NoArvore *novo = inserir_recursivo(raiz->direita, livro, sucesso);

        if (*sucesso) {
            raiz->direita = novo;
        }
    } else {
        /* IDs duplicados nao sao permitidos */
        *sucesso = 0;
    }

    return raiz;
}

int arvore_inserir(Arvore *arvore, Livro livro) {
    int sucesso = 0;

    arvore->raiz = inserir_recursivo(arvore->raiz, livro, &sucesso);

    return sucesso;
}

/* Busca um livro pelo ID */
static Livro *buscar_recursivo(NoArvore *raiz, int id) {
    if (raiz == NULL) {
        return NULL;
    }

    if (id == raiz->livro.id) {
        return &raiz->livro;
    }

    if (id < raiz->livro.id) {
        return buscar_recursivo(raiz->esquerda, id);
    }

    return buscar_recursivo(raiz->direita, id);
}

Livro *arvore_buscar(Arvore *arvore, int id) {
    return buscar_recursivo(arvore->raiz, id);
}

/* Encontra o menor ID de uma subarvore */
static NoArvore *encontrar_menor(NoArvore *raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }

    return raiz;
}

/* Remove um livro da arvore */
static NoArvore *remover_recursivo(NoArvore *raiz, int id, int *sucesso) {
    NoArvore *temp;

    if (raiz == NULL) {
        return NULL;
    }

    if (id < raiz->livro.id) {
        raiz->esquerda = remover_recursivo(raiz->esquerda, id, sucesso);
    } else if (id > raiz->livro.id) {
        raiz->direita = remover_recursivo(raiz->direita, id, sucesso);
    } else {
        *sucesso = 1;

        /* Caso 1: no sem filhos */
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }

        /* Caso 2: no com apenas filho direito */
        if (raiz->esquerda == NULL) {
            temp = raiz->direita;
            free(raiz);
            return temp;
        }

        /* Caso 2: no com apenas filho esquerdo */
        if (raiz->direita == NULL) {
            temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        /* Caso 3: no com dois filhos */
        temp = encontrar_menor(raiz->direita);

        raiz->livro = temp->livro;

        raiz->direita = remover_recursivo(
            raiz->direita,
            temp->livro.id,
            sucesso
        );
    }

    return raiz;
}

int arvore_remover(Arvore *arvore, int id) {
    int sucesso = 0;

    arvore->raiz = remover_recursivo(arvore->raiz, id, &sucesso);

    return sucesso;
}

/* Percurso em ordem: esquerda, raiz, direita */
static void listar_recursivo(NoArvore *raiz) {
    if (raiz == NULL) {
        return;
    }

    listar_recursivo(raiz->esquerda);

    printf("\nID: %d\n", raiz->livro.id);
    printf("Titulo: %s\n", raiz->livro.titulo);
    printf("Autor: %s\n", raiz->livro.autor);
    printf("Ano: %d\n", raiz->livro.ano);

    listar_recursivo(raiz->direita);
}

void arvore_listar_em_ordem(Arvore *arvore) {
    if (arvore->raiz == NULL) {
        printf("\nArvore vazia.\n");
        return;
    }

    printf("\n===== LIVROS EM ORDEM CRESCENTE DE ID =====\n");

    listar_recursivo(arvore->raiz);
}

/* Consulta o livro de menor ID */
Livro *arvore_menor_id(Arvore *arvore) {
    NoArvore *menor = encontrar_menor(arvore->raiz);

    if (menor == NULL) {
        return NULL;
    }

    return &menor->livro;
}

/* Consulta o livro de maior ID */
Livro *arvore_maior_id(Arvore *arvore) {
    NoArvore *atual = arvore->raiz;

    if (atual == NULL) {
        return NULL;
    }

    while (atual->direita != NULL) {
        atual = atual->direita;
    }

    return &atual->livro;
}

/* Libera toda a memoria da arvore */
static void liberar_recursivo(NoArvore *raiz) {
    if (raiz == NULL) {
        return;
    }

    liberar_recursivo(raiz->esquerda);
    liberar_recursivo(raiz->direita);

    free(raiz);
}

void arvore_liberar(Arvore *arvore) {
    liberar_recursivo(arvore->raiz);
    arvore->raiz = NULL;
}
