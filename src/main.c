
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "lista.h"
#include "livro.h"
#include "ordenacao.h"
#include "arvore.h"
#include "pilha.h"
#include "fila.h"

int main() {
    Lista lista;
    Arvore arvore;
    Pilha historico;
    Fila filaAtendimento;

    Livro livro;
    Livro atendido;
    NoLista *atual;
    Livro *vetor;
    Livro *encontrado;

    char acao[TAM_ACAO];

    int opcao;
    int id;
    int quantidade;
    int i;

    lista_inicializar(&lista);
    arvore_inicializar(&arvore);
    pilha_inicializar(&historico);
    fila_inicializar(&filaAtendimento);

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
        printf("10 - Adicionar livro a fila de atendimento\n");
        printf("11 - Atender proximo livro da fila\n");
        printf("12 - Exibir fila de atendimento\n");
        printf("13 - Exibir ultimas cinco acoes\n");
        printf("14 - Consultar ultima acao\n");
        printf("15 - Remover ultima acao do historico\n");
        printf("0 - Sair\n");
        printf("========================================\n");

        if (!lerInteiro("Escolha uma opcao: ", 0, 15, &opcao)) {
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

                snprintf(acao, TAM_ACAO,
                         "Cadastro do livro ID %d", livro.id);

                if (!pilha_push(&historico, acao)) {
                    printf("Aviso: nao foi possivel registrar no historico.\n");
                }

                break;

            case 2:
                lista_imprimir(&lista);
                break;

            case 3:
                lista_liberar(&lista);
                arvore_liberar(&arvore);

                fila_liberar(&filaAtendimento);

                printf("\nTodos os livros foram removidos.\n");

                pilha_push(&historico, "Limpeza de todos os livros");
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

                snprintf(acao, TAM_ACAO,
                         "Remocao do livro ID %d", id);

                if (!pilha_push(&historico, acao)) {
                    printf("Aviso: nao foi possivel registrar no historico.\n");
                }

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

            case 10:
                if (!lerInteiro("Digite o ID do livro solicitado: ",
                                1, INT_MAX, &id)) {
                    break;
                }

                encontrado = arvore_buscar(&arvore, id);

                if (encontrado == NULL) {
                    printf("\nLivro nao encontrado.\n");
                    break;
                }

                if (!fila_enfileirar(&filaAtendimento, *encontrado)) {
                    printf("\nErro ao adicionar livro na fila.\n");
                    break;
                }

                printf("\nLivro adicionado a fila de atendimento!\n");

                snprintf(acao, TAM_ACAO,
                         "Livro ID %d adicionado a fila", id);

                pilha_push(&historico, acao);
                break;

            case 11:
                if (!fila_desenfileirar(&filaAtendimento, &atendido)) {
                    printf("\nNao existem livros aguardando atendimento.\n");
                    break;
                }

                printf("\nLivro atendido:\n");
                exibirLivro(atendido);

                snprintf(acao, TAM_ACAO,
                         "Atendimento do livro ID %d", atendido.id);

                pilha_push(&historico, acao);
                break;

            case 12:
                fila_imprimir(&filaAtendimento);
                break;

            case 13:
                pilha_imprimir_ultimas(&historico);
                break;

            case 14:
                if (pilha_peek(&historico, acao)) {
                    printf("\nUltima acao: %s\n", acao);
                } else {
                    printf("\nHistorico vazio.\n");
                }
                break;

            case 15:
                if (pilha_pop(&historico, acao)) {
                    printf("\nAcao removida do historico: %s\n", acao);
                } else {
                    printf("\nHistorico vazio.\n");
                }
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;
        }

    } while (opcao != 0);

    /* Libera a memoria de todas as estruturas */
    lista_liberar(&lista);
    arvore_liberar(&arvore);
    pilha_liberar(&historico);
    fila_liberar(&filaAtendimento);

    return 0;
}
