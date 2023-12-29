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

<<<<<<< Updated upstream
//cartas do baralho
=======
#define NUM_PILHAS 7

// Inclusões de bibliotecas padrão
#include "../include/common.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Estrutura representando uma carta
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    Deck fundacao[4];
    time_t start_time;  
    time_t first_command_time;  //esta linha para armazenar o tempo do primeiro comando '1'
    int jogadas;              
=======
    Deck fundacao[NUM_NAIPES];
    Deck pilhas[NUM_PILHAS];
    int start_time;  
    int first_command_time;  //esta linha para armazenar o tempo do primeiro comando '1'
    int jogadas;              
    int pontos;
    int nivel;

    /**
     * -1 - nada selecionado
     * 0 - descarte
     * 1 - pilha 1
     * 2 - pilha 2
     * 3 - pilha 3
     * 4 - pilha 4
     * 5 - pilha 5
     * 6 - pilha 6
     * 7 - pilha 7
     * 8 - fundação
    */
    int selecao;
>>>>>>> Stashed changes
} Jogo;

void inicializar_carta(Carta *carta, int virada, int naipe, int numero);
void retirar_carta(Deck *origem, Deck *destino, int virada);

<<<<<<< Updated upstream
=======
/**
 * @brief Inicializa um deck de cartas.
 *
 * @param deck Ponteiro para a estrutura de deck a ser inicializada.
 */
void inicializar_deck(Deck *deck);

/**
 * @brief Embaralha as cartas em um deck usando o algoritmo de Fisher-Yates.
 *
 * @param deck Ponteiro para o deck a ser embaralhado.
 */
void randomizar_deck(Deck *deck);


/**
 * @brief Envia as cartas de baralho para as pilhas 
 * na ordem de inicialização do jogo, de 1 a 7
 *
 * @param jogo Ponteiro para a estrutura de jogo a ser processada
 */
void enviar_para_pilhas(Jogo *jogo);


/**
 * @brief Inicializa a estrutura de jogo.
 *
 * @param jogo Ponteiro para a estrutura de jogo a ser inicializada.
 */
void inicializar_jogo(Jogo *jogo);

/**
 * @brief Retira uma carta de um deck de origem e a coloca em um deck de destino.
 *
 * @param origem Ponteiro para o deck de origem.
 * @param destino Ponteiro para o deck de destino.
 * @param v Valor de virada da carta no deck de destino (0 ou 1).
 */
void retirar_carta(Deck *origem, Deck *destino, int v);

/**
 * @brief Verifica se duas cartas têm cores diferentes.
 *
 * @param origem Carta de origem.
 * @param destino Carta de destino.
 * @return true Se as cartas têm cores diferentes.
 * @return false Se as cartas têm a mesma cor.
 */
>>>>>>> Stashed changes
bool cores_diferentes(Carta origem, Carta destino);
bool verificar_movimento_valido_fundacao(Carta origem, Carta destino);
void atualizar_descarte(Jogo *jogo);

int mover_para_fundacao(Jogo *jogo);

void inicializar_deck(Deck *deck);
void randomizar_deck(Deck *deck);

void inicializar_jogo(Jogo *jogo);
int checagem_fim_de_jogo(Jogo *jogo);


#endif  // GAME_LOGIC_H
