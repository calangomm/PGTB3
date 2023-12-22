#ifndef UI_WM_H
#define UI_WM_H


#ifndef SDL_TTF_H
#define SDL_TTF_H
#include <SDL_ttf.h>
#endif

#include "../include/common.h"

#define WINDOW_WIDTH (DIST_HEADER_LEFT*2+CARD_WIDTH*7+CARDS_DIST*6)
#define WINDOW_HEIGHT 212

#define HEADER_WIDTH 691
#define HEADER_HEIGHT 50

#define CARD_WIDTH 73
#define CARD_HEIGHT 97

#define CARDS_DIST 30

#define DIST_HEADER_TOP 15
#define DIST_HEADER_LEFT 50

typedef struct {
    int largura, altura;  // Tamanho do bloco
    Uint8 cor_r, cor_g, cor_b;  // Componentes RGB da cor
} Bloco;

void window_background(SDL_Renderer *renderer);
void desenhar_bloco(SDL_Renderer *renderer, const Bloco *bloco, int x, int y);
void renderizar_row(SDL_Renderer *renderer, Bloco *blocos, int num_blocos, int distancia_entre_blocos, int x_inicial, int y_inicial);
void renderizar_base(SDL_Renderer *renderer, int distancia_entre_blocos, int x_inicial, int y_inicial);


void renderizar_texto(SDL_Renderer *renderer, const char *texto, int x, int y, int tamanho);

void renderizar_header_status(Jogo *meu_jogo, SDL_Renderer *renderer);
void renderizar_cartas_fRow(Jogo *meu_jogo);

Uint32 calculateElapsedTime(int GameStartTime);

void renderizar_game(Jogo *meu_jogo, SDL_Renderer *renderer);

#endif