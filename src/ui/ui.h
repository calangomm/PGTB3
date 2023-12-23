#ifndef UI_H
#define UI_H

#include "../include/common.h"

#define WINDOW_WIDTH (DIST_HEADER_LEFT*2+CARD_WIDTH*7+CARDS_DIST*6)
#define WINDOW_HEIGHT 212

#define HEADER_WIDTH 691
#define HEADER_HEIGHT 50
#define DIST_HEADER_TOP 15
#define DIST_HEADER_LEFT 50
#define DIST_CARD_HEADER 35

#define CARD_WIDTH 73
#define CARD_HEIGHT 97
#define CARDS_DIST 30

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define MAX_CARD_STRING 10
#define NUM_DECKS 6

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

#define FONT_SIZE 24

#define	c_backgroung 		graph_rgb(41,153,97)


struct header{
    float x;
    float y;
    float width;
    float height;
} header;

struct graph_baralho{
    float x;
    float y;
    float width;
    float height;
} graph_baralho;

typedef struct{
    float x;
    float y;
    char card[MAX_CARD_STRING];
}graph_card;

struct graph_game{
    graph_card deck[NUM_DECKS];
}graph_game;

//int inicializar_window(void);

#endif