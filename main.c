#include <stdio.h>
#include "funcoes.h"
#include <stdio.h>



int main(void) {
  int opcao;
  Lista *lista = criaLista();
  do{
    opcao = menu();
    printf("Digite o número de sua escolha: \n");
    switch(opcao){
      case 1 :
        subMenuCadastrar(lista);
        break;
    }
  }while(opcao != 0);
  return 0;
}