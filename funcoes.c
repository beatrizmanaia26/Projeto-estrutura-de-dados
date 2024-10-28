
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// para pegar data atual
#include <time.h>

int menu() {
  int opcao;
  printf("Qual o numero da operação que deseja "
         "fazer\n1.Cadastro\n2.Atendimento\n3.Pesquisa\n4.Desfazer"
         "Operação\n5.Carregar Arquivo\n6.Salvar Arquivo\n7.Sobre\n");
  scanf("%d", &opcao);
  printf("\n");
  return opcao;
}

void subMenuCadastrar(Lista *lista) {
  int subOpcao;
  printf(
      "1-Cadastrar novo paciente\n2-Consultar paciente cadastrado \n3-Mostrar "
      "lista completa \n4-Atualizar dados de paciente \n4-Remover paciente.\n");
  printf("Digite o número de sua escolha: ");
  scanf("%d", &subOpcao);
  printf("\n");
  switch (subOpcao) {
  case 1:
    cadastrar(lista);
    break;
  // case 2:
  //   consultar();
  case 3:
    mostrarLista(lista);
    break;
  }
}
// informacoes para cadastrar pessoa
Registro *salvarPessoa(char *nome, int idade, char *rg, Data *data) {
  Registro *pessoa = malloc(sizeof(Registro));
  strcpy(pessoa->nome, nome);
  pessoa->idade = idade;
  strcpy(pessoa->rg, rg);
  pessoa->entrada = data;
  return pessoa;
}

Elista *criaElista(Registro *r) { // modificar a lista aqui dentro
  Elista *celula = malloc(sizeof(Elista));
  celula->prox = NULL;
  celula->dados = r;
  return celula;
}

Lista *criaLista() {
  Lista *lista = malloc(sizeof(Lista));
  lista->inicio = NULL;
  lista->qtde = 0;
  return lista;
}

Data *criaData(int dia, int mes, int ano){
  Data *data = malloc(sizeof(Data));
  data->dia = dia;
  data->mes = mes;
  data->ano = ano;
  return data;
}
// item 1 submenu cadastrar
void cadastrar(Lista *lista) { // insere ordenadamente
  char nome[50];
  char rg[10];
  int idade = 0;
  printf("Digite o nome da pessoa: ");
  scanf("%s", nome);
  clearBuffer();
  printf("Digite o RG da pessoa: ");
  scanf("%s", rg); // RG TER 9 DIGITOS E SER ENTRE . E - !!!!!!!!!!!!!!!!!!!
  clearBuffer();
  printf("Digite a idade da pessoa: ");
  scanf("%d", &idade);
  clearBuffer();
  // Salvar data de entrada
  time_t t = time(NULL);//tempo atual
  struct tm *tm_info = localtime(&t);  // Converter para estrutura tm
  int dia = tm_info->tm_mday;
  int mes = tm_info->tm_mon + 1;
  int ano = tm_info->tm_year + 1900;
  Data *data = criaData(dia, mes, ano);
  Registro *pessoa = salvarPessoa(nome, idade, rg, data);
  Elista *novo = criaElista(pessoa);
  novo->prox = lista->inicio;
  lista->inicio = novo;
  lista->qtde++;
}

// item 3 submenu cadastrar
void mostrarLista(Lista *lista) {
  if(lista->inicio == NULL){
    printf("Lista vazia\n");
    return;
  }
  Elista *atual = lista->inicio;
  while (atual != NULL) {
    Registro r = *atual->dados;
    printf("Nome: %s\n", r.nome);
    //printf("Idade: %d\n", atual->dados->idade);
    //printf("RG: %s\n", atual->dados->rg);
    // printf("Data: %d/%d/%d", atual->dados->entrada->dia,atual->dados->entrada->mes, atual->dados->entrada->ano);
    atual = atual->prox;
  }  

  printf("\n");
}

// Função para limpar o buffer do teclado
void clearBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

