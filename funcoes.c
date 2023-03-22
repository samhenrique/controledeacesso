#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

struct elemento{
    struct log dados;
    struct elemento *prox;
};

Lista *cria_lista() {
  Lista *li = (Lista *)malloc(sizeof(Lista));
  if (li != NULL)
    *li = NULL;
  return li;
}
int tamanho_lista(Lista *li) {
  if (li == NULL)
    return 0;
  int cont = 0;
  Elem *no = *li;
  while (no != NULL) {
    cont++;
    no = no->prox;
  }
  return cont;
}
int insere_lista_ordenada(Lista *li, struct log linha) {
  if (li == NULL)
    return 0;
  Elem *no = (Elem *)malloc(sizeof(Elem));
  if (no == NULL)
    return 0;
  no->dados = linha;
  if ((*li) == NULL) { // lista vazia: insere in�cio
    no->prox = NULL;
    *li = no;
    return 1;
  } else {
    Elem *ant, *atual = *li;
    while (atual != NULL && atual->dados.DataHora < linha.DataHora) {
      ant = atual;
      atual = atual->prox;
    }
    if (atual == *li) { // insere in�cio
      no->prox = (*li);
      *li = no;
    } else {
      no->prox = atual;
      ant->prox = no;
    }
    return 1;
  }
}
int salvaEmLista(char carga[], Lista *li) {
  struct log novaLinha;
  FILE *pontArquivo = fopen(carga, "r");
  if (pontArquivo != NULL) {
    while (!feof(pontArquivo)) {
      fscanf(pontArquivo, "%d;%d;%d;%c\n", &novaLinha.DataHora,
             &novaLinha.CodigoCartaoAcesso, &novaLinha.CodigoCatraca,
             &novaLinha.TipoEvento);
      if (duplicata(li, novaLinha)) {
        insere_lista_ordenada(li, novaLinha);
      }
    }
    fclose(pontArquivo);
    printf("Carga feita com sucesso!");

    return 1;
  } else {
    puts("Nao foi possivel abrir o arquivo");
    return 0;
  }
}

void libera_lista(Lista *li) {
  if (li != NULL) {
    Elem *no;
    while ((*li) != NULL) {
      no = *li;
      *li = (*li)->prox;
      free(no);
    }
    free(li);
  }
}

void relatorioAcesso(Lista* li, int numerocartao){
    char nomecartao[100];
    char salvarstring[100];

    sprintf(salvarstring, "%d", numerocartao);
    strcat(nomecartao, salvarstring);
    strcat(nomecartao, ".csv");
  
    FILE *relatorio = fopen(nomecartao, "w");
    struct log salvar;

    Elem* no = *li;
    for(int i = 0;i < tamanho_lista(li); i++){
        if(no != NULL){
            if(no->dados.CodigoCartaoAcesso == numerocartao){
                salvar.DataHora = no->dados.DataHora;
                salvar.CodigoCartaoAcesso = no->dados.CodigoCartaoAcesso;
                salvar.CodigoCatraca = no->dados.CodigoCatraca;
                salvar.TipoEvento = no->dados.TipoEvento;
                fprintf(relatorio, "%d;%d;%d;%c\n", salvar.DataHora, salvar.CodigoCartaoAcesso, salvar.CodigoCatraca, salvar.TipoEvento);
             }
         no = no->prox;
        }
    }
  fclose(relatorio);
  printf("Relatorio gerado com sucesso!\n");
}

int percorreArquivo(Lista *li, char carga[]) {
  struct log novaLinha;
  FILE *pontArquivo = fopen(carga, "r");
  if (pontArquivo != NULL) {
    while (!feof(pontArquivo)) {
      fscanf(pontArquivo, "%d;%d;%d;%c\n", &novaLinha.DataHora,
             &novaLinha.CodigoCartaoAcesso, &novaLinha.CodigoCatraca,
             &novaLinha.TipoEvento);
      remove_lista(li, novaLinha);
    }
    fclose(pontArquivo);
    return 1;
  } else {
    puts("Nao foi possivel abrir o arquivo");
    return 0;
  }
}
int remove_lista(Lista *li, struct log linha) {
  if (li == NULL)
    return 0;
  if ((*li) == NULL) // lista vazia
    return 0;
  Elem *ant, *no = *li;
  while (no != NULL &&
         no->dados.CodigoCartaoAcesso != linha.CodigoCartaoAcesso &&
         no->dados.DataHora != linha.DataHora &&
         no->dados.CodigoCatraca != linha.CodigoCatraca &&
         no->dados.TipoEvento != linha.TipoEvento) {
    ant = no;
    no = no->prox;
  }
  if (no == NULL) // n�o encontrado
    return 0;

  if (no == *li) // remover o primeiro?
    *li = no->prox;
  else
    ant->prox = no->prox;
  free(no);
  return 1;
}

void salvaNoArquivoDescarga(Lista *liDescarga) {
  FILE *descarga = fopen("descarga.csv", "w");
  if (liDescarga == NULL)
    return;
  Elem *no = *liDescarga;
  while (no != NULL) {
    fprintf(descarga, "%d;%d;%d;%c\n", no->dados.DataHora,
            no->dados.CodigoCartaoAcesso, no->dados.CodigoCatraca,
            no->dados.TipoEvento);
    no = no->prox;
  }
  fclose(descarga);
}
void salvaNoArquivo(Lista *li) {
  FILE *saida = fopen("saida.csv", "w");
  if (li == NULL)
    return;
  Elem *no = *li;
  while (no != NULL) {
    fprintf(saida, "%d;%d;%d;%c\n", no->dados.DataHora,
            no->dados.CodigoCartaoAcesso, no->dados.CodigoCatraca,
            no->dados.TipoEvento);
    no = no->prox;
  }
  fclose(saida);
  fprintf(
      saida,
      "------------------------------------------------------------------\n");
}

int duplicata(Lista *li, struct log linha) {
  if (li == NULL)
    return;
  Elem *no = *li;
  while (no != NULL) {
    if (((no->dados.CodigoCartaoAcesso == linha.CodigoCartaoAcesso) &&
         (no->dados.TipoEvento == linha.TipoEvento) &&
         (no->dados.CodigoCatraca == linha.CodigoCatraca) &&
         (no->dados.DataHora == linha.DataHora))) {
      return 0;
    }
    no = no->prox;
  }
  return 1;
}

int inconsistencias(Lista *li) {
  if ((*li) == NULL) // verifica se a lista esta vazia.
    return 0;
  FILE *inconsistencias = fopen("inconsistencias.csv", "w");
  Elem *no;
  Elem *proximo;
  no = *li;
  int codigo,controlePraAchar,controleNenhum;
  char evento = 'S';
  
  while (no != NULL) { 
    evento = no->dados.TipoEvento;
    codigo = no->dados.CodigoCartaoAcesso; 
    controlePraAchar = 0; // serve para otimar tempo quando ja acha a inconsistencia;
    proximo = no->prox;
    while ((proximo != NULL)  && (controlePraAchar == 0)) { 
      if(codigo == proximo->dados.CodigoCartaoAcesso){
           controleNenhum =1;  // se nao acahou nenhum codigo igual significa uma inconsistencia
        if(evento == proximo->dados.TipoEvento){
            fprintf(inconsistencias, "%d;%d;%d;%c\n", no->dados.DataHora,no->dados.CodigoCartaoAcesso, no->dados.CodigoCatraca,no->dados.TipoEvento);        
            controlePraAchar = 1; // para de procurar quando a inconsistencia é achada.
        }         
      }    
    proximo = proximo->prox;  
    }
    if(controleNenhum == 0 && evento == 'E'){ // nao achou ninguem com o mesmo codigo entao é inconsistencia.
       fprintf(inconsistencias, "%d;%d;%d;%c\n", no->dados.DataHora,no->dados.CodigoCartaoAcesso, no->dados.CodigoCatraca,no->dados.TipoEvento);   
    }
    controleNenhum =0;
    no =  no->prox;
  }
  fclose(inconsistencias);
}