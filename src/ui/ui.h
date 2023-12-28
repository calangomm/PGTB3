#ifndef UI_H
#define UI_H

#include "../include/common.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL_ttf.h>


#define WINDOW_WIDTH (DIST_HEADER_LEFT*2+CARD_WIDTH*7+CARDS_DIST*6)
#define WINDOW_HEIGHT 212

#define HEADER_WIDTH 691
#define HEADER_HEIGHT 50
#define DIST_HEADER_TOP 15
#define DIST_HEADER_LEFT 50
#define DIST_CARD_HEADER 35

#define DIST_TOP_H_PLAYS (DIST_HEADER_TOP + 10)
#define DIST_L_H_PLAYS (DIST_HEADER_LEFT + 9)
#define DIST_L_H_PLAYS_BOX (DIST_L_H_PLAYS + 56)

#define DIST_L_H_POINTS (DIST_L_H_PLAYS_BOX + 200)
#define DIST_L_H_POINTS_BOX (DIST_L_H_POINTS + 64)

#define DIST_L_H_TIMER_BOX (DIST_L_H_POINTS_BOX + 241)


#define PLAY_BOX_WIDHT 56
#define PLAY_BOX_HEIGHT 33

#define POINTS_BOX_WIDHT 64

#define TIMER_BOX_WIDHT 109

#define CARD_WIDTH 73
#define CARD_HEIGHT 97
#define CARDS_DIST 30

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define MAX_CARD_STRING 10
#define NUM_DECKS 6

#define Y_AREA_JOGAVEL_INI (DIST_HEADER_TOP+HEADER_HEIGHT+DIST_CARD_HEADER)
#define Y_AREA_JOGAVEL_FINAL (Y_AREA_JOGAVEL_INI+CARD_HEIGHT)
#define X_FINAL_BARALHO (DIST_HEADER_LEFT+CARD_WIDTH)
#define X_INICIAL_DESCARTE (X_FINAL_BARALHO+CARDS_DIST)
#define X_FINAL_DESCARTE (X_INICIAL_DESCARTE+CARD_WIDTH)
#define X_I_FUND1 (X_FINAL_DESCARTE+CARDS_DIST*2+CARD_WIDTH)
#define X_F_FUND1 (X_I_FUND1+CARD_WIDTH)

#define X_I_FUND2 (X_F_FUND1+CARDS_DIST)
#define X_F_FUND2 (X_I_FUND2+CARD_WIDTH)

#define X_I_FUND3 (X_F_FUND2+CARDS_DIST)
#define X_F_FUND3 (X_I_FUND3+CARD_WIDTH)

#define X_I_FUND4 (X_F_FUND3+CARDS_DIST)
#define X_F_FUND4 (X_I_FUND4+CARD_WIDTH)

#define FONT_SIZE 20

#define C_BACKGROUND ((SDL_Color){41, 153, 97, 255})
#define C_HEADER ((SDL_Color){64, 64, 64, 255})
#define C_CARDS_BACK ((SDL_Color){20,120,50,255})
#define C_TEXT ((SDL_Color){255,146,36,255})
#define C_P_BACK_BOX ((SDL_Color){210,210,210,255})
#define C_P_BACK_TXT ((SDL_Color){0,0,0,255})


typedef struct{
    float x;
    float y;
    char card[MAX_CARD_STRING];
}graph_card;

int initialize_window(SDL_Window **window,SDL_Renderer **renderer, TTF_Font **font);

void process_input(int *game_is_running, Jogo *jogo);

void draw_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Color color, bool filled);

SDL_Texture* load_texture(SDL_Renderer *renderer, const char *path);

void draw_image(SDL_Renderer *renderer, const char *path, int x, int y, int width, int height);

void desenha_carta_header(SDL_Renderer *renderer,Carta *carta, const char *path, int x, int y);

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int blockWidth, int blockHeight, SDL_Color textColor, SDL_Color bgColor);

void formatarTempo(char *stringFormatada, int minutos, int segundos);

void render(SDL_Renderer *renderer, Jogo *jogo, TTF_Font *font);

void destroy_window(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font);

#endif