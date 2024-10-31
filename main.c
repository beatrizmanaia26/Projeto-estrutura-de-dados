#include "funcoes.h"
#include <stdio.h>

int main(void) {
  int opcao;
  Lista *lista = criaLista();
  Fila *fila = criaFila();
  Registro r;
  do {
    opcao = menu();
    switch (opcao) {
    case 1:
      subMenuCadastrar(lista);
    break;
    case 2:
      subMenuAtendimento(lista, fila);
    break;
    case 7:
      sobre();
    break;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  } while (opcao != 0);
  return 0;
}