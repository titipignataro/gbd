
typedef struct{
    int espaco_livre;
    int id_bloco;
}diretorio_blocos;

typedef struct{
    int arquivo_id; //usa pra que ??
    diretorio_blocos* header;
}linha_tabela;

typedef struct{
    linha_tabela tabelas[5];
}diretorio_arquivos;

//FUN��ES

int inicializa_ga(diretorio_arquivos diretorio); //INICIALIZA GA COLOCANDO ARQUIVO_ID=-1 E HEADER=NULL;

int criar_tabela(int tabela,ged gerenciador_disco); //Criar uma nova tabela e chama 'cria_diretorio' para alocar um espa�o no diretorio_arquivos para essa nova tabela(arquivo)

int cria_diretorio(int arquivo_id,diretorio_arquivos diretorio_arquivos,int id_bloco, diretorio_blocos diretorio_blocos); // Respons�vel por alocar um espa�o no diretorio de arquivos (recebe um arquivo id e um id_bloco proveniente do GED(funcao aloca bloco) para ser a header page) e retornar o endere�o da tabela nova

int checar_espaco_blocos(int arquivo_id, int espaco_necessario); //Repons�vel por checar se existe bloco com espa�o livre (do tamanho do espaco necessario ou menor), e se sim, verificar se o bloco ja esta carregado na memoria, se nao, carregar.

int cria_pagina(void); //Respons�vel por chamar GED para alocar um novo bloco e por criar uma nova p�gina e retornar endere�o dessa nova pagina

int atualiza_espaco(int arquivo_id, int id_pagina, int num); //Repons�vel por atualizar o campo espa�o livre de uma pagina(o campo 'num' teria valor 1 ou -1)

int busca_pagina(int id_arquivo, int id_pagina); //Respons�vel por retornar o endere�o de uma p�gina


//arquivo_id = id da linha_tabela
