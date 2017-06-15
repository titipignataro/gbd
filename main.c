#include "include.h" // stdio,stdlib,string
#include "ged.h" // incluso pagina.h
#include "ga.h"
#include "gbp.h"

int main()
{
int user_nblocos = 10;
ged  gerenciador_disco;
gerenciador_disco = inicializa_ged(user_nblocos);



int end_bloco;
end_bloco = aloca_bloco(gerenciador_disco);
if(end_bloco == -1)
    printf("Nao ha blocos livres disponiveis\n");
else
    printf("Bloco Alocado com exito no endereco %d\n",end_bloco);

pagina pag;
registro user_reg;
strcpy(user_reg.str,"Joao");
//printf("%s",user_reg.str);

pag.slot[0] = cria_registro(pag.slot[0],user_reg);


escreve_bloco(pag);



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
