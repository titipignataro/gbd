#include "include.h" // stdio,stdlib,string
#include "ged.h" // incluso pagina.h
#include "ga.h"
#include "gbp.h"

int inicializa_ga(diretorio_arquivos diretorio){
    int i;
    for(i=0;i<5;i++){
        diretorio.tabelas[i].arquivo_id = -1;
        diretorio.tabelas[i].header = NULL;
    }
    return 1;
}

ged inicializa_ged(int num_blocos) // Inicializa GED, alocando 'num_blocos' blocos e vetor auxiliar de blocos
{
    ged gerenciador_disco;
    gerenciador_disco.controle = num_blocos;
    gerenciador_disco.blocos_disco = (bloco*) malloc(num_blocos*sizeof(bloco));

    int i;
    for(i=0;i<num_blocos;i++)
    gerenciador_disco.blocos_disco[i].livre = 12; // SETANDO BLOCOS PARA INTEIRAMENTE LIVRES ( Livre = 12)

    return gerenciador_disco;
}

//

registro cria_registro(registro slot,registro user_reg)//Respons�vel por inserir um novo registro em uma p�gina
{
strcpy(slot.str,user_reg.str);
return slot;
}
// ANOTACAO:A funcao cria_registro s� insere na pagina. inserir_registro corresponde � operacao toda de insercao do registro.

int aloca_bloco(ged gerenciador_disco){
    int num_blocos = gerenciador_disco.controle;
    int i = 0;

    while(i <= num_blocos && gerenciador_disco.blocos_disco[i].livre != 12){
        i ++; // PROCURANDO BLOCO INTEIRAMENTE LIVRE ( Livre = 12 )
    }
    if(i > num_blocos){
        return -1; // NENHUM BLOCO INTEIRAMENTE LIVRE FOI ENCONTRADO
    }
    else {
        return i; // BLOCO LIVRE ENCONTRADO COM ENDERECO i
    }
}


// FUNCOES EM CONSTRUCAO


int cria_diretorio(int arquivo_id,diretorio_arquivos diretorio_arquivos,int id_bloco){
    int i = 0;
    while(i < 5 && diretorio.tabelas[i].arquivo_id != -1){
        i ++; // PROCURANDO LINHA_TABELA LIVRE PARA SER CRIADA UMA NOVA TABELA
    }
    if(i >= 5){
        printf("\nN�o foi possivel criar uma nova tabela pois a tabela de diretorios esta cheia!\n");
    }else{
        diretorio_blocos nova_entrada;
        nova_entrada.espaco_livre = 12;
        nova_entrada.id_bloco = id_bloco;
        diretorio.tabelas[i].arquivo_id = arquivo_id;
        diretorio.tabelas[i].header = nova_entrada;
    }

}

int criar_tabela(int tabela,ged gerenciador_disco,diretorio_arquivos diretorio){
    int addr_bloco_diretorio;

    addr_bloco_diretorio = aloca_bloco(gerenciador_disco);
    if (addr_bloco_diretorio == -1){
        printf("Erro ao criar tabela\n Blocos ocupados!\n");
        return -1;
    }else{
        cria_diretorio(tabela,diretorio,addr_bloco_diretorio);
        return 1;
    }

}





int escreve_bloco(pagina pag){
FILE*pfile;
pfile = fopen("blocos.txt","w");
int i;
for(i=0;pag.slot[0].str[i]!='\0';i++){
fprintf(pfile,"%c",pag.slot[0].str[i]);
printf("%c",pag.slot[0].str[i]);
}
int tam = strlen(pag.slot[0].str);
// para campos de tamanho fixo

for(i=tam;i<6;i++){
    fprintf(pfile,"X");
}

pfile = fclose(pfile);

}







/*
void ler_do_disco(FILE**pfile,char*k){
*pfile = fopen("blocos.txt","r");
int x = 0;
//fseek(*pfile,x,SEEK_CUR);
int i;
for(i=0;i<6;i++){
fscanf(*pfile,"%c",&k[i]);
printf("%d %c",i,k[i]);
}
*pfile = fclose(*pfile);
}
*/
