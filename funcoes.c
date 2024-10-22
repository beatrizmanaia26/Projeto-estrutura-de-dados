#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

int menu(){
  int opcao;
    printf("Qual o numero da operação que deseja fazer?\n1.Cadastro\n2.Atendimento\n3.Pesquisa\n4.Desfazer Operação\n5.Carregar Arquivo\n6.Salvar Arquivo\n7.Sobre\n");
    scanf("%d", &opcao);
    return opcao;
}