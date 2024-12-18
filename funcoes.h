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
  struct E_arvore_busca *pai;
} E_arvore_busca;

typedef struct {
  E_arvore_busca *raiz;
  int qtde;
} Arvore_busca;

//para o item "desfazer operacao"
typedef struct EPilha{
  struct EPilha *anterior;
  int operacao;
  Registro *dados;
  struct EPilha *prox;
}Epilha;

typedef struct Pilha{
  Epilha *topo;
  int qtde;
}Pilha;

// menus
int menu();
void subMenuCadastrar(Lista *lista, Arvore_busca *arvoreAno, Arvore_busca *arvoreMes, Arvore_busca *arvoreDia, Arvore_busca *arvoreIdade);
void subMenuAtendimento(Lista *lista, Fila *fila, Pilha *stack, Registro *r);
void subMenuPesquisa(Arvore_busca *arvoreAno, Arvore_busca *arvoreMes, Arvore_busca *arvoreDia, Arvore_busca *arvoreIdade, Registro *r);

// funcoes base dos structs
Registro *salvarPessoa(char *nome, int idade, char *rg, Data *data);
// inicializações
Elista *criaElista(Registro *r);
Lista *criaLista();
Efila *criaEfila(Registro *r);
Fila *criaFila();
E_arvore_busca *criaE_arv(Registro *r);
Arvore_busca *criaArvore();
Epilha *criaEPilha(int operacao, Registro *r);
Pilha *criaPilha();

Registro *procurarPaciente(Lista *lista, char *rg);

// funções de cadastrar
Data *criaData(int dia, int mes, int ano);
void cadastrar(Lista *lista, Arvore_busca *arvoreAno, Arvore_busca *arvoreMes, Arvore_busca *arvoreDia, Arvore_busca *arvoreIdade);
void consultar(Lista *lista);
void mostrarLista(Lista *lista);
void atualizarDados(Lista *lista);
void removerPaciente(Lista *lista, Arvore_busca *arvoreAno, Arvore_busca *arvoreMes, Arvore_busca *arvoreDia, Arvore_busca *arvoreIdade);

// funcoes atendimento
void enfileirarPaciente(Lista *lista, Fila *fila, Pilha *stack, Registro *r);
Registro *desenfileirarpaciente(Lista *lista, Fila *fila, Pilha *stack, Registro *r);
void mostrarFila(Fila *fila);

// funcoes pesquisa
void in_ordem(E_arvore_busca *raiz);
void *registroOrdenadoAno(Arvore_busca *arvore, Registro *r);
void *registroOrdenadoMes(Arvore_busca *arvore, Registro *r);
void *registroOrdenadoDia(Arvore_busca *arvore, Registro *r);
void *registroOrdenadoIdade(Arvore_busca *arvore, Registro *r);

//funcoes de remover
void push(Pilha *stack, int operacao, Registro *r);
void enfileirarPacienteAutomatico(Lista *lista, Fila *fila, Registro *r, Pilha *stack); //para nao ter que digitar o rg da pessoa a ser enfileirada
void DesfazerOperacao(Lista *lista, Fila *fila, Pilha *stack); 

void salvaArquivo(Lista *lista, char *nomeArquivo);
int lerArquivo(Lista *lista,int cont, char *nomeArquivo, Arvore_busca *arvoreAno, Arvore_busca *arvoreMes, Arvore_busca *arvoreDia, Arvore_busca *arvoreIdade);
void sobre();

E_arvore_busca* buscar_valorAno(Arvore_busca *arvore, Registro *pessoa);
E_arvore_busca* buscar_valorMes(Arvore_busca *arvore, Registro *pessoa);
E_arvore_busca* buscar_valorDia(Arvore_busca *arvore, Registro *pessoa);
E_arvore_busca* buscar_valorIdade(Arvore_busca *arvore, Registro *r);

void apaga_arvoreAno(Arvore_busca *arvore, E_arvore_busca *vertice);
void apaga_arvoreMes(Arvore_busca *arvore, E_arvore_busca *vertice);
void apaga_arvoreDia(Arvore_busca *arvore, E_arvore_busca *vertice);
void apaga_arvoreIdade(Arvore_busca *arvore, E_arvore_busca *vertice);

void clearBuffer();
// guarda de inclusao (garante que conteudo do arquivo é incluido apenas 1x em
// cada arquivo que o referencia)
#endif