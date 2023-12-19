// utils/utils.h
#ifndef UTILS_H
#define UTILS_H

#include "../include/common.h"

void limpar_terminal();
void limpar_buffer();

void imprimir_carta(Carta c, int v);
void imprimir_deck(Deck *deck);
void imprimir_jogo(Jogo *jogo);

#endif  // UTILS_H
