#include "funcoes.h"
#include <stdio.h>

int main(void) {
  int opcao;
  Lista *lista = criaLista();
  Registro r;
  do {
    opcao = menu();
    switch (opcao) {
    case 1:
      subMenuCadastrar(lista);
    break;
    }
  } while (opcao != 0);
  return 0;
}