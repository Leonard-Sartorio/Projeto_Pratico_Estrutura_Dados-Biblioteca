
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <errno.h> // facilitar verificacoes

#include "livro.h"

int lerInteiro(const char *mensagem, int minimo, int maximo, int *valor) {
    char entrada[100];
    char *fim;
    long numero;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
            return 0;

        if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Entrada muito longa.\n");
            continue;
        }

        errno = 0;
        numero = strtol(entrada, &fim, 10);

        while (isspace((unsigned char)*fim))
            fim++;

        if (entrada == fim || *fim != '\0' ||
            errno == ERANGE || numero < minimo || numero > maximo) {
            printf("Valor invalido. Tente novamente.\n");
            continue;
        }

        *valor = (int)numero;
        return 1;
    }
}

static int lerTexto(const char *mensagem, char destino[80]) {
    char entrada[256];
    size_t tamanho;
    size_t i;
    int somenteEspacos;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
            return 0;

        if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Texto muito longo. Maximo de 79 caracteres.\n");
            continue;
        }

        entrada[strcspn(entrada, "\n")] = '\0';
        tamanho = strlen(entrada);
        somenteEspacos = 1;

        for (i = 0; i < tamanho; i++) {
            if (!isspace((unsigned char)entrada[i])) {
                somenteEspacos = 0;
                break;
            }
        }

        if (tamanho == 0 || tamanho > 79 || somenteEspacos) {
            printf("Texto invalido. Tente novamente.\n");
            continue;
        }

        strcpy(destino, entrada);
        return 1;
    }
}

int cadastrarLivro(Livro *livro) {
    printf("\n=== CADASTRO DE LIVRO ===\n");

    if (!lerInteiro("ID: ", 1, 2147483647, &livro->id))
        return 0;

    if (!lerTexto("Titulo: ", livro->titulo))
        return 0;

    if (!lerTexto("Autor: ", livro->autor))
        return 0;

    if (!lerInteiro("Ano: ", 1, 2026, &livro->ano))
        return 0;

    return 1;
}

void exibirLivro(Livro livro) {
    printf("\nID: %d\n", livro.id);
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Ano: %d\n", livro.ano);
}


