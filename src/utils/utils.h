// utils/utils.h
#ifndef UTILS_H
#define UTILS_H

#define MAX_STRING_CARD 30
#include "../include/common.h"

void limpar_terminal();
void limpar_buffer();

void imprimir_carta(Carta c, int v);
void imprimir_deck(Deck *deck);
void imprimir_jogo(Jogo *jogo);
void convert_cards_string(Carta c, char *result);

#endif  // UTILS_H
