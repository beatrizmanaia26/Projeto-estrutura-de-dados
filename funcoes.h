#ifndef PROJETO1_H
#define PROJETO1_H
#include <stdio.h>

// tudo que tem E na frente equivale a celula de tal procedimento
// Registro do usuario
typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct {
  char nome[50];
  char rg[10];
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

typedef struct EPilha{
  struct EPilha *anterior;
  int operacao;
  struct EPilha *prox;
}Epilha;

typedef struct Pilha{
  Epilha *topo;
  int qtde;
}Pilha;

// menus
int menu();
void subMenuCadastrar(Lista *lista);
void subMenuAtendimento(Lista *lista, Fila *fila);
// void subMenuPesquisa(Lista *lista);

// funcoes base dos structs
Registro *salvarPessoa(char *nome, int idade, char *rg, Data *data);
// inicializações
Elista *criaElista(Registro *r);
Lista *criaLista();
Efila *criaEfila(Registro *r);
Fila *criaFila();
E_arvore_busca *criaE_arv(int valor);
Arvore_busca *criaArvore();
Epilha *criaEPilha(int operacao);
Pilha *criaPilha();

Registro *procurarPaciente(Lista *lista, char *rg);

// funções de cadastrar
Data *criaData(int dia, int mes, int ano);
void cadastrar(Lista *lista);
void consultar(Lista *lista);
void mostrarLista(Lista *lista);
void atualizarDados(Lista *lista);
void removerPaciente(Lista *lista);

// funcoes atendimento
void enfileirarPaciente(Lista *lista, Fila *fila);
void desenfileirarpaciente(Lista *lista, Fila *fila);
void mostrarFila(Fila *fila);

void sobre();

void clearBuffer();
// guarda de inclusao (garante que conteudo do arquivo é incluido apenas 1x em
// cada arquivo que o referencia)
#endif