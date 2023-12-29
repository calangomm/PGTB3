#ifndef UI_H
#define UI_H


// Inclusões de bibliotecas padrão
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL_ttf.h>

// Inclusão do arquivo de definições comuns
#include "../include/common.h"


// Definições de constantes para o layout da interface gráfica
#define WINDOW_WIDTH (DIST_HEADER_LEFT*2+CARD_WIDTH*7+CARDS_DIST*6)     //tamanho da largura da janela
#define WINDOW_HEIGHT 212   //tamanho da altura da janela

#define WINDOW_HEIGHT_LVL_2_3_DIF 591 //diferença de altura entre nivel 1 par 2 e 3

#define HEADER_WIDTH 691    //largura do header
#define HEADER_HEIGHT 50    //altura do header

#define TABULEIRO_HEIGHT 509 //altura do tabuleiro

#define DIST_HEADER_TOP 15  //distancia entre o header e a borda superior da janela
#define DIST_HEADER_LEFT 50 //distancia entre o header e a borda esquerda da janela
#define DIST_CARD_HEADER 35 //distancia entre a parte superior da carta e o header
#define DIST_CARDS_BARALHO 24 //distancia entre as cartas nas pilhas do baralho

#define DIST_TOP_H_PLAYS (DIST_HEADER_TOP + 10)     //distancia em y do texto apresentado no header
#define DIST_L_H_PLAYS (DIST_HEADER_LEFT + 9)       //distancia em x do texto PLAYS apresentado no header
#define DIST_L_H_PLAYS_BOX (DIST_L_H_PLAYS + 56)    //distancia em x da caixa de jogadas

#define DIST_L_H_POINTS (DIST_L_H_PLAYS_BOX + 200)  //distancia em x do texto POINTS apresentado no header
#define DIST_L_H_POINTS_BOX (DIST_L_H_POINTS + 64)  //distancia em x da caixa de POINTS

#define DIST_L_H_TIMER_BOX (DIST_L_H_POINTS_BOX + 241)  //distancia em x da caixa de TIMER

#define DIST_TABULEIRO_CARDS 63
#define DIST_TABULEIRO_TOP (DIST_TABULEIRO_CARDS+CARD_HEIGHT+DIST_CARD_HEADER+HEADER_HEIGHT+DIST_HEADER_TOP)
#define DIST_TABULEIRO_BACK (WINDOW_HEIGHT_LVL_2_3_DIF - 40)

#define PLAY_BOX_WIDHT 56       //largura da caixa JOGADAS
#define PLAY_BOX_HEIGHT 33      //altura do texto printado no header

#define POINTS_BOX_WIDHT 64     //largura da caixa PONTOS

#define TIMER_BOX_WIDHT 109     //largura da caixa TIMER

#define CARD_WIDTH 73           //largura da carta
#define CARD_HEIGHT 97          //altura da carta
#define CARDS_DIST 30           //distancia em x da carta

#define FPS 30                  //target fps
#define FRAME_TARGET_TIME (1000 / FPS)      //target frametime

#define MAX_CARD_STRING 10  //numero arbitrario para uma string utilizada para guardar o nome da carta completo com o simbolo
#define NUM_DECKS 6         //numero de deks utilizados no jogo nivel 1

//coordenadas usadas na verificação do mouse
#define Y_AREA_JOGAVEL_INI (DIST_HEADER_TOP+HEADER_HEIGHT+DIST_CARD_HEADER)     //coordenada em y da area jogavel inicial
#define Y_AREA_JOGAVEL_FINAL (Y_AREA_JOGAVEL_INI+CARD_HEIGHT)                   //coordenada em y da area jogavel final                       //coordenada em x da area final do descarte

//para os outros niveis
#define X_I_PILHA1 (DIST_HEADER_LEFT)                    
#define X_F_PILHA1 (X_I_PILHA1+CARD_WIDTH)

#define X_I_PILHA2 (X_F_PILHA1+CARDS_DIST)
#define X_F_PILHA2 (X_I_PILHA2+CARD_WIDTH)

#define X_I_PILHA3 (X_F_PILHA2+CARDS_DIST)
#define X_F_PILHA3 (X_I_PILHA3+CARD_WIDTH)

#define X_I_PILHA4 (X_F_PILHA3+CARDS_DIST)
#define X_F_PILHA4 (X_I_PILHA4+CARD_WIDTH)

#define X_I_PILHA5 (X_F_PILHA4+CARDS_DIST)
#define X_F_PILHA5 (X_I_PILHA5+CARD_WIDTH)

#define X_I_PILHA6 (X_F_PILHA5+CARDS_DIST)
#define X_F_PILHA6 (X_I_PILHA6+CARD_WIDTH)

#define X_I_PILHA7 (X_F_PILHA6+CARDS_DIST)
#define X_F_PILHA7 (X_I_PILHA7+CARD_WIDTH)


//Definição do tamanho da fonte
#define FONT_SIZE 20

// Definição de constantes de cores
#define C_BACKGROUND ((SDL_Color){41, 153, 97, 255})
#define C_HEADER ((SDL_Color){64, 64, 64, 255})
#define C_TABULEIRO ((SDL_Color){95,80,70,255})
#define C_CARDS_BACK ((SDL_Color){20,120,50,255})
#define C_TEXT ((SDL_Color){255,146,36,255})
#define C_P_BACK_BOX ((SDL_Color){210,210,210,255})
#define C_P_BACK_TXT ((SDL_Color){0,0,0,255})


// Estrutura para representar uma carta na interface gráfica
typedef struct {
    float x;
    float y;
    char card[MAX_CARD_STRING];
} graph_card;

/**
 * @brief Inicializa a janela SDL, o renderizador e a fonte TTF.
 *
 * @param window Ponteiro para a variável que receberá a janela SDL.
 * @param renderer Ponteiro para a variável que receberá o renderizador SDL.
 * @param font Ponteiro para a variável que receberá a fonte TTF.
 * @param nivel recebe valor do nivel que está a ser executado
 *
 * @return Retorna verdadeiro (true) se a inicialização for bem-sucedida, falso (false) caso contrário.
 */
int initialize_window(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font, int nivel);


/**
 * @brief Processa os eventos de entrada do usuário.
 *
 * @param game_is_running Ponteiro para a variável que indica se o jogo está em execução.
 * @param jogo Ponteiro para a estrutura que representa o estado do jogo.
 */
void process_input(int *game_is_running, Jogo *jogo);


/**
 * @brief Desenha um retângulo no renderer SDL.
 *
 * @param renderer Ponteiro para o renderer onde o retângulo será desenhado.
 * @param x Coordenada x do canto superior esquerdo do retângulo.
 * @param y Coordenada y do canto superior esquerdo do retângulo.
 * @param width Largura do retângulo.
 * @param height Altura do retângulo.
 * @param color Cor do retângulo (R, G, B, A).
 * @param filled Indica se o retângulo deve ser preenchido (true) ou apenas contornado (false).
 */
void draw_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Color color, bool filled);


/**
 * @brief Carrega uma textura a partir de um arquivo de imagem.
 *
 * @param renderer Ponteiro para o renderer SDL onde a textura será utilizada.
 * @param path Caminho para o arquivo de imagem.
 *
 * @return Retorna um ponteiro para a textura carregada ou NULL em caso de erro.
 */
SDL_Texture* load_texture(SDL_Renderer *renderer, const char *path);


/**
 * @brief Desenha uma imagem em um renderer SDL.
 *
 * @param renderer Ponteiro para o renderer onde a imagem será desenhada.
 * @param path Caminho para o arquivo de imagem.
 * @param x Coordenada x do canto superior esquerdo da imagem.
 * @param y Coordenada y do canto superior esquerdo da imagem.
 * @param width Largura da imagem.
 * @param height Altura da imagem.
 */
void draw_image(SDL_Renderer *renderer, const char *path, int x, int y, int width, int height);


/**
 * @brief Desenha uma carta no cabeçalho do jogo.
 *
 * @param renderer Ponteiro para o renderer onde a carta será desenhada.
 * @param carta Ponteiro para a estrutura que representa a carta.
 * @param path Caminho base para os arquivos de imagem das cartas.
 * @param x Coordenada x do canto superior esquerdo da carta.
 * @param y Coordenada y do canto superior esquerdo da carta.
 */
void desenha_carta_header(SDL_Renderer *renderer, Carta *carta, const char *path, int x, int y);


/**
 * Renderiza um texto em um renderer SDL com opções de posicionamento, tamanho e cores.
 *
 * @param renderer  O renderer SDL onde o texto será renderizado.
 * @param font      A fonte TTF usada para renderizar o texto.
 * @param text      O texto a ser renderizado.
 * @param x         A coordenada x inicial do bloco onde o texto será renderizado.
 * @param y         A coordenada y inicial do bloco onde o texto será renderizado.
 * @param blockWidth Largura do bloco onde o texto será renderizado. Se for 0, a largura do texto será usada.
 * @param blockHeight Altura do bloco onde o texto será renderizado. Se for 0, a altura do texto será usada.
 * @param textColor Cor do texto.
 * @param bgColor   Cor de fundo do bloco onde o texto será renderizado.
 */
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int blockWidth, int blockHeight, SDL_Color textColor, SDL_Color bgColor);


/**
 * @brief Formata o tempo em minutos e segundos para uma string no formato "MM:SS".
 *
 * @param stringFormatada Ponteiro para a string onde o tempo formatado será armazenado.
 * @param minutos Valor dos minutos.
 * @param segundos Valor dos segundos.
 */
void formatarTempo(char *stringFormatada, int minutos, int segundos);


/**
 * @brief Renderiza o estado atual do jogo na tela.
 *
 * @param renderer Ponteiro para o renderer SDL onde o jogo será renderizado.
 * @param jogo Ponteiro para a estrutura que representa o estado do jogo.
 * @param font Ponteiro para a fonte TTF utilizada na renderização.
 */
void render(SDL_Renderer *renderer, Jogo *jogo, TTF_Font *font);


/**
 * @brief Destrói os recursos associados à janela, ao renderer e à fonte TTF.
 *
 * @param window Ponteiro para a janela SDL a ser destruída.
 * @param renderer Ponteiro para o renderer SDL a ser destruído.
 * @param font Ponteiro para a fonte TTF a ser destruída.
 */
void destroy_window(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font);

#endif
