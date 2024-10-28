
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// para pegar data atual
#include <time.h>

int menu() {
  int opcao;
  printf("1.Cadastro\n2.Atendimento\n3.Pesquisa\n4.Desfazer"
         "Operação\n5.Carregar Arquivo\n6.Salvar Arquivo\n7.Sobre\n");
  printf("Digite o número de sua escolha: ");
  scanf("%d", &opcao);
  printf("\n");
  return opcao;
}

void subMenuCadastrar(Lista *lista) {
  int subOpcao;
  printf(
      "1-Cadastrar novo paciente\n2-Consultar paciente cadastrado \n3-Mostrar "
      "lista completa \n4-Atualizar dados de paciente \n5-Remover paciente.\n");
  printf("Digite o número de sua escolha: ");
  scanf("%d", &subOpcao);
  printf("\n");
  switch (subOpcao) {
  case 1:
    cadastrar(lista);
    break;
  case 2:
    consultar(lista);
    break;
  case 3:
    mostrarLista(lista);
    break;
  case 4:
    atualizarDados(lista);
    break;
  case 5:
    removerPaciente(lista);
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

  //verificar se nao cadastrou o mesmo rg
  int rgCadastrado;
  do {
    rgCadastrado = 0; 
    printf("Digite o RG da pessoa: ");
    scanf("%s", rg); // RG deve ter 9 dígitos, ser entre '.' e '-'
    clearBuffer();

    // Verifica se o RG já está cadastrado
    Elista *atual = lista->inicio;
    while (atual != NULL) {
      if (strcmp(atual->dados->rg, rg) == 0) {
        rgCadastrado = 1;
        printf("Este RG já está cadastrado. Por favor, insira um RG diferente.\n");
        break;
      }
      atual = atual->prox;
    }
  } while (rgCadastrado); 

  printf("Digite a idade da pessoa: ");
  scanf("%d", &idade);

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
  printf("\n");
  printf("Paciente cadastrado com sucesso!\n");
  printf("\n");
}

void consultar(Lista *lista){
  char rg[10];
  printf("Digite o RG da pessoa a ser consultada: ");
  scanf("%s", rg);
  Elista *atual = lista->inicio;
  while(atual != NULL){
    if(strcmp(atual->dados->rg, rg) == 0){
      printf("Nome: %s\n", atual->dados->nome);
      printf("RG: %s\n", atual->dados->rg);
      printf("Idade: %d\n", atual->dados->idade);
      printf("Data de cadastro: %d/%d/%d\n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
      printf("\n");
      return;
    }
    atual = atual->prox;
    printf("\n");
  }
  printf("Paciente não cadastrado :(\n");
}

// item 3 submenu cadastrar
void mostrarLista(Lista *lista) {
  if(lista->inicio == NULL){
    printf("Nenhum paciente cadastrado\n");
    return;
  }
  Elista *atual = lista->inicio;
  while (atual != NULL) {
    Registro r = *atual->dados;
    printf("Nome: %s\n", r.nome);
    printf("Idade: %d\n", atual->dados->idade);
    printf("RG: %s\n", atual->dados->rg);
    printf("Data: %d/%d/%d\n", atual->dados->entrada->dia,atual->dados->entrada->mes, atual->dados->entrada->ano);
    atual = atual->prox;
    printf("\n");
  }  
  printf("\n");
}

void atualizarDados(Lista *lista){
  char rg[10];
  printf("Digite o RG da pessoa a ser atualizada: ");
  scanf("%s", rg);
  printf("\n");
  Elista *atual = lista->inicio;
  while(atual != NULL){
    if(strcmp(atual->dados->rg, rg) == 0){
      break;
    }
    atual = atual->prox;
  }
  if(atual == NULL){
    printf("Paciente não cadastrado :(\n");
    return;
  }
  printf("O que deseja atualizar?\n");
  printf("1-Nome\n2-RG\n3-Idade\n");
  int opcao;
  scanf("%d", &opcao);
  do{
    if(opcao == 1){
      printf("Digite o novo nome: ");
      scanf("%s", atual->dados->nome);
    }else if(opcao == 2){
      //verificar se nao cadastrou o mesmo rg
      int rgCadastrado;
      do {
        char novoRg[10];
        rgCadastrado = 0; 
        printf("Digite o novo RG: ");
        scanf("%s", novoRg); 
        clearBuffer();

        // Verifica se o RG já está cadastrado
        Elista *atual = lista->inicio;
        while (atual != NULL) {
          if (strcmp(atual->dados->rg, novoRg) == 0) {
            rgCadastrado = 1;
            printf("Este RG já está cadastrado. Por favor, insira um RG diferente.\n");
            break;
          }
          atual = atual->prox;
        }
        if (!rgCadastrado) {
          strcpy(atual->dados->rg, novoRg);
        }
        else{
          printf("Rg já cadastrado, escreva outro\n");
        }
      } while(rgCadastrado); 

    }else if(opcao == 3){
      printf("Digite a nova idade: ");
      scanf("%d", &atual->dados->idade);
      clearBuffer();
    }else{
      printf("Opção inválida\n");
    }
  }while(opcao != 1 && opcao != 2 && opcao != 3);
  printf("Dados atualizados com sucesso!\n");
  printf("\n");
}

void removerPaciente(Lista *lista){
  char rg[10];
  printf("Digite o RG da pessoa a ser removida: ");
  scanf("%s", rg);
  printf("\n");
  Elista *atual = lista->inicio;
  Elista *anterior = NULL;
  while(atual != NULL && atual->dados->rg != rg){
    anterior = atual;
    atual = atual->prox;
  }
  if(atual == NULL){
    printf("Paciente não cadastrado :(\n");
  }else{
    if(anterior == NULL){
      lista->inicio = atual->prox;
      lista->qtde--;
    }else{
      anterior->prox = atual->prox;
      lista->qtde--;
    }
  }
}

void sobre(){
  printf("Nome das desenvolvedoras: Beatriz Manaia Lourenço Berto e Luana Bortko Rodrigues\nCiclo: 4° período\nCurso: Ciencia da Computação\nDiciplina: Estrutura de dados\nData do término: X/11/2024\n");
}

// Função para limpar o buffer do teclado
void clearBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

/* 
int salva_clientes(listaClientes Lc, char nomeArquivo[]) {
  FILE *f = fopen(nomeArquivo, "wb");
  if (f == NULL) { // vê se valor do ponteiro ta apontando pra NULL
    printf("Falha ao abrir o arquivo");
    return 1;
  }
  fwrite(&Lc, sizeof(listaClientes), 1, f);
  fclose(f);
  return 0;
}

int ler(listaClientes *Lc, char nomeArquivo[]) {
  FILE *f = fopen(nomeArquivo, "rb");
  if (f == NULL) {
    printf("Falha ao abrir o arquivo");
    return 1;
  }
  fread(Lc, sizeof(listaClientes), 1,
        f); // 1 pq é 1 struct (se fosse o tarefa seria 100 em quantidade)
  fclose(f);
  return 0;
}
*/

