// game_logic/game_logic.h
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../include/common.h"
#include <stdbool.h>
#include <time.h>

#define NUM_NAIPES 4    //"♣", "♦", "♥", "♠"
#define NUM_NUMEROS 13  // A, 1, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K
#define NUM_CARTAS (NUM_NAIPES * NUM_NUMEROS)
#define NUM_DECKS 6

//cartas do baralho
typedef struct {
    int virada;  // 0 ou 1
    int naipe;   // 1 a 4
    int numero;  // 1 a 13
} Carta;

//baralho de cartas do jogo (deck)
typedef struct {
    Carta cartas[NUM_CARTAS];
    int indice;
} Deck;


//Jogo
typedef struct {
    Deck baralho;
    Deck descarte;
    Deck fundacao[4];
    time_t start_time;  
    time_t first_command_time;  //esta linha para armazenar o tempo do primeiro comando '1'
<<<<<<< Updated upstream
    int jogadas;              
=======
    int contador_time;
    int jogadas;
    int pontos;               
>>>>>>> Stashed changes
} Jogo;

void inicializar_carta(Carta *carta, int virada, int naipe, int numero);
void retirar_carta(Deck *origem, Deck *destino, int virada);

bool cores_diferentes(Carta origem, Carta destino);
bool verificar_movimento_valido_fundacao(Carta origem, Carta destino);
void atualizar_descarte(Jogo *jogo);

int mover_para_fundacao(Jogo *jogo);

void inicializar_deck(Deck *deck);
void randomizar_deck(Deck *deck);

void inicializar_jogo(Jogo *jogo);
int checagem_fim_de_jogo(Jogo *jogo);

<<<<<<< Updated upstream
=======
void game_run(Jogo *jogo);

>>>>>>> Stashed changes

#endif  // GAME_LOGIC_H
