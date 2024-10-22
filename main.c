#include <stdio.h>
#include "funcoes.h"
#include "funcoes.c"


int main(void) {
  int opcao;
  do{
    opcao = menu();
    printf("Digite o número de sua escolha: ");
    switch(opcao){
      case 1 :
        break;
    }
  }while(opcao != 0);
  return 0;
}