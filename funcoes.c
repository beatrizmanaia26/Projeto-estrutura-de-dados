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
  default:
    printf("Opção inválida. Tente novamente.\n");
    break;
  }
}

void subMenuAtendimento(Lista *lista, Fila *fila, Pilha *stack, Registro *r) {
  int subOpcao;
  printf("1-Enfileirar paciente\n2-Desenfileirar paciente \n3-Mostrar fila.\n");
  printf("Digite o número de sua escolha: ");
  scanf("%d", &subOpcao);
  printf("\n");
  switch (subOpcao) {
  case 1:
    enfileirarPaciente(lista, fila, stack, r);
    break;
  case 2:
    desenfileirarpaciente(lista, fila, stack, r);
    break;
  case 3:
    mostrarFila(fila);
    break;
  default:
    printf("Opção inválida. Tente novamente.\n");
    break;
  }
}

void subMenuPesquisa(Arvore_busca *arvore, Registro *r) {
  int subOpcao;
  printf("1-Mostrar registros ordenados por ano de registro.\n2-Mostrar "
         "registros ordenados por mês de registro.\n"
         "3-Mostrar registros ordenados por dia de registro.\n4-Mostrar "
         "registros ordenados por idade do paciente.\n");
  printf("Digite o número de sua escolha: ");
  scanf("%d", &subOpcao);
  printf("\n");
  switch (subOpcao) {
  case 1:
    // registroOrdenadoAno(arvore, r);
    in_ordem(arvore->raiz); //in_ordem comeca percorrendo o no raiz da arvore
    break;
  // case 2:

  //   break;
  // case 3:

  //   break;
  // case 4:

  //   break;
  default:
    printf("Opção inválida. Tente novamente.\n");
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
    int rgValido = 0;
    printf("Digite o RG da pessoa: ");
      scanf("%s", rg); // RG deve ter 9 dígitos, ser entre '.' e '-'
      clearBuffer();
  //  do{
  //   printf("Digite o RG da pessoa: ");
  //   scanf("%s", rg); // RG deve ter 9 dígitos, ser entre '.' e '-'
  //   clearBuffer();
  //   // Verifica se o RG tem exatamente 9 caracteres
  //     if (strlen(rg) == 9) {
  //       rgValido = 1; // RG válido
  //     } else {
  //       printf("RG inválido! O RG deve ter exatamente 9 dígitos. Tente novamente.\n");
  //     }
  //   } while (!rgValido);

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
  } while (rgCadastrado); // como rgJaCadastrado só recebe 1 ou 0, a forma mais comum e clara em C é simplesmente verificar while (rgJaCadastrado);

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

  //adiciona paciente na arvore 

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
  while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) { // while que percorre a lista ate achar o rg
    anterior = atual;
    atual = atual->prox;
  }
  if (atual != NULL) {
    return atual->dados;
  } else {
    registro = NULL; // nao pega lixo de memoria
    printf("Paciente não cadastrado :(\n");
    printf("\n");
    return registro;
  }
}

// item 1 do subMenuAtendimento
void enfileirarPaciente(Lista *lista, Fila *fila, Pilha *stack, Registro *r) { // precisa da condição pra não add o mesmo paciente
  char rg[10];
  printf("Digite o RG do paciente: ");
  scanf("%s", rg);
  printf("\n");
  Registro *paciente = procurarPaciente(lista, rg);
  if (paciente == NULL) {
    return;
  } // Verifica se o paciente já está na fila
    Efila *atual = fila->head;
    while (atual != NULL && atual->dados != paciente) {
      atual = atual->prox;
    }
    if (atual != NULL) {
      printf("Paciente já está na fila\n");
      printf("\n");
      return;
    }
  //adiciona paciente na fila
  Efila *nova = criaEfila(paciente);
  if (fila->qtde == 0) { // fila vazia
    fila->head = nova;
  } else {
    fila->tail->prox = nova;
  }
  fila->tail = nova;
  fila->qtde++;
  printf("Paciente %s entrou na fila!\n", paciente->nome);
  printf("\n");
  // coloca operacao na pilha
  push(stack, 1, paciente);
  // printf("paciente %s adicionado na PILHA \n", paciente->nome);
}

// item 2 do subMenuAtendimento
Registro *desenfileirarpaciente(Lista *lista, Fila *fila, Pilha *stack, Registro *r) { //retorna registro o paciente removido para usar esse registro para enfileirar o paciente quando clico em desfazeroperacao de desenfileirar o paciente
  if (fila->head == NULL) {
    printf("Fila vazia, nenhum paciente para desenfileirar.\n");
    return NULL;
  }
  Efila *removido = fila->head;
  Registro *pacienteRemovido = removido->dados; //para que seja possivel enfileirar ele novamente quando clicar em desfazer operação
  fila->head = fila->head->prox;
  if (fila->head == NULL) {
    fila->tail = NULL; // Se a fila ficou vazia
  }
  fila->qtde--;
  printf("Paciente %s saiu da fila!\n\n", pacienteRemovido->nome);
  // Armazena o paciente removido na pilha para desfazer a operação
  push(stack, 2, pacienteRemovido); 
  // printf("Paciente %s adicionado na PILHA!\n\n", pacienteRemovido->nome);
  free(removido);
  return pacienteRemovido;
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
    printf("%d-Nome: %s\n", cont,r.nome); 
    printf("%d-RG: %s\n", cont,r.rg); 
    printf("%d-Idade: %d\n", cont,r.idade); 
    printf("Data de cadastro: %d/%d/%d\n", r.entrada->dia, r.entrada->mes, r.entrada->ano); 
    atual = atual->prox;
    cont++;
    printf("\n");
  }
}

// para a arvore
E_arvore_busca *criaE_arv(Registro *r){
  E_arvore_busca *novo = malloc(sizeof(E_arvore_busca));
  novo->esq = NULL;
  novo->dir = NULL;
  novo->pai = NULL;
  novo->dados = r;
  return novo;
}

Arvore_busca *criaArvore(){
  Arvore_busca *arvore = malloc(sizeof(Arvore_busca));
  arvore->raiz = NULL;
  arvore->qtde = 0;
  return arvore;
}

void in_ordem(E_arvore_busca *raiz){ //mostra ano em ordem crescente
   if (raiz != NULL) {
    in_ordem(raiz->esq);
    printf("%d\n", raiz->dados->entrada->ano); // Imprime o ano em ordem crescente
    in_ordem(raiz->dir);
  }
}

// item 1 do subMenuPesquisa
Registro *registroOrdenadoAno(Arvore_busca *arvore, Registro *r) { //(Lista *lista, Registro *r
  E_arvore_busca *novo = malloc(sizeof(E_arvore_busca));

  if(arvore->raiz == NULL){//arvore vazia
    arvore->raiz = novo;
  }else{//arvore não vazia
    E_arvore_busca *anterior = NULL;
    E_arvore_busca *atual = arvore->raiz;
    while(atual != NULL){//itera(caminha) para achar o nó de inserção 
      anterior = atual;
        //arruma ponteiros para inserção
      if(r->entrada->ano < atual->dados->entrada->ano){
           atual = atual->esq;
      }
      else if (r->entrada->ano > atual->dados->entrada->ano){
        atual = atual->dir;
      }
    }
    //insere
    novo->pai = anterior; //faz pai do novo ser o anterior 
    if(r->entrada->ano > atual->dados->entrada->ano){//valor a ser inserido > valor do pai
      anterior->dir = novo;
    }else{
      anterior->esq = novo;
    }
    arvore->qtde++;
  }
}

// para a pilha (desfazer operacao)
Epilha *criaEPilha(int operacao, Registro *r) {
  Epilha *celula = malloc(sizeof(Epilha));
  if(celula == NULL){
    printf("Erro ao alocar memória\n");
    return NULL;
  }
  celula->anterior = NULL;
  celula->prox = NULL;
  celula->operacao = operacao;
  celula->dados = r;
  return celula;
}

Pilha *criaPilha() {
  Pilha *stack = malloc(sizeof(Pilha));
  stack->qtde = 0;
  stack->topo = NULL;
  return stack;
}

//funcoes para remocao de operacao 

// empilhar operações da fila de atendimento
void push(Pilha *stack,int operacao, Registro *r) { // endereço da pilha e valor a ser empilhado
  // otimizado
  Epilha *novo = criaEPilha(operacao, r);
  if (stack->qtde > 0) {
    novo->anterior = stack->topo;
    stack->topo->prox = novo;
  }
  stack->topo = novo;
  stack->qtde++;
}

void DesfazerOperacao(Lista *lista, Fila *fila, Pilha *stack) { // desempilhar (pop) operações
  // se pilha é vazia
  if (stack->qtde == 0) {
    printf("Não há operações para desfazer\n");
    return;
  }
  // validar desfazer operação do topo da pilha
  int op = stack->topo->operacao;
  char resp[10];

  // desfazer "enfileirar paciente"
  if (op == 1) {
    Registro *paciente = stack->topo->dados;
    printf("Você deseja desfazer a operação de inserir o paciente %s na fila de atendimento? (S/N): ", paciente->nome);
    scanf("%s", resp);
    if (strcmp(resp, "S") == 0 ||strcmp(resp, "s") == 0) { 
      // remover paciente da fila
      if (fila->head == NULL) {
          printf("A fila já está vazia, não há operações para desfazer.\n");
          return;
        }
        // Remove o último elemento da fila (tail)
        Efila *atual = fila->head;
        if (atual == fila->tail) { // apenas um elemento na fila
          free(fila->tail);
          fila->head = fila->tail = NULL;
        } else {
          // Percorre até o penúltimo elemento
          while (atual->prox != fila->tail) {
            atual = atual->prox;
          }
          free(fila->tail);
          fila->tail = atual;
          fila->tail->prox = NULL;
        }
        fila->qtde--;
        printf("O paciente %s foi removido da fila.\n", paciente->nome);

        // Remove o topo da pilha
        Epilha *temp = stack->topo;
        stack->topo = stack->topo->anterior;
        if (stack->qtde > 1) { // para que o novo topo não aponte para o nó que foi removido
          stack->topo->prox = NULL;
        }
        free(temp);
        stack->qtde--;
      } else {
        printf("Cancelamento de operação cancelado\n");
      }
    }
  // desfazer "desenfileirar paciente"
  if (op == 2) {
    Registro *pacienteRemovido = stack->topo->dados;
    printf("Você deseja desfazer a operação de desenfileirar o paciente %s na fila de atendimento? (S/N): ", pacienteRemovido->nome);
    scanf("%s", resp);
    if (strcmp(resp, "S") == 0 || strcmp(resp, "s") == 0) {
      enfileirarPacienteAutomatico(lista, fila, pacienteRemovido, stack);
      // remove o topo da pilha
      Epilha *temp = stack->topo;
      stack->topo = stack->topo->anterior;
      if (stack->qtde > 1) { // novo topo não aponte para o nó que foi removido
        stack->topo->prox = NULL;
      }
      free(temp);
      stack->qtde--;
    }
  }
}

void enfileirarPacienteAutomatico(Lista *lista, Fila *fila, Registro *pacienteRemovido, Pilha *stack){
  char *rg = pacienteRemovido->rg;
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
    fila->tail = nova;
  } else {
    nova->prox = fila->head;
    fila->head = nova;
  }
  fila->tail = nova;
  fila->qtde++;
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