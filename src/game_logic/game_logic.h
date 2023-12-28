// game_logic/game_logic.h
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define NUM_NAIPES 4    //"♣", "♦", "♥", "♠"
#define NUM_NUMEROS 13  // A, 1, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K
#define NUM_CARTAS (NUM_NAIPES * NUM_NUMEROS)
#define NUM_DECKS 6

#include <stdbool.h>

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
    int start_time;  
    int first_command_time;  //esta linha para armazenar o tempo do primeiro comando '1'
    int jogadas;              
    int pontos;
} Jogo;

struct time_show{
    int s;
    int m;
}time_show;

struct mouse_last_cord{
    int x;
    int y;
    int click;
} mouse_last_cord;

void inicializar_carta(Carta *carta, int virada, int naipe, int numero);
void retirar_carta(Deck *origem, Deck *destino, int virada);

bool cores_diferentes(Carta origem, Carta destino);
bool verificar_movimento_valido_fundacao(Carta origem, Carta destino);
void atualizar_descarte(Jogo *jogo);

int mover_para_fundacao(Jogo *jogo);

void inicializar_deck(Deck *deck);
void randomizar_deck(Deck *deck);

void inicializar_jogo(Jogo *jogo);
void checagem_fim_de_jogo(Jogo *jogo, int *game_is_running);

char map_numero_para_letra(int numero);

const char* transform_card_to_path(const Carta* carta, const char* path_folder_images);

void liberar_caminho_da_carta(const char* caminho_da_carta);

void setup(Jogo *jogo);

void calcular_diferenca_tempo(Jogo *jogo);

void update(int *last_frame_time, int *game_is_running, Jogo *jogo);

#endif  // GAME_LOGIC_H