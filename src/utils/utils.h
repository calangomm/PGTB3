// utils/utils.h
#ifndef UTILS_H
#define UTILS_H

#include "../include/common.h"

//funções para mostrar as cartas no terminal


/**
 * @brief Limpa o terminal.
 */
void limpar_terminal();


/**
 * @brief Limpa o buffer do teclado.
 */
void limpar_buffer();

/**
 * @brief Imprime uma carta no formato especificado.
 *
 * @param c Carta a ser impressa.
 * @param v Valor de virada da carta (0 ou 1).
 */
void imprimir_carta(Carta c, int v);

/**
 * @brief Imprime as cartas de um deck.
 *
 * @param deck Ponteiro para o deck a ser impresso.
 */
void imprimir_deck(Deck *deck);

/**
 * @brief Imprime o estado atual do jogo.
 *
 * @param jogo Ponteiro para a estrutura de jogo a ser impressa.
 */
void imprimir_jogo(Jogo *jogo);

#endif  // UTILS_H
