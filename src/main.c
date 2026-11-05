#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "lista.h"
#include "livro.h"
#include "ordenacao.h"

int main() {
    Lista lista;
    Livro livro;
    NoLista *atual;
    Livro *vetor;
    int opcao;
    int id;
    int quantidade;
    int i;

    lista_inicializar(&lista);

    do {
        printf("\n========== SISTEMA BIBLIOTECA ==========\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Exibir livros cadastrados\n");
        printf("3 - Limpar lista de livros\n");
        printf("4 - Remover livro por ID\n");
        printf("5 - Exibir livros ordenados por titulo\n");
        printf("0 - Sair\n");
        printf("========================================\n");

        if (!lerInteiro("Escolha uma opcao: ", 0, 5, &opcao)) {
            break;
        }

        switch (opcao) {

            case 1:
                if (!cadastrarLivro(&livro)) {
                    break;
                }

                if (lista_inserir_fim(&lista, livro)) {
                    printf("\nLivro adicionado a lista com sucesso!\n");
                } else {
                    printf("\nErro ao adicionar livro. Memoria insuficiente.\n");
                }
                break;

            case 2:
                lista_imprimir(&lista);
                break;

            case 3:
                lista_liberar(&lista);
                printf("\nLista de livros limpa com sucesso!\n");
                break;

            case 4:
                if (!lerInteiro("Digite o ID do livro que deseja remover: ",
                                1, INT_MAX, &id)) {
                    break;
                }

                if (lista_remover_id(&lista, id)) {
                    printf("\nLivro removido com sucesso!\n");
                } else {
                    printf("\nNenhum livro encontrado com esse ID.\n");
                }
                break;

            case 5:
                quantidade = 0;
                atual = lista.inicio;

                // Conta os livros cadastrados
                while (atual != NULL) {
                    quantidade++;
                    atual = atual->proximo;
                }

                if (quantidade == 0) {
                    printf("\nNenhum livro cadastrado.\n");
                    break;
                }

                // Cria um vetor auxiliar
                vetor = malloc(quantidade * sizeof(Livro));

                if (vetor == NULL) {
                    printf("\nErro ao alocar memoria para ordenacao.\n");
                    break;
                }

                // Copia os livros da lista para o vetor
                atual = lista.inicio;

                for (i = 0; i < quantidade; i++) {
                    vetor[i] = atual->livro;
                    atual = atual->proximo;
                }

                // Ordena o vetor auxiliar
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

            case 0:
                printf("\nEncerrando programa...\n");
                break;
        }

    } while (opcao != 0);

    lista_liberar(&lista);

    return 0;
}