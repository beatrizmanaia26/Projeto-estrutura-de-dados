#ifndef PROJETO1_H
#define PROJETO1_H
#include <stdio.h>

// tudp que tem E na frente equivale a celula de tal procedimento

// Registro do usuario
typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct {
  char nome[50];
  char rg[20];
  int idade;
  Data *entrada;
} Registro;

// lista dinamica encadeada
typedef struct Elista {
  Registro *dados;
  struct Elista *prox;
} Elista;

typedef struct {
  Elista *inicio;
  int qtde;
} Lista;

// fila encadeada
typedef struct Efila {
  Registro *dados;
  struct Efila *prox;
} Efila;

typedef struct {
  Efila *head;
  Efila *tail;
  int qtde;
} Fila;

// arvore binaria de busca
// Arvore para buscar as coisas mais facil
typedef struct E_arvore_busca {
  Registro *dados;
  struct E_arvore_busca *esq;
  struct E_arvore_busca *dir;
} E_arvore_busca;

typedef struct {
  E_arvore_busca *raiz;
  int qtde;
} Arvore_busca;

// typedef struct EPilha{
// }
// typedef struct Pilha{
// }

int menu();
void subMenuCadastrar(Lista *lista);

Registro salvarPessoa();
Elista *criaElista();
Lista *criaLista();
Efila *criaEfila(int valor);
Fila *criaFila();
E_arvore_busca *criaE_arv(int valor);
Arvore_busca *criaArvore();

void cadastrar(Lista *lista);
void mostrarLista(Lista *lista);

// guarda de inclusao (garante que conteudo do arquivo é incluido apenas 1x em
// cada arquivo que o referencia)
#endif