
#define MEMSZ 5 //P�ginas(frames) que podem ser comportadas na mem�ria

typedef struct{
    int pin_count;
    int dirty_bit;
    int id_bloco;
    pagina *referencia;  //APONTA PARA MEMORIA PARA SABER SE E NULL OU NAO
    //struct pagina* addr_pagina;
} frame_info;

typedef struct {
    frame_info frames_gbp[MEMSZ];
} gbp;

//FUN��ES

gbp inicializa_gbp(gbp gerenciador_bufferpool,pagina* buffer_pool);

pagina* verifica_quant_frames(int arquivo_id); //Checa se existem frames livres e retorna uma p�gina(se tiver que criar, chama o 'cria_pagina')



int inserir_registro(pagina*buffer_pool,gbp*gerenciador_bufferpool, ga*gerenciador_arquivo,int user_tabela,char *user_str,ged*gerenciador_disco); //Responsavel por inserir um registro STR. Comunica com GA e chama o checa_espaco_bloco
// ANOTACAO: inserir_registro corresponde � operacao toda de insercao do registro. A funcao cria_registro s� insere na pagina


int gbp_lru(void); //Respons�vel por aplicara pol�tica de substitui��o Least Recently Used


//bloco -> memoria
int habilitar_transferencia(void);// Chama a funcao LER BLOCO do GED pra transferir blcoo para a memoria

int busca_registro(int arquivo_id, char *str); //Respons�vel por retornar o numero do slot de um registro

int atualiza_registro(int arquivo_id, int id_pagina, registro reg, int slot); //Respons�vel por atualizar um registro

int remover_registro(int arquivo_id, int id_pagina, int num_slot); //Respons�vel por remover um registro e atualizar espa�o livre

int escrever_pagina(pagina pagina); //Respons�vel por escrever uma p�gina no disco

int numero_frame(int id_bloco); //Respons�vel por retornar numero do frame de um determinado bloco

void frame_modificado(pagina pagina); //Respons�vel por alterar o campo dirty_bit e dizer que p�gina foi alterada

void pagina_setUse(pagina pagina, int flag); //Se a pagina estiver em uso: flag = 1 -> incrementar pin_count; se flag = 0 -> decrementa pin_count

