#include <stdio.h>
#include <limits.h>

#include "lista.h"
#include "livro.h"

int main() {
    Lista lista;
    int opcao;
    int id;

    lista_inicializar(&lista);

    do {
        printf("\n========== SISTEMA BIBLIOTECA ==========\n");
        printf("1 - Inserir ID na lista\n");
        printf("2 - Exibir lista\n");
        printf("3 - Limpar lista\n");
        printf("0 - Sair\n");
        printf("========================================\n");

        if (!lerInteiro("Escolha uma opcao: ", 0, 3, &opcao)) {
            break;
        }

        switch (opcao) {

            case 1:
                if (!lerInteiro("Digite o ID: ", 1, INT_MAX, &id)) {
                    break;
                }

                if (lista_inserir_fim(&lista, id)) {
                    printf("ID inserido com sucesso!\n");
                } else {
                    printf("Erro ao inserir ID. Memoria insuficiente.\n");
                }
                break;

            case 2:
                printf("\nLista atual:\n");
                lista_imprimir(&lista);
                break;

            case 3:
                lista_liberar(&lista);
                lista_inicializar(&lista);
                printf("Lista limpa com sucesso!\n");
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;
        }

    } while (opcao != 0);

    lista_liberar(&lista);

    return 0;
}