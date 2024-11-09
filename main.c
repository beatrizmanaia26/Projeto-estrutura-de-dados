#include "funcoes.h"
#include <stdio.h>

int main(void) {
  int opcao;
  char arquivo[]= "pacientes";
  Lista *lista = criaLista();
  Fila *fila = criaFila();
  Pilha *stack = criaPilha();
  int cont = 0;
  Arvore_busca *arvoreAno = criaArvore();
  Arvore_busca *arvoreMes = criaArvore();
  Arvore_busca *arvoreDia = criaArvore();
  Arvore_busca *arvoreIdade = criaArvore();
  Registro r;
  do {
    opcao = menu();
    switch (opcao) {
    case 1:
      subMenuCadastrar(lista, arvoreAno, arvoreMes, arvoreDia, arvoreIdade);
    break;
    case 2:
      subMenuAtendimento(lista, fila, stack, &r);
    break;
    case 3:
      subMenuPesquisa(arvoreAno, arvoreMes, arvoreDia, arvoreIdade, &r);
    break;
    case 4:
      DesfazerOperacao(lista, fila, stack);
    break;
    case 5:
      cont = lerArquivo(lista, cont, arquivo,arvoreAno, arvoreMes, arvoreDia, arvoreIdade);
    break;
    case 6:
      salvaArquivo(lista, arquivo);
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