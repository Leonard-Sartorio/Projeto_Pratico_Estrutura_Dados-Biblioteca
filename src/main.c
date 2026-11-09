
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "lista.h"
#include "livro.h"
#include "ordenacao.h"
#include "arvore.h"

int main() {
    Lista lista;
    Arvore arvore;

    Livro livro;
    NoLista *atual;
    Livro *vetor;
    Livro *encontrado;

    int opcao;
    int id;
    int quantidade;
    int i;

    lista_inicializar(&lista);
    arvore_inicializar(&arvore);

    do {
        printf("\n========== SISTEMA BIBLIOTECA ==========\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Exibir livros cadastrados\n");
        printf("3 - Limpar lista de livros\n");
        printf("4 - Remover livro por ID\n");
        printf("5 - Exibir livros ordenados por titulo\n");
        printf("6 - Listar livros pela arvore (em ordem)\n");
        printf("7 - Buscar livro na arvore por ID\n");
        printf("8 - Consultar livro com menor ID\n");
        printf("9 - Consultar livro com maior ID\n");
        printf("0 - Sair\n");
        printf("========================================\n");

        if (!lerInteiro("Escolha uma opcao: ", 0, 9, &opcao)) {
            break;
        }

        switch (opcao) {

            case 1:
                if (!cadastrarLivro(&livro)) {
                    break;
                }

                /* Verifica se o ID ja existe */
                if (arvore_buscar(&arvore, livro.id) != NULL) {
                    printf("\nErro: ja existe um livro com esse ID.\n");
                    break;
                }

                /* Insere primeiro na lista */
                if (!lista_inserir_fim(&lista, livro)) {
                    printf("\nErro ao inserir livro na lista.\n");
                    break;
                }

                /* Insere tambem na arvore */
                if (!arvore_inserir(&arvore, livro)) {
                    lista_remover_id(&lista, livro.id);
                    printf("\nErro ao inserir livro na arvore.\n");
                    break;
                }

                printf("\nLivro cadastrado com sucesso!\n");
                break;

            case 2:
                lista_imprimir(&lista);
                break;

            case 3:
                lista_liberar(&lista);
                arvore_liberar(&arvore);

                printf("\nTodos os livros foram removidos.\n");
                break;

            case 4:
                if (!lerInteiro("Digite o ID do livro que deseja remover: ",
                                1, INT_MAX, &id)) {
                    break;
                }

                if (arvore_buscar(&arvore, id) == NULL) {
                    printf("\nNenhum livro encontrado com esse ID.\n");
                    break;
                }

                lista_remover_id(&lista, id);
                arvore_remover(&arvore, id);

                printf("\nLivro removido com sucesso!\n");
                break;

            case 5:
                quantidade = 0;
                atual = lista.inicio;

                /* Conta os livros cadastrados */
                while (atual != NULL) {
                    quantidade++;
                    atual = atual->proximo;
                }

                if (quantidade == 0) {
                    printf("\nNenhum livro cadastrado.\n");
                    break;
                }

                /* Cria um vetor auxiliar */
                vetor = malloc(quantidade * sizeof(Livro));

                if (vetor == NULL) {
                    printf("\nErro ao alocar memoria para ordenacao.\n");
                    break;
                }

                /* Copia os livros da lista para o vetor */
                atual = lista.inicio;

                for (i = 0; i < quantidade; i++) {
                    vetor[i] = atual->livro;
                    atual = atual->proximo;
                }

                /* Ordena o vetor auxiliar */
                ordenar_livros(vetor, quantidade);

                printf("\n====== LIVROS ORDENADOS POR TITULO ======\n");

                for (i = 0; i < quantidade; i++) {
                    printf("\nID: %d\n", vetor[i].id);
                    printf("Titulo: %s\n", vetor[i].titulo);
                    printf("Autor: %s\n", vetor[i].autor);
                    printf("Ano: %d\n", vetor[i].ano);
                }

                free(vetor);
                break;

            case 6:
                arvore_listar_em_ordem(&arvore);
                break;

            case 7:
                if (!lerInteiro("Digite o ID para buscar: ",
                                1, INT_MAX, &id)) {
                    break;
                }

                encontrado = arvore_buscar(&arvore, id);

                if (encontrado == NULL) {
                    printf("\nLivro nao encontrado.\n");
                } else {
                    printf("\nLivro encontrado:\n");
                    exibirLivro(*encontrado);
                }
                break;

            case 8:
                encontrado = arvore_menor_id(&arvore);

                if (encontrado == NULL) {
                    printf("\nArvore vazia.\n");
                } else {
                    printf("\nLivro com menor ID:\n");
                    exibirLivro(*encontrado);
                }
                break;

            case 9:
                encontrado = arvore_maior_id(&arvore);

                if (encontrado == NULL) {
                    printf("\nArvore vazia.\n");
                } else {
                    printf("\nLivro com maior ID:\n");
                    exibirLivro(*encontrado);
                }
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;
        }

    } while (opcao != 0);

    /* Libera a memoria das estruturas */
    lista_liberar(&lista);
    arvore_liberar(&arvore);

    return 0;
}
