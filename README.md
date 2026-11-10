# Projeto_Pratico_Estrutura_Dados-Biblioteca


# Sistema de Biblioteca em C

## Sobre o projeto

Este projeto consiste no desenvolvimento de um sistema de gerenciamento de biblioteca utilizando a linguagem C, como parte das atividades acadêmicas da disciplina de Estruturas de Dados da Fatec Ribeirão Preto.

O sistema permite cadastrar, consultar, listar e remover livros, utilizando diferentes estruturas de dados para organizar e manipular as informações.

O objetivo é aplicar na prática os conceitos de estruturas de dados, alocação dinâmica de memória, modularização e organização de um projeto em C.

## Funcionalidades

- Cadastro de livros, contendo ID, título, autor e ano de publicação.
- Listagem dos livros cadastrados.
- Remoção de livros por ID.
- Busca de livros por ID.
- Consulta do livro com menor e maior ID.
- Listagem dos livros em ordem crescente de ID por meio da árvore.
- Ordenação dos livros por título.
- Gerenciamento da fila de atendimento.
- Registro e consulta do histórico de operações.

## Estruturas de dados utilizadas

| Estrutura | Aplicação no sistema |
|---|---|
| Lista encadeada | Armazenamento e gerenciamento dos livros cadastrados. |
| Árvore binária de busca (BST) | Busca, remoção e organização dos livros pelo ID. |
| Pilha | Registro do histórico das operações realizadas. |
| Fila | Organização dos livros aguardando atendimento. |
| Vetor e Insertion Sort | Ordenação dos livros pelo título. |

### Observações sobre as estruturas

Cada estrutura possui uma finalidade específica dentro do sistema.

A lista e a árvore mantêm os livros cadastrados, enquanto a pilha armazena o histórico das operações e a fila organiza os livros que aguardam atendimento.

A fila armazena uma cópia dos dados do livro. Portanto, caso um livro seja removido do cadastro enquanto ainda estiver aguardando atendimento, sua cópia continuará disponível na fila até ser atendida ou até que a fila seja limpa.

O histórico da pilha registra as operações, mas não possui funcionalidade de desfazer ações.

## Organização do projeto

```text
biblioteca/
│
├── include/
│   ├── livro.h
│   ├── lista.h
│   ├── arvore.h
│   ├── pilha.h
│   ├── fila.h
│   └── ordenacao.h
│
├── src/
│   ├── main.c
│   ├── livro.c
│   ├── lista.c
│   ├── arvore.c
│   ├── pilha.c
│   ├── fila.c
│   └── ordenacao.c
│
├── Makefile
├── .gitignore
└── README.md
```

## Tecnologias utilizadas

- Linguagem C.
- GCC (GNU Compiler Collection).
- Git e GitHub para versionamento.
- GitHub Codespaces para desenvolvimento.
- Makefile para automatização da compilação.

## Como compilar e executar

É necessário possuir o GCC e o Make instalados.

Na pasta principal do projeto, execute:

### Compilar o programa

```bash
make
```

### Compilar e executar

```bash
make run
```

### Remover o executável gerado

```bash
make clean
```

## Testes

Foram definidos testes para verificar o funcionamento individual das estruturas de dados e a interação entre elas.

Os testes contemplam:

- Inserção, consulta, listagem e remoção de livros.
- Impedimento de IDs duplicados.
- Busca e remoção de elementos na árvore binária de busca.
- Funcionamento da pilha e do histórico de operações.
- Ordem de entrada e saída dos elementos da fila.
- Ordenação dos livros por título.
- Sincronização entre a lista e a árvore.
- Comportamento da fila quando um livro é removido do cadastro.
- Limpeza e liberação de memória das estruturas.

Os resultados dos testes serão registrados conforme a execução do programa.

## Autor
Leandro Sertorio
Projeto acadêmico desenvolvido como atividade da disciplina de Estruturas de Dados — Fatec Ribeirão Preto.
```

