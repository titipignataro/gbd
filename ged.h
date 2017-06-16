#include "pagina.h"
enum t{
    di =0, //TIPO DIRETORIO
    da = 1 //TIPO DADOS
};
typedef struct{
    //int id_pagina; //Qual pagina na memoria referencia esse bloco
    //int id_bloco; //Referencia ao bloco -> NÃO COLOCAMOS PORQUE CADA POSICAO DA ESTRUTURA ABAIXO CORRESPONDE AO DE CIMA
    enum t tipo;
    int livre; // 0 SE ESTIVER OCUPADO E 1 SE ESTIVER TOTALMENTE LIVRE
} bloco; //INFORMAÇÃO DE CADA BLOCO

typedef struct{
    bloco* blocos_disco; // VETOR PRA GUARDAR CADA BLOCO
    int controle;
} ged;

ged inicializa_ged(int num_blocos); // Inicializa GED, alocando 'num_blocos' blocos

int aloca_bloco(ged*gerenciador_disco,enum t tipo); //Criar um novo bloco e retornar o endereço do mesmo. ALOCAR SEMPRE UM BLOCO QUE TIVER LIVRE = 12

int desaloca_bloco(int id_bloco); //Responsável por desalocar um bloco
// o que fazer?? funcao necessaria?

int escreve_bloco(pagina pag,enum t tipo); //Responsável por escrever página no bloco

pagina ler_bloco(int id_bloco); //Responsável por ler um bloco e retornar uma página correspondente. RECEBE ID DE UM BLOCO DA TABELA E RETORNA UMA PAGINA

