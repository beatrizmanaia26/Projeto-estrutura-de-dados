#include "funcoes.h"
#include <stdio.h>

int main(void) {
  int opcao;
  Lista *lista = criaLista();
  Fila *fila = criaFila();
  Pilha *stack = criaPilha();
  Arvore_busca *arvore = criaArvore();
  Registro r;
  do {
    opcao = menu();
    switch (opcao) {
    case 1:
      subMenuCadastrar(lista);
    break;
    case 2:
      subMenuAtendimento(lista, fila, stack, &r);
    break;
    case 3:
      subMenuPesquisa(arvore, &r);
    break;
    case 4:
      DesfazerOperacao(lista, fila, stack);
    break;
    case 7:
      sobre();
    break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
  } while (opcao != 0);
  return 0;
}