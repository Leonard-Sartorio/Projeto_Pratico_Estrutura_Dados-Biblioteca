
#ifndef LIVRO_H
#define LIVRO_H

typedef struct {
    int id;
    char titulo[80];
    char autor[80];
    int ano;
} Livro;

int cadastrarLivro(Livro *livro);
void exibirLivro(Livro livro);

#endif
