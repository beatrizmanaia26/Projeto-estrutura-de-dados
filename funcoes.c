#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h> //para malloc
#include <string.h> //para usar strcmp
#include <time.h>   // para pegar data atual

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

void subMenuAtendimento(Lista *lista, Fila *fila) {
  int subOpcao;
  printf("1-Enfileirar paciente\n2-Desenfileirar paciente \n3-Mostrar fila.\n");
  printf("Digite o número de sua escolha: ");
  scanf("%d", &subOpcao);
  printf("\n");
  switch (subOpcao) {
  case 1:
    enfileirarPaciente(lista, fila);
    break;
  case 2:
    desenfileirarpaciente(lista, fila);
    break;
  case 3:
    mostrarFila(fila);
    break;
  }
}

void subMenuPesquisa(Lista *lista) {
  int subOpcao;
  printf("1-Mostrar registros ordenados por ano de registro.\n2-Mostrar "
         "registros ordenados por mês de registro.\n"
         "\n3-Mostrar registros ordenados por dia de registro.\n4-Mostrar "
         "registros ordenados por idade do paciente.\n");
  printf("Digite o número de sua escolha: ");
  scanf("%d", &subOpcao);
  printf("\n");
  switch (subOpcao) {
  case 1:
    // registroOrdenadoAno(lista);
    break;
    // case 2:

    //   break;
    // case 3:

    //   break;
    // case 4:

    //   break;
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

Data *criaData(int dia, int mes, int ano) {
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

  // verificar se nao cadastrou o mesmo rg
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
        printf(
            "Este RG já está cadastrado. Por favor, insira um RG diferente.\n");
        break;
      }
      atual = atual->prox;
    }
  } while (rgCadastrado);

  printf("Digite a idade da pessoa: ");
  scanf("%d", &idade);

  // Salvar data de entrada
  time_t t = time(NULL);              // tempo atual
  struct tm *tm_info = localtime(&t); // Converter para estrutura tm
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

// item 2 submenu cadastrar
void consultar(Lista *lista) {
  char rg[10];
  printf("Digite o RG da pessoa a ser consultada: ");
  scanf("%s", rg);
  Elista *atual = lista->inicio;
  while (atual != NULL) {
    if (strcmp(atual->dados->rg, rg) == 0) {
      printf("Nome: %s\n", atual->dados->nome);
      printf("RG: %s\n", atual->dados->rg);
      printf("Idade: %d\n", atual->dados->idade);
      printf("Data de cadastro: %d/%d/%d\n", atual->dados->entrada->dia,
             atual->dados->entrada->mes, atual->dados->entrada->ano);
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
  if (lista->inicio == NULL) {
    printf("Nenhum paciente cadastrado\n");
    return;
  }
  Elista *atual = lista->inicio;
  while (atual != NULL) {
    Registro r = *atual->dados;
    printf("Nome: %s\n", r.nome);
    printf("Idade: %d\n", atual->dados->idade);
    printf("RG: %s\n", atual->dados->rg);
    printf("Data: %d/%d/%d\n", atual->dados->entrada->dia,
           atual->dados->entrada->mes, atual->dados->entrada->ano);
    atual = atual->prox;
    printf("\n");
  }
  printf("\n");
}

// item 4 submenu cadastrar
void atualizarDados(Lista *lista) {
  char rg[10];
  printf("Digite o RG da pessoa a ser atualizada: ");
  scanf("%s", rg);
  printf("\n");
  Elista *atual = lista->inicio;
  while (atual != NULL) {
    if (strcmp(atual->dados->rg, rg) == 0) {
      break;
    }
    atual = atual->prox;
  }
  if (atual == NULL) {
    printf("Paciente não cadastrado :(\n");
    return;
  }
  printf("O que deseja atualizar?\n");
  printf("1-Nome\n2-RG\n3-Idade\n");
  int opcao;
  scanf("%d", &opcao);
  do {
    if (opcao == 1) {
      printf("Digite o novo nome: ");
      scanf("%s", atual->dados->nome);
    } else if (opcao == 2) {
      // verificar se nao cadastrou o mesmo rg
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
            printf("Este RG já está cadastrado. Por favor, insira um RG "
                   "diferente.\n");
            break;
          }
          atual = atual->prox;
        }
        if (!rgCadastrado) {
          strcpy(atual->dados->rg, novoRg);
        } else {
          printf("Rg já cadastrado, escreva outro\n");
        }
      } while (rgCadastrado);

    } else if (opcao == 3) {
      printf("Digite a nova idade: ");
      scanf("%d", &atual->dados->idade);
      clearBuffer();
    } else {
      printf("Opção inválida\n");
    }
  } while (opcao != 1 && opcao != 2 && opcao != 3);
  printf("Dados atualizados com sucesso!\n");
  printf("\n");
}

// item 5 submenu cadastrar
void removerPaciente(Lista *lista) {
  char rg[10];
  printf("Digite o RG da pessoa a ser removida: ");
  scanf("%s", rg);
  printf("\n");
  Elista *atual = lista->inicio;
  Elista *anterior = NULL;
  while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
    anterior = atual;
    atual = atual->prox;
  }
  if (atual == NULL) {
    printf("Paciente não cadastrado :(\n");
    printf("\n");
  } else {
    if (anterior == NULL) {
      lista->inicio = atual->prox;
      lista->qtde--;
    } else {
      anterior->prox = atual->prox;
      lista->qtde--;
    }
    printf("Paciente removido com sucesso\n");
  }
}

// para a fila
Efila *criaEfila(Registro *r) {
  Efila *celula = malloc(sizeof(Efila));
  celula->prox = NULL;
  celula->dados = r;
  return celula;
}

Fila *criaFila() {
  Fila *queue = malloc(sizeof(Fila));
  queue->head = NULL;
  queue->tail = NULL;
  queue->qtde = 0;
  return queue;
}

Registro *procurarPaciente(Lista *lista, char *rg) {
  // verificar se paciente existe
  Registro *registro = malloc(sizeof(Registro));
  Elista *atual = lista->inicio;
  Elista *anterior = NULL;
  while (atual != NULL && strcmp(atual->dados->rg, rg) !=
                              0) { // while que percorre a lista ate achar o rg
    anterior = atual;
    atual = atual->prox;
  }
  if (atual != NULL) {
    return atual->dados;
  } else {
    registro = NULL;
    printf("Paciente não cadastrado :(\n");
    printf("\n");
    return registro;
  }
}

// item 1 do subMenuAtendimento
void enfileirarPaciente(Lista *lista, Fila *fila) { // precisa da condição pra não add o mesmo paciente
  char rg[10];
  printf("Digite o RG do paciente: ");
  scanf("%s", rg);
  printf("\n");
  Registro *paciente = procurarPaciente(lista, rg);
  if (paciente == NULL) {
    return;
  } else { // Verifica se o paciente já está na fila
    Efila *atual = fila->head;
    while (atual != NULL && atual->dados != paciente) {
      atual = atual->prox;
    }
    if (atual != NULL) {
      printf("Paciente já está na fila\n");
      printf("\n");
      return;
    }
  }
  Efila *nova = criaEfila(paciente);
  if (fila->qtde == 0) { // fila vazia
    fila->head = nova;
  } else {
    fila->tail->prox = nova;
  }
  fila->tail = nova;
  fila->qtde++;
  printf("%s entrou na fila!\n", paciente->nome);
  printf("\n");
}

// item 2 do subMenuAtendimento
void desenfileirarpaciente(Lista *lista, Fila *fila) {

  if (fila->qtde > 0) {
    Efila *removido = fila->head; // para poder dar free (desalocar memoria)
    // quando tem mais de um elemento
    fila->head = fila->head->prox;
    if (fila->qtde == 1) { // quando tem apenas 1 elemento
      fila->tail = NULL;
    }
    printf("%s saiu da fila!\n", removido->dados->nome);
    printf("\n");
    fila->qtde--;
    free(removido);
  } else {
    printf("Não há pacientes na fila\n");
    printf("\n");
    return;
  }
}

// item 3 do subMenuAtendimento
void mostrarFila(Fila *fila) {
  if (fila->head == NULL) {
    printf("A fila de atendimento está vazia\n");
    printf("\n");
    return;
  }
  Efila *atual = fila->head;
  int cont = 1;
  while (atual != NULL) {
    Registro r = *atual->dados;
    printf("%d-Nome: %s\n", cont,
           r.nome); // perguntar se vai precisa coloca o resto das informações
    atual = atual->prox;
    cont++;
    printf("\n");
  }
}

// sobre
void sobre() {
  printf(
      "Nome das desenvolvedoras: Beatriz Manaia Lourenço Berto e Luana Bortko "
      "Rodrigues\nCiclo: 4° período\nCurso: Ciencia da Computação\nDiciplina: "
      "Estrutura de dados\nData do término: X/11/2024\n");
}

// Função para limpar o buffer do teclado
void clearBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// item 1 do subMenuPesquisa
//  void registroOrdenadoAno(Lista *lista){ //ver se quando removemos um
//  paciente da fila ele n aparece aqui
//    //quando pessoa clicar em pesquisar por ano, pega a lista de registros
//    item por item e vai adicionando na arvore

// }

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