// game_logic/game_logic.h
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// Número de naipes no baralho
#define NUM_NAIPES 4    //"♣", "♦", "♥", "♠"

// Número de diferentes valores nas cartas
#define NUM_NUMEROS 13  // A, 1, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K

// Número total de cartas no baralho
#define NUM_CARTAS (NUM_NAIPES * NUM_NUMEROS)

// Número de baralhos utilizados no jogo
#define NUM_DECKS 6

// Inclusões de bibliotecas padrão
#include "../include/common.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Estrutura representando uma carta
typedef struct {
    int virada;  // 0 ou 1
    int naipe;   // 1 a 4
    int numero;  // 1 a 13
} Carta;


// Estrutura representando um baralho de cartas
typedef struct {
    Carta cartas[NUM_CARTAS];
    int indice;
} Deck;

// Estrutura representando o estado do jogo
typedef struct {
    Deck baralho;
    Deck descarte;
    Deck fundacao[4];
    int start_time;  
    int first_command_time;  //esta linha para armazenar o tempo do primeiro comando '1'
    int jogadas;              
    int pontos;
} Jogo;

// Estrutura para mostrar o tempo do jogo
struct time_show{
    int s;
    int m;
}time_show;


// Estrutura para armazenar a última posição do mouse
struct mouse_last_cord{
    int x;
    int y;
} mouse_last_cord;


// Protótipos de funções
/**
 * @brief Inicializa uma carta com os valores fornecidos.
 *
 * @param carta Ponteiro para a estrutura de carta a ser inicializada.
 * @param virada Valor de virada da carta (0 ou 1).
 * @param naipe Número do naipe (1 a 4).
 * @param numero Número da carta (1 a 13).
 */
void inicializar_carta(Carta *carta, int virada, int naipe, int numero);

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
bool cores_diferentes(Carta origem, Carta destino);

/**
 * @brief Verifica se o movimento de uma carta para a fundação é válido.
 *
 * @param origem Carta de origem.
 * @param destino Carta no topo da fundação.
 * @return true Se o movimento é válido.
 * @return false Se o movimento não é válido.
 */
bool verificar_movimento_valido_fundacao(Carta origem, Carta destino);

/**
 * @brief Atualiza o deck de descarte, movendo cartas do baralho, se necessário.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void atualizar_descarte(Jogo *jogo);

/**
 * @brief Move uma carta do descarte para a fundação, se possível.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 * @return int 1 se o movimento foi bem-sucedido, 0 se não foi.
 */
int mover_para_fundacao(Jogo *jogo);

/**
 * @brief Verifica se as condições de fim de jogo foram atendidas.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 * @param game_is_running Ponteiro para a variável de controle do jogo.
 */
void checagem_fim_de_jogo(Jogo *jogo, int *game_is_running);

/**
 * @brief Mapeia um número de carta para uma letra.
 *
 * @param numero Número da carta.
 * @return char Letra correspondente ao número da carta.
 */
char map_numero_para_letra(int numero);

/**
 * @brief Transforma uma carta em um caminho de imagem.
 *
 * @param carta Ponteiro para a carta a ser transformada.
 * @param path_folder_images Caminho da pasta de imagens.
 * @return const char* Ponteiro para a string do caminho da carta alocada dinamicamente.
 */
const char* transform_card_to_path(const Carta* carta, const char* path_folder_images);

/**
 * @brief Libera a memória alocada para o caminho da carta.
 *
 * @param caminho_da_carta Ponteiro para a string do caminho da carta.
 */
void liberar_caminho_da_carta(const char* caminho_da_carta);

/**
 * @brief Configura o jogo inicialmente.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void setup(Jogo *jogo);

/**
 * @brief Calcula a diferença de tempo desde o início do jogo.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void calcular_diferenca_tempo(Jogo *jogo);

/**
 * @brief Atualiza o estado do jogo.
 *
 * @param last_frame_time Ponteiro para o tempo do último quadro.
 * @param game_is_running Ponteiro para a variável de controle do jogo.
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void update(int *last_frame_time, int *game_is_running, Jogo *jogo);


#endif  // GAME_LOGIC_H