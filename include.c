#include "include.h" // stdio,stdlib,string
#include "ged.h" // incluso pagina.h
#include "ga.h"
#include "gbp.h"

ged inicializa_ged(int num_blocos) // Inicializa GED, alocando 'num_blocos' blocos e vetor auxiliar de blocos
{
    ged gerenciador_disco;
    gerenciador_disco.controle = num_blocos;
    gerenciador_disco.blocos_disco = (bloco*) malloc(num_blocos*sizeof(bloco));

    int i;
    for(i=0;i<num_blocos;i++)
    gerenciador_disco.blocos_disco[i].livre = 1; // SETANDO BLOCOS PARA INTEIRAMENTE LIVRES ( Livre = 1)

    return gerenciador_disco;
}

//

registro cria_registro(registro slot,registro user_reg)//Responsável por inserir um novo registro em uma página
{
strcpy(slot.str,user_reg.str);
return slot;
}
// ANOTACAO:A funcao cria_registro só insere na pagina. inserir_registro corresponde á operacao toda de insercao do registro.

int aloca_bloco(ged*gerenciador_disco,enum t tipo){
int num_blocos;
num_blocos = (*gerenciador_disco).controle;
int i;
i = 0;

while(i <= num_blocos && (*gerenciador_disco).blocos_disco[i].livre != 12){
    i ++; // PROCURANDO BLOCO INTEIRAMENTE LIVRE ( Livre = 12 )
}
if(i > num_blocos){
    return -1; // NENHUM BLOCO INTEIRAMENTE LIVRE FOI ENCONTRADO
}
else {
    (*gerenciador_disco).blocos_disco[i].tipo = tipo;
    return i; // BLOCO LIVRE ENCONTRADO COM ENDERECO i
}
}


// FUNCOES EM CONSTRUCAO

diretorio_blocos* ga_lista_inicia(){
    return NULL;
}

diretorio_blocos* ga_lista_insere(diretorio_blocos*header,int addr_bloco){
    diretorio_blocos*novo;
    novo = (diretorio_blocos*) malloc(sizeof(diretorio_blocos));
    novo->espaco_livre = 6;
    novo->id_bloco = addr_bloco;
    novo->prox = NULL;
    if(header == NULL){
    return novo;
    }
    else {
        diretorio_blocos* aux;
        aux = header;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        return header;

    }

}

ga inicializa_ga(ga diretorio){
int i;
for (i=0;i<5;i++){
diretorio.tabelas[i].arquivo_id = -1;
diretorio.tabelas[i].header = ga_lista_inicia();
}

return diretorio;
}


int cria_diretorio(int arquivo_id,ga*diretorio){

int i;
i = 0;
while(i<5 && (*diretorio).tabelas[i].arquivo_id != -1){
    i++; // PROCURANDO ENTRADA NO VETOR DIRETORIO DESOCUPADA
}
if(i == 5){
    printf("Todas as entradas de diretorio estao ocupadas! Maximo de tabelas ja criadas\n");
    return 0;
}
else{
    (*diretorio).tabelas[i].arquivo_id = arquivo_id;
    return 1;
}

}

int criar_tabela(int tabela,ged*gerenciador_disco,ga*gerenciador_arquivo){
int addr_bloco_diretorio;

addr_bloco_diretorio = aloca_bloco(gerenciador_disco,di);
if (addr_bloco_diretorio == -1){
    printf("Erro ao criar tabela\n Blocos ocupados!\n");
    return -1;
}else{
cria_diretorio(tabela,gerenciador_arquivo);
    return addr_bloco_diretorio;
}

}

gbp inicializa_gbp(gbp gerenciador_bufferpool, pagina* buffer_pool){

int i;
for(i=0;i<MEMSZ;i++){
    gerenciador_bufferpool.frames_gbp[i].pin_count = 0;
    gerenciador_bufferpool.frames_gbp[i].dirty_bit = 0;
    gerenciador_bufferpool.frames_gbp[i].id_bloco = -1;
    gerenciador_bufferpool.frames_gbp[i].referencia = buffer_pool[i];
    }

return gerenciador_bufferpool;
}

void inicializa_memoria(pagina* buffer_pool){
    int i;
    for(i=0;i<MEMSZ;i++){
        buffer_pool[i] = NULL;
    }
}

int inserir_registro(pagina*buffer_pool,gbp*gerenciador_bufferpool,ga*gerenciador_arquivo,int user_tabela,char *user_str,ged*gerenciador_disco){
int i;
i=0;
while(i<5 && (*gerenciador_arquivo).tabelas[i].arquivo_id != user_tabela){
    i++; // BUSCANDO PELA TABELA INFORMADA NO GERENCIADOR DE ARQUIVOS
}
    if(i == 5)
    {
        printf("Tabela informada nao existe no banco!\n");
        return 0;
    }
    else // TABELA EXISTE NO BANCO
        {
        int addr_novo_bloco;
        diretorio_blocos*aux;
        aux = (*gerenciador_arquivo).tabelas[i].header;
        if(aux != NULL) // A LISTA DE PAGINAS EXISTE
        {
            while(aux != NULL && aux->espaco_livre == 0)
            {
                aux = aux->prox; // PROCURANDO NA LISTA DE BLOCOS DA TABELA UMA PAGINA COM ESPAÇO LIVRE
            }
            if(aux == NULL) // NAO ACHOU - PAGINAS TODAS OCUPADAS TOTALMENTE
            {
                addr_novo_bloco = aloca_bloco(gerenciador_disco,di);
                (*gerenciador_arquivo).tabelas[i].header = ga_lista_insere((*gerenciador_arquivo).tabelas[i].header,addr_novo_bloco);
            }
            else // ACHOU A PRIMEIRA PAGINA QUE TEM BYTES LIVRES SUFICIENTES
            {
                aux->espaco_livre = aux->espaco_livre - 6; // pode ser 12 ou 6 e vamos inserir um registro de tamanho 6 bytes
                // -- A MUDANÇA EM AUX SE PROPAGA PARA O HEADER PORQUE ELE É IGUAL AO ARGUMENTO POR REFERENCIA -PONTEIRO *gerenciador_arquivos
            }

        }
        else  // A LISTA ESTA VAZIA - NAO HA BLOCOS ALOCADOS AINDA
        {
            addr_novo_bloco = aloca_bloco(gerenciador_disco,di);
            (*gerenciador_arquivo).tabelas[i].header  = ga_lista_insere( (*gerenciador_arquivo).tabelas[i].header ,addr_novo_bloco);
        }
        return 1;
    }

int j;
j =0;
while(j<MEMSZ && (*gerenciador_bufferpool).frames_gbp[j].pin_count != 0){
    j++; // ACHANDO UMA PAGINA DISPONIVEL NO BUFFER POOL
}
if (j == MEMSZ){
    printf("Buffer Pool Cheio!\n");
    //CHAMAR POLITICA DE SUBSTITUICAO
    //if( (*gerenciador_bufferpool).frames_gbp[j].dirty_bit == 1){
    // Fazer funcao de escrever no disco
    //}
}
else{
    strcpy(buffer_pool[j].slot[0].str,user_str);
}

}

int escreve_bloco(pagina pag,enum t tipo){
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
