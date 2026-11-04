
#include <stdio.h>
#include "livro.h"

int main() {
    Livro livro;

    printf("================================\n");
    printf("       SISTEMA BIBLIOTECA\n");
    printf("================================\n");

    if (!cadastrarLivro(&livro)) {
        printf("\nEntrada encerrada.\n");
        return 0;
    }

    exibirLivro(livro); //função do menu

    printf("\nPrograma finalizado.\n");

    return 0;
}
