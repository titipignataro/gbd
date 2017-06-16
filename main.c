#include "include.h" // stdio,stdlib,string
#include "ged.h" // incluso pagina.h
#include "ga.h"
#include "gbp.h"

int main()
{
int user_nblocos = 20;
ged  gerenciador_disco;
gerenciador_disco = inicializa_ged(user_nblocos);

ga gerenciador_arquivo;
gerenciador_arquivo = inicializa_ga(gerenciador_arquivo);

int addr_bloco_tabela;
addr_bloco_tabela = criar_tabela(0,&gerenciador_disco,&gerenciador_arquivo);
printf("%d\n",gerenciador_arquivo.tabelas[0].arquivo_id);


//inserir_registro
gbp gerenciador_bufferpool;
gerenciador_bufferpool = inicializa_gbp(gerenciador_bufferpool);

pagina pag;
registro user_reg;
strcpy(user_reg.str,"Joao");
char user_str[6];

strcpy(user_str,"joao");
inserir_registro(memoria,&gerenciador_bufferpool,&gerenciador_arquivo,0,user_str,&gerenciador_disco);
inserir_registro(memoria,&gerenciador_bufferpool,&gerenciador_arquivo,0,user_str,&gerenciador_disco);


printf("\n\n\n I = %d",gerenciador_arquivo.tabelas[0].header->espaco_livre);


//printf("%s",user_reg.str);
pag.slot[0] = cria_registro(pag.slot[0],user_reg);

escreve_bloco(pag,da);


free(gerenciador_disco.blocos_disco);
}

/*
FILE*pfile;
printf("Registro a ser inserido: ");
char w[7],r[6];
gets(&w);
escrever_no_disco(&pfile,w);

ler_do_disco(&pfile,r);

printf("%s",r);

ged g_disco;
gbp g_bufferpool;
*/
