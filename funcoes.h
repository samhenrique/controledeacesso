struct log{
  long int DataHora;
  int CodigoCartaoAcesso;
  int CodigoCatraca;
  char TipoEvento;
};
typedef struct elemento* Lista;
typedef struct elemento Elem;


Lista* cria_lista();
int insere_lista_ordenada(Lista* li, struct log linha);
int tamanho_lista(Lista* li);
int salvaEmLista(char carga[],Lista* li);
int percorreArquivo(Lista* li,char carga[]);
void salvaNoArquivo(Lista* li); // so serve para a saida.
void salvaNoArquivoDescarga(Lista* liDescarga);
int remove_lista(Lista* li,struct log linha);
void libera_lista(Lista* li);
void relatorioAcesso(Lista* li, int numerocartao);
int inconsistencias(Lista* li);
int duplicata(Lista* li, struct log linha);