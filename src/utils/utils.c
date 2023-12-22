// utils/utils.c
#include "utils.h"
#include "../include/common.h"

void limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void imprimir_carta(Carta c, int v) {
    const char *naipes[] = {"♣", "♦", "♥", "♠"}; // Naipes Unicode para uma saída mais bonita

    // Códigos de cores ANSI
    const char *cor_vermelha = "\x1b[31m";
    const char *cor_reset = "\x1b[0m";

    if (!v) {
        if (!c.virada) {
            const char *cor_naipe = (c.naipe == 1 || c.naipe == 3) ? cor_vermelha : cor_reset;

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




void imprimir_deck(Deck *deck) {
    for (int i = 0; i < deck->indice; ++i) {
        imprimir_carta(deck->cartas[i],0);
    }
    printf("\n");
}

void convert_cards_string(Carta c, char *result)
{
    const char *naipes[] = {"\u2663", "\u2666", "\u2665", "\u2660"}; //{'♣', '♦', '♥', '♠'}
    char numero_str[3];
    sprintf(numero_str, "%1d", c.numero);

    // Códigos de cores ANSI
    const char *cor_vermelha = "\x1b[31m";
    const char *cor_reset = "\x1b[0m";
    
    if (!c.virada) {
        const char *cor_naipe = (c.naipe == 1 || c.naipe == 3) ? cor_vermelha : cor_reset;
        strcpy(result, cor_naipe);
        if (c.numero == 1) {
            strcat(result, "A");
            strcat(result,naipes[c.naipe - 1]);
            strcat(result, cor_reset);
        } else if (c.numero == 11) {
            strcat(result, "J");
            strcat(result,naipes[c.naipe - 1]);
            strcat(result, cor_reset);
        } else if (c.numero == 12) {
            strcat(result, "Q");
            strcat(result,naipes[c.naipe - 1]);
            strcat(result, cor_reset);
        } else if (c.numero == 13) {
            strcat(result, "K");
            strcat(result,naipes[c.naipe - 1]);
            strcat(result, cor_reset);
        } else {
            strcat(result, numero_str);
            strcat(result,naipes[c.naipe - 1]);
            strcat(result, cor_reset);
        }
    } else {
        printf("!!");
    }
}

void imprimir_jogo(Jogo *jogo) {
    printf("%-25s %-25s %-25s %-25s %-25s %-25s\n", "Baralho", "Descarte", "Fundação1", "Fundação2", "Fundação3", "Fundação4");

    char baralho[MAX_STRING_CARD] = "";
    char descarte[MAX_STRING_CARD] = "";
    char fundac[4][MAX_STRING_CARD];

    if (jogo->baralho.indice > 0) {
        strncpy(baralho, "??", sizeof(baralho));
    } else {
        strncpy(baralho, "!!", sizeof(baralho));
    }

    if (jogo->descarte.indice > 0) {
        convert_cards_string(jogo->descarte.cartas[jogo->descarte.indice-1],descarte);
    } else {
        strncpy(descarte, "!!", sizeof(descarte));
    }

    for (int i = 0; i < 4; ++i) {
        if (jogo->fundacao[i].indice > 0) {
            convert_cards_string(jogo->fundacao[i].cartas[jogo->fundacao[i].indice - 1],fundac[i]);
        } else {
            strncpy(fundac[i], "!!", sizeof(fundac[i]));
        }
    }

    printf("%-25s %-25s %-25s %-25s %-25s %-25s\n", baralho, descarte, fundac[0], fundac[1], fundac[2], fundac[3]);

}



