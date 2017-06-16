
typedef struct Diretorio_blocos{
    int espaco_livre;
    int id_bloco; // addr_bloco
    struct Diretorio_blocos*prox;
}diretorio_blocos;

typedef struct{
    int arquivo_id;
    diretorio_blocos*header; //  //VAI SER UMA LISTA AO INVES DE VETOR, PORQUE VETOR � ESTATICO E LISTA PODE AUMENTAR O TAMANHO
}linha_tabela;

typedef struct{
    linha_tabela tabelas[5];
}ga;

//FUN��ES

//int inicializa_ga(int num_tabelas); //Inicializa diretorio de arquivos e ja define um numero maximo de tabelas que pode haver

ga inicializa_ga(ga diretorio);

int criar_tabela(int tabela,ged*gerenciador_disco,ga*gerenciador_arquivo); //Criar uma nova tabela e chama 'cria_diretorio' para alocar um espa�o no diretorio_arquivos para essa nova tabela(arquivo)

int cria_diretorio(int arquivo_id,ga*diretorio); // Respons�vel por alocar um espa�o no diretorio de arquivos (recebe um arquivo id e um id_bloco proveniente do GED(funcao aloca bloco) para ser a header page) e retornar o endere�o da tabela nova

int checar_espaco_blocos(int arquivo_id, int espaco_necessario); //Repons�vel por checar se existe bloco com espa�o livre (do tamanho do espaco necessario ou menor), e se sim, verificar se o bloco ja esta carregado na memoria, se nao, carregar.

int cria_pagina(void); //Respons�vel por chamar GED para alocar um novo bloco e por criar uma nova p�gina e retornar endere�o dessa nova pagina

int atualiza_espaco(int arquivo_id, int id_pagina, int num); //Repons�vel por atualizar o campo espa�o livre de uma pagina(o campo 'num' teria valor 1 ou -1)

int busca_pagina(int id_arquivo, int id_pagina); //Respons�vel por retornar o endere�o de uma p�gina


//arquivo_id = id da linha_tabela
