#ifndef PROJETO1_H
#define PROJETO1_H
#include <stdio.h>

typedef struct {
  int dia;
  int mes;
  int ano;
}Data;

typedef struct{
  char nome[50];
  char rg[20];
  int idade;
  Data *entrada;
}Registro;

typedef struct Elista{
  Registro *dados;
  struct Elista *prox;
}Elista;

typedef struct{
  Elista *inicio;
  int qtde;
}Lista;

typedef struct Efila{
  Registro *dados;
  struct Efila *prox;
}Efila;

typedef struct{
  Efila *head;
  Efila *tail;
  int qtde;
}Fila;

typedef struct E_arvore_busca{
  Registro *dados;
  struct E_arvore_busca *esq;
  struct E_arvore_busca *dir;
}E_arvore_busca;

typedef struct{
  E_arvore_busca *raiz;
  int qtde;
}Arvore_busca;

// typedef struct EPilha{
// }
// typedef struct Pilha{
// }

int menu();


//guarda de inclusao (garante que conteudo do arquivo é incluido apenas 1x em cada arquivo que o referencia)
#endif  