
#ifndef LIVRO_H
#define LIVRO_H

typedef struct {
    int id;
    char titulo[80];
    char autor[80];
    int ano;
} Livro;

int lerInteiro(const char *mensagem, int minimo, int maximo, int *valor);
int cadastrarLivro(Livro *livro);
void exibirLivro(Livro livro);

#endif
