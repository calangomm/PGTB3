// utils/utils.c
#include "utils.h"
#include "../include/common.h"


/**
 * @brief Limpa o terminal.
 */
void limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


/**
 * @brief Limpa o buffer do teclado.
 */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/**
 * @brief Imprime uma carta no formato especificado.
 *
 * @param c Carta a ser impressa.
 * @param v Valor de virada da carta (0 ou 1).
 */
void imprimir_carta(Carta c, int v) {
    const char *naipes[] = {"♣", "♦", "♥", "♠"}; // Naipes Unicode para uma saída mais bonita

    // Códigos de cores ANSI
    const char *cor_vermelha = "\x1b[31m";
    const char *cor_reset = "\x1b[0m";

    if (!v) {
        if (!c.virada) {
            const char *cor_naipe = (c.naipe == 1 || c.naipe == 3) ? cor_vermelha : cor_reset;

            // Verifica se a carta é um Ás, Valete, Rainha, Rei ou outro número
            if (c.numero == 1) {
                printf("%s A%s %s", cor_naipe, naipes[c.naipe - 1], cor_reset);
            } else if (c.numero == 11) {
                printf("%s J%s %s", cor_naipe, naipes[c.naipe - 1], cor_reset);
            } else if (c.numero == 12) {
                printf("%s Q%s %s", cor_naipe, naipes[c.naipe - 1], cor_reset);
            } else if (c.numero == 13) {
                printf("%s K%s %s", cor_naipe, naipes[c.naipe - 1], cor_reset);
            } else {
                printf("%s%2d%s %s", cor_naipe, c.numero, naipes[c.naipe - 1], cor_reset);
            }
        } else {
            printf("?? ");
        }
    } else {
        const char *cor_naipe = (c.naipe == 1 || c.naipe == 3) ? cor_vermelha : cor_reset;

        // Verifica se a carta é um Ás, Valete, Rainha, Rei ou outro número
        if (c.numero == 1) {
            printf("%s A%s %s", cor_naipe, naipes[c.naipe - 1], cor_reset);
        } else if (c.numero == 11) {
            printf("%s J%s %s", cor_naipe, naipes[c.naipe - 1], cor_reset);
        } else if (c.numero == 12) {
            printf("%s Q%s %s", cor_naipe, naipes[c.naipe - 1], cor_reset);
        } else if (c.numero == 13) {
            printf("%s K%s %s", cor_naipe, naipes[c.naipe - 1], cor_reset);
        } else {
            printf("%s%2d%s %s", cor_naipe, c.numero, naipes[c.naipe - 1], cor_reset);
        }
    }
}


/**
 * @brief Imprime as cartas de um deck.
 *
 * @param deck Ponteiro para o deck a ser impresso.
 */
void imprimir_deck(Deck *deck) {
    for (int i = 0; i < deck->indice; ++i) {
        imprimir_carta(deck->cartas[i], 0);
    }
    printf("\n");
}


/**
 * @brief Imprime o estado atual do jogo.
 *
 * @param jogo Ponteiro para a estrutura de jogo a ser impressa.
 */
void imprimir_jogo(Jogo *jogo) {
    printf("Baralho:\n");
    if (jogo->baralho.indice > 0) {
        imprimir_carta(jogo->baralho.cartas[jogo->baralho.indice - 1], 0);
    } else {
        printf("!!\n");
    }

    printf("\nDescarte:\n");
    if (jogo->descarte.indice > 0) {
        imprimir_carta(jogo->descarte.cartas[jogo->descarte.indice - 1], 0);
    } else {
        printf("!!\n");
    }

    printf("\nFundação:\n");
    for (int i = 0; i < 4; ++i) {
        printf("Fundação %d: ", i + 1);
        if (jogo->fundacao[i].indice > 0) {
            imprimir_carta(jogo->fundacao[i].cartas[jogo->fundacao[i].indice - 1], 0);
        } else {
            printf("N/A");
        }
        printf("\n");
    }

    printf("\n\n");
}