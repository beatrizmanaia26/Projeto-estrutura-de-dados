
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
// para pegar data atual
#include <time.h>

int menu() {
  int opcao;
  printf("Qual o numero da operação que deseja "
         "fazer\n1.Cadastro\n2.Atendimento\n3.Pesquisa\n4.Desfazer "
         "Operação\n5.Carregar Arquivo\n6.Salvar Arquivo\n7.Sobre\n");
  scanf("%d", &opcao);
  return opcao;
}

void subMenuCadastrar(Lista *lista) {
  int subOpcao;
  printf("1-Cadastrar novo paciente\n2-Consultar paciente cadastrado \n3-Mostrar lista completa \n4-Atualizar dados de paciente \n4-Remover paciente.\n");
  printf("Digite o número de sua escolha: ");
  scanf("%d", &subOpcao);
  switch (subOpcao) {
  case 1:
    //cadastrar(lista);
    criaElista(lista);
    break;
    // case 2:
    //  consultar();
  case 3:
    //  mostrarLista(lista);
    break;
  }
}
// informacoes para cadastrar pessoa
void salvarPessoa(Registro *r) {
  Registro pessoa;
  printf("Digite o nome da pessoa: ");
  scanf("%s", pessoa.nome);
  clearBuffer();
  printf("Digite o RG da pessoa: ");
  scanf("%s", pessoa.rg); // RG TER 9 DIGITOS E SER ENTRE . E -
                          // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  clearBuffer();
  printf("Digite a idade da pessoa: ");
  // scanf("%d", &pessoa.idade);
  clearBuffer();
  printf("aqui");
  // Salvar data de entrada
  //  time_t t = time(NULL);//tempo atual
  //  struct tm *tm_info = localtime(&t);  // Converter para estrutura tm
  //  int dia = tm_info->tm_mday;
  //  pessoa->entrada->dia = dia;
  //  int mes = tm_info->tm_mon + 1;
  //  pessoa->entrada->mes = mes;
  //  int ano = tm_info->tm_year + 1900;
  //  pessoa->entrada->ano = ano;
r = &pessoa;
}

void criaElista(Elista *eli) { //modificar a lista aqui dentro
  Registro r; //cria variavel antes e passa pra funcao e na cadastrar passo r pra alterar
  Elista *celula = malloc(sizeof(Elista));
  celula->prox = NULL;
  // Registro dados =
  salvarPessoa(&r); //USAR REGISTRO QUE RECBI 
  // celula->dados = &dados;
  eli = celula;
}

void criaLista(Lista *lis) {
  Lista *lista = malloc(sizeof(Lista));
  lista->inicio = NULL;
  lista->qtde = 0;
  lis = lista;
}
// item 1 submenu cadastrar
void cadastrar(Lista *lista) { // insere ordenadamente
  Elista *novo;
  criaElista(novo);
  Elista *atual = lista->inicio;
  Elista *anterior = NULL;
  if (lista->inicio == NULL) {
    lista->inicio = novo;
  }
  while (atual != NULL && lista->qtde != 0) { // percorre enquanto nao é vazio e não ta no final
                             // da lista de pacientes
    atual = atual->prox;
    anterior = atual;
  }
  // Inserindo na lista
  anterior->prox = novo;
  lista->qtde++;
}

// item 3 submenu cadastrar
void mostrarLista(Lista *lista) {
  Elista *atual = lista->inicio;
  while (atual != NULL) {
    printf("Nome: %s\n", atual->dados->nome);
    printf("Idade: %d\n", atual->dados->idade);
    printf("RG: %s\n", atual->dados->rg);
    printf("Data: %d/%d/%d", atual->dados->entrada->dia,
           atual->dados->entrada->mes, atual->dados->entrada->ano);
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
