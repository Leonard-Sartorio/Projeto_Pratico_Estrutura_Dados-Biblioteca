#include <string.h>
#include "ordenacao.h"

//inserction short
void ordenar_livros(Livro vetor[], int quantidade) {
    int i, j;
    Livro chave;

    for (i = 1; i < quantidade; i++) {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0 &&
              (strcmp(vetor[j].titulo, chave.titulo) > 0 ||
              (strcmp(vetor[j].titulo, chave.titulo) == 0 &&
               vetor[j].id > chave.id))) {

            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = chave;
    }
}