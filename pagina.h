#include "registro.h"

#define TAM_FRAME 2 //Cada frame conterá no máximo 2 slots

typedef struct {
    int id_pagina;
    registro slot[TAM_FRAME];
}pagina;

registro cria_registro(registro slot,registro user_reg); //Responsável por inserir um novo registro em uma página
