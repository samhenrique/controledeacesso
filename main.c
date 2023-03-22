#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
// Alunos: Samuel Henrique, Allan Miller e Vinicius Souza

int main(){
    struct log linha;
    Lista* li = cria_lista();
    
    int opcao =-1, numCartao = 0;
    char nomeArquivo[100];

    while(opcao != 0 ){
     printf("\nSistema de Integracao de Controle de Acesso \n\n1- Fazer carga de dados \n2- Desfazer a ultima carga \n3- Buscar inconsistencias\n4- Relatorio de Acesso\n0- Para parar\nInsira sua opcao:\n");
     scanf("%d",&opcao);

     if(opcao == 1){
       Lista* liDescarga = cria_lista();
       printf("Digite o nome do arquivo .csv:");
       scanf("%s",nomeArquivo);
       salvaEmLista(nomeArquivo,liDescarga);
       salvaNoArquivoDescarga(liDescarga);      
       libera_lista(liDescarga);
       salvaEmLista(nomeArquivo,li);
       salvaNoArquivo(li);
       printf("Tamanho: %d\n\n",tamanho_lista(li));

     }else if(opcao == 2){
       percorreArquivo(li,"descarga");
       salvaNoArquivo(li);
     }else if(opcao ==3){
        inconsistencias(li);
     }else if(opcao == 4){
       printf("Insira o numero do cartao a ser consultado\n");
       scanf("%d", &numCartao);
       relatorioAcesso(li, numCartao);
     }else if(opcao == 0){
       return 0;
     }else{
       printf("Opcao Invalida");
     }
  }
return 0;
}

