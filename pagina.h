#include "registro.h"
#define MEMSZ 5
#define TAM_FRAME 2 //Cada frame conterá no máximo 2 slots

typedef struct {
    int id_pagina;
    registro slot[TAM_FRAME];
}pagina;


pagina memoria[MEMSZ];

registro cria_registro(registro slot,registro user_reg); //Responsável por inserir um novo registro em uma página
